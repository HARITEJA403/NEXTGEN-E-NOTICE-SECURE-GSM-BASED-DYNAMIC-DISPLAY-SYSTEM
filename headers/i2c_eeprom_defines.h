/******************************************************************************
 * File: i2c_eeprom_defines.h
 * Description: Defines the hardware slave addresses for AT24Cxxx EEPROMs 
 * on the I2C bus and sets the specific memory map locations for project data.
 ******************************************************************************/
#ifndef I2C_EEPROM_DEFINES_H
#define I2C_EEPROM_DEFINES_H

// 7-Bit Slave Addresses based on hardware A0, A1, A2 pin configurations
#define I2C_EEPROM_SA1 0x50 // Default address when all address pins are grounded
#define I2C_EEPROM_SA2 0x51 
#define I2C_EEPROM_SA3 0x52 
#define I2C_EEPROM_SA4 0x53 
#define I2C_EEPROM_SA5 0x54 
#define I2C_EEPROM_SA6 0x55 
#define I2C_EEPROM_SA7 0x56 
#define I2C_EEPROM_SA8 0x57 

// Custom Memory Map Addresses for the E-Notice System Data
#define EE_MOBI  0x00 // Memory address storing the 'Mobile Auth Setup' flag
#define EE_MOB   0x01 // Starting memory address to store the 10-digit authorized number
#define EE_MSGI  0x14 // Memory address storing the 'Message Present' flag
#define EE_MSG   0x16 // Starting memory address to store the dynamic display string

#endif