/******************************************************************************
 * Project: NextGen E-Notice: Secure GSM-Based Dynamic Display System
 * Author: Addala Hari Teja
 * Description: Main application loop. Initializes LPC2148 peripherals, reads 
 * stored messages from AT24C256 EEPROM, continuously scrolls the text on 
 * the dot matrix display, and processes GSM module SMS interruptions.
 ******************************************************************************/
#include <string.h>
#include "uart.h"
#include "types.h"
#include "delay.h"
#include "i2c_eeprom.h"
#include "gsm.h"
#include "fun.h"
#include "i2c_eeprom_defines.h"
#include "dotmatrix.h"
#include "i2c.h"

u8 Invalid[300]=""; // Buffer to hold invalid message content for error reporting
u8 stored_msg[400]="    MESSAGE WAITING  "; // Default message if EEPROM is empty
u8 new_msg[512]; // Buffer to store incoming raw SMS from the GSM module
u8 auth_number[] ="9347062370"; // Default authorized master mobile number

extern u8 sms_flag; // Global flag set by UART ISR when an SMS arrives
extern u32 index;   // Global index for UART buffer tracking

// Function to initialize all system hardware peripherals
void init_sym()
{
    UART0_Init(); // Initialize UART0 for GSM communication at specific baud rate
    init_i2c();   // Initialize I2C lines (SDA/SCL) for EEPROM interface
    Init_dm_rows(); // Initialize GPIO pins for 74HC164 shift registers and Dot Matrix rows
    gsm_init();   // Send AT commands to configure GSM module in Text Mode
    
    // Send a boot-up alert to the authorized number regarding character limits
    send_sms(auth_number,"PLEASE ENSURE THE TRANSMITTED DATA DOES NOT EXCEED 140 CHARACTERS.\r\n",Invalid);
}
				 
int main(void)
{
    s32 N_Bytes=100; // Define maximum bytes to read from EEPROM

    init_sym(); // Call hardware initialization

    // Check EEPROM flag at EE_MSGI. If '1', a valid message was previously saved
    if((i2c_eeprom_randomread(I2C_EEPROM_SA1,EE_MSGI))=='1')
        EEPROM_Read(I2C_EEPROM_SA1,EE_MSG,stored_msg,N_Bytes); // Read saved message into buffer

    // Check EEPROM flag at EE_MOBI. If '2', a custom authorized number was saved
    if((i2c_eeprom_randomread(I2C_EEPROM_SA1,EE_MOBI))=='2')
       	EEPROM_Read(I2C_EEPROM_SA1,EE_MOB,auth_number,11); // Read saved mobile number into buffer

   while(1) // Infinite embedded loop
   {
        index=0; // Reset UART buffer index
        memset(rx_buf,'\0',512); // Clear the UART reception buffer
        
        // Loop to continuously display the message until an SMS interrupts
        do
        {
           Display(stored_msg,500); // Send string to shift registers for multiplexing
        } while(sms_flag==0); // Break loop if UART ISR sets sms_flag to 1
        
        sms_flag=0; // Reset SMS flag for the next cycle
        Read_sms(new_msg); // Send AT+CMGR=1 to read the unread SMS into new_msg buffer
	 		
        // Pass the raw SMS and authorized number to security verification function
        switch(verify_format(new_msg,auth_number)) 
        {
            case 1: // Returns 1 if format is Valid Display Update (e.g., 1212Dmsg.)
                extract_content(new_msg,stored_msg); // Strip security code, extract raw text
                N_Bytes=mystrlen(stored_msg); // Calculate length of new message
                
                // Write '1' to EEPROM flag address to indicate message presence
                i2c_eeprom_bytewrite(I2C_EEPROM_SA1, EE_MSGI, '1'); 
                // Write the actual message payload to EEPROM memory
                EEPROM_write(I2C_EEPROM_SA1,EE_MSG,stored_msg,N_Bytes);
                delete_sms(); // Delete processed SMS from SIM card (AT+CMGD=1)
                break;
                
            case 2: // Returns 2 if format is Valid Mobile Number Update (e.g., 1212Mnum.)
                extract_num(new_msg,auth_number); // Extract the new 10-digit number
                
                // Write '2' to EEPROM flag address to indicate custom number presence
                i2c_eeprom_bytewrite(I2C_EEPROM_SA1, EE_MOBI, '2');
                // Write the new mobile number to EEPROM memory
                EEPROM_write(I2C_EEPROM_SA1, EE_MOB, auth_number,11);
                delete_sms(); // Free up GSM memory
                break;
                
            case 3: // Returns 3 if sender is authorized, but syntax is incorrect
                Invalid_msg(new_msg,Invalid); // Extract the malformed message
                // Send SMS feedback to the authorized user explaining the correct syntax
                send_sms(auth_number,"Not a valid format","\r\ncorrect format is 1212Dmsg(.)" );
                delete_sms(); // Delete the malformed SMS
                break;
                
            case 4: // Returns 4 if sender's mobile number does not match auth_number
                Invalid_num(new_msg,Invalid); // Extract the unauthorized number from the AT response
                // Send security alert SMS to the Master admin number with the intruder's details
                send_sms(auth_number,"Invalid access number\r\n",Invalid);
                delete_sms(); // Delete the unauthorized SMS
                break;
        }
    }
}