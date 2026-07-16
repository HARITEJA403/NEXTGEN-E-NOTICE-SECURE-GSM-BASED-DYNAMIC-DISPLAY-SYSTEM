/******************************************************************************
 * Project: NextGen E-Notice: Secure GSM-Based Dynamic Display System
 * Author: Addala Hari Teja
 * Description: Low-level I2C protocol driver for the LPC2148. Generates start, 
 * stop, read, write, and acknowledge conditions for the bus.
 ******************************************************************************/
#include "types.h"  
#include "dotmatrix.h"
#include "i2c_defines.h"
#include <LPC21xx.h>    

int count=50000; // Timeout counter to prevent infinite hanging

// Configures I2C pins and sets the serial clock frequency
void init_i2c(void) 
{ 
    PINSEL0 |= SCL_0_2 | SDA_0_3; // Select I2C function on P0.2 (SCL) and P0.3 (SDA)
    I2SCLH = I2C_DIVIDER;         // Set clock high duty cycle
    I2SCLL = I2C_DIVIDER;         // Set clock low duty cycle
    I2CONSET = 1 << I2EN_BIT;     // Enable I2C interface
}

// Generates an I2C Start condition
void i2c_start(void) 
{ 
    I2CONSET = 1 << STA_BIT; // Set Start bit
	
    // Wait for SI (Serial Interrupt) bit to be set, indicating start was sent
    while((((I2CONSET >> SI_BIT) & 1) == 0) && count){
        count--;
    }
    if(count ==0){
        Display("eeprom not connected ",100); // Timeout error handling
    }	    
    I2CONCLR = 1 << STAC_BIT; // Clear Start bit
}

// Generates an I2C Restart condition for changing read/write directions
void i2c_restart(void) 
{ 
    I2CONSET = 1 << STA_BIT; 
    I2CONCLR = 1 << SIC_BIT; // Clear SI flag
    while (((I2CONSET >> SI_BIT) & 1) == 0); // Wait for transmission
    I2CONCLR = 1 << STAC_BIT; 
}

// Generates an I2C Stop condition to release the bus
void i2c_stop(void) 
{ 
    I2CONSET = 1 << STO_BIT; 
    I2CONCLR = 1 << SIC_BIT;
}

// Transmits a single byte over the I2C bus
void i2c_write(u8 dat) 
{
    I2DAT = dat; // Load data into register
    I2CONCLR = 1 << SIC_BIT; // Clear interrupt flag to initiate transfer
    while (((I2CONSET >> SI_BIT) & 1) == 0); // Wait for transfer to complete
}

// Receives a byte and replies with a NACK (Not Acknowledge - typically end of read)
u8 i2c_nack(void) 
{ 
    I2CONCLR = 1 << SIC_BIT; 
    while (((I2CONSET >> SI_BIT) & 1) == 0); 
    return I2DAT;
}

// Receives a byte and replies with an ACK (Acknowledge - to read more bytes)
u8 i2c_mack(void)
{ 
    I2CONSET = 1 << AA_BIT; // Set Assert Acknowledge flag
    I2CONCLR = 1 << SIC_BIT; 
    while (((I2CONSET >> SI_BIT) & 1) == 0);
    I2CONCLR = 1 << AA_BIT;
    return I2DAT;
}