/******************************************************************************
 * File: i2c_eeprom.h
 * Description: Function prototypes for high-level EEPROM read/write operations.
 ******************************************************************************/
#ifndef I2C_EEPROM_H
#define I2C_EEPROM_H

#include "types.h"

// Writes an array of bytes (string) to sequential addresses in EEPROM
void EEPROM_write(u8 slaveAddr, u16 wBufStartAddr, u8 *p, u8 nBytes);

// Reads an array of bytes from sequential EEPROM addresses until termination
void EEPROM_Read(u8 slaveAddr, u16 rBufStartAddr, u8 *p, u8 nBytes); 

// Reads a single byte from a specific memory address (used for checking flags)
u8 i2c_eeprom_randomread(u8 slaveAddr, u8 rBufAddr);

// Writes a single byte to a specific memory address
void i2c_eeprom_bytewrite(u8 slaveAddr, u8 wBufAddr, u8 dat);

#endif