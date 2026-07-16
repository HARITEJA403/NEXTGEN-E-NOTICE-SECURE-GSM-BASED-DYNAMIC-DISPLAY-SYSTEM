/******************************************************************************
 * File: i2c.h
 * Description: Function prototypes for the low-level I2C protocol driver.
 ******************************************************************************/
#ifndef I2C_H
#define I2C_H

#include "types.h"

// Configures LPC2148 pins and clock speeds for I2C communication
void init_i2c(void);

// Generates an I2C Start condition on the bus
void i2c_start(void);

// Generates an I2C Restart condition (used when switching read/write directions)
void i2c_restart(void);

// Generates an I2C Stop condition to release the bus
void i2c_stop(void); 

// Transmits an 8-bit data payload over the I2C bus
void i2c_write(u8 dat);

// Receives 8 bits of data and replies with a NACK (Not Acknowledge)
u8 i2c_nack(void); 

// Receives 8 bits of data and replies with an ACK (Acknowledge)
u8 i2c_mack(void);

#endif