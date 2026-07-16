/******************************************************************************
 * Project: NextGen E-Notice: Secure GSM-Based Dynamic Display System
 * Author: Addala Hari Teja
 * Description: GSM module driver. Uses standard AT commands over UART to 
 * initialize the module, set it to text mode, and handle SMS transmission.
 ******************************************************************************/
#include "uart.h"
#include "types.h"
#include <string.h>
#include <LPC21xx.H>
#include "gsm.h"
#include "dotmatrix.h"
#include "delay.h"

extern u32 index; // Shared variable to track UART reception buffer position

// Initializes the GSM module and configures it to trigger UART interrupts on new SMS
void gsm_init(void)
{
    index=0;
    memset(rx_buf,'\0',512); // Clear buffer
    UART0_Str("AT\r\n");     // Test communication with GSM module
    delay_s(2);
    rx_buf[index]='\0';

    if(strstr((char*)rx_buf,"OK")) // If GSM responds, proceed with config
    {
        index=0;memset(rx_buf,'\0',512);
        UART0_Str("ATE0\r\n"); // Disable command echo to keep buffer clean
        while(index<3);
        delay_ms(500);
        rx_buf[index]='\0';

        if(strstr((s8*)rx_buf,"OK"))
        {
            index=0;memset(rx_buf,'\0',512);
            UART0_Str("AT+CMGF=1\r\n"); // Set SMS format to Text Mode (instead of PDU)
            delay_s(2);
            delay_ms(500);
            rx_buf[index]='\0';

            if(strstr((s8*)rx_buf,"OK"))
            {
                index=0;memset(rx_buf,'\0',512);
                // Configure module to route incoming SMS alerts directly to the terminal
                UART0_Str("AT+CNMI=2,1,0,0,0\r\n"); 
                while(index<4);
                delay_ms(1100);
                rx_buf[index]='\0';
                
                if(strstr((char*)rx_buf,"OK"))
                    Display(" GSM INIT SUCCESS ",300); // Visual feedback on hardware
                else
                    Display("  GSM INIT TEXT MODE ERROR ",100);					 
            }
            else
                Display("  GSM INIT ERROR ",100);
        }
        else
            Display("  GSM INIT SMS EDRROR ERROR ",100);
    }
    else
        Display("  GSM INIT ERROR NOT CONNECTED  ",100); 	    
}

// Sends an SMS from the GSM module to a specific mobile number
void send_sms(u8 *num, u8 *info,u8 *msg)
{ 
    index=0;memset(rx_buf,'\0',512);
    UART0_Str("AT+CMGS=\""); // AT command to send message
    UART0_Str(num);          // Append destination number
    UART0_Str("\"\r\n");
    delay_ms(500);
    
    index=0;
    UART0_Str(info); // Send header/alert info
    UART0_Str(msg);  // Send actual message payload

    UART0_Tx(0x1A);  // Send CTRL+Z (0x1A) to indicate end of message and transmit
    delay_ms(5000);

    while(index<3);
    rx_buf[index]='\0';
    if(strstr((s8*)rx_buf,"OK"))
    {
        UART0_Str("MESSAGE SENT \r\n"); // Debug confirmation
    }
}

// Deletes the SMS at memory index 1 to ensure the SIM card doesn't fill up
void delete_sms(void)
{
    index=0;memset(rx_buf,0,512);
    UART0_Str("AT+CMGD=1\r\n"); // AT command to delete message
    delay_ms(1000);
    while(index<3);
}

// Reads the SMS stored at memory index 1 into the provided buffer
void Read_sms(u8 *sms)
{
   index=0;
   memset(rx_buf,'\0',512);
   UART0_Str("AT+CMGR=1\r\n"); // AT command to read message
   while(index<3);
   delay_s(2);
   rx_buf[index]='\0';
   
   if(strstr((s8*)rx_buf,"OK"))
       strcpy((char*)sms,(char*)rx_buf); // Copy raw response to application buffer
}