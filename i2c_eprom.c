/******************************************************************************
 * Project: NextGen E-Notice: Secure GSM-Based Dynamic Display System
 * Author: Addala Hari Teja
 * Description: High-level driver for the AT24C256 EEPROM. Uses the I2C 
 * peripheral to read and write multi-byte strings and verify data integrity.
 ******************************************************************************/
#include "i2c.h"
#include "delay.h"

// Forward declaration
void i2c_eeprom_bytewrite(u8 slaveAddr,u16 wBufAddr,u8 dat);

// Writes a string array to sequential addresses in the EEPROM
void EEPROM_write(u8 slaveAddr,u16 wBufStartAddr,u8 *p,u8 nBytes) 
{ 
    int i=0;
    for(i=0;p[i];i++)
    {
        i2c_eeprom_bytewrite(slaveAddr,wBufStartAddr++,p[i]);
    }
    // Append a '#' character to act as an end-of-message terminator in memory
    i2c_eeprom_bytewrite(slaveAddr,wBufStartAddr++,'#'); 
}			  

// Reads sequential bytes from the EEPROM until the '#' terminator is found
void EEPROM_Read(u8 slaveAddr,u16 rBufStartAddr,u8 *p,u8 nBytes) 
{ 
    u8 i; 
    i2c_start();	 
    i2c_write(slaveAddr<<1); // Send device address with write bit (0)
 
    i2c_write(rBufStartAddr>>8); // Send MSB of memory address
    i2c_write(rBufStartAddr);    // Send LSB of memory address

    i2c_restart(); // Switch bus direction to read

    i2c_write(slaveAddr<<1|1); // Send device address with read bit (1)

    for(i=0;i<nBytes;i++) 
    { 
        p[i]=i2c_mack(); // Read byte and acknowledge

        if(p[i]=='#') // Stop reading if the terminator is reached
        {
            break;	
        } 
    }

    p[i]='\0'; // Null-terminate the string for standard C handling

    i2c_nack(); // NACK the last byte to signal the EEPROM to stop transmitting
    i2c_stop(); // Release bus
}

// Writes a single byte to a specific EEPROM address (used for flags and sequential writes)
void i2c_eeprom_bytewrite(u8 slaveAddr,u16 wBufAddr,u8 dat)
{
    i2c_start();
    i2c_write(slaveAddr<<1); // Device address + Write
    i2c_write(wBufAddr>>8);  // Memory Address MSB
    i2c_write(wBufAddr);     // Memory Address LSB
    i2c_write(dat);          // Data payload
    i2c_stop();
    delay_ms(10); // Required write-cycle delay for EEPROM internals to complete
}

// Reads a single byte from a random EEPROM address (used to check status flags)
u8 i2c_eeprom_randomread(u8 slaveAddr,u8 rBufAddr)
{
    u8 dat;
    i2c_start();
    i2c_write(slaveAddr<<1); // Device address + Write
    i2c_write(rBufAddr>>8);	 // Memory Address MSB
    i2c_write(rBufAddr);     // Memory Address LSB
    i2c_restart();
    i2c_write(slaveAddr<<1|1); // Device address + Read
    
    dat=i2c_nack(); // Read byte and NACK to end transfer
    i2c_stop();
    return dat;
}