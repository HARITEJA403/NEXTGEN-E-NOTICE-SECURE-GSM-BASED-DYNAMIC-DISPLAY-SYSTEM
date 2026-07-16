/******************************************************************************
 * File: i2c_defines.h
 * Description: Hardware register bit configurations and clock speed math 
 * required to initialize the LPC2148's I2C peripheral.
 ******************************************************************************/
#ifndef I2C_DEFINES_H
#define I2C_DEFINES_H

// Define pin selection masks for I2C0 functions on Port 0
#define SCL_0_2   0x00000010 // Pin P0.2 mapped to Serial Clock (SCL)
#define SDA_0_3   0x00000040 // Pin P0.3 mapped to Serial Data (SDA)

// Defines for I2C Clock Speed Configuration  
#define FOSC      12000000   // External Oscillator Frequency (12 MHz)
#define CCLK      (5*FOSC )  // CPU Clock (Multiplier configured in PLL)
#define PCLK      (CCLK/4)   // Peripheral Clock (Hz) 
#define I2C_SPEED 100000     // Target I2C Bus Speed (100 kHz - Standard Mode)

// Calculate the divider value to load into I2SCLH/I2SCLL registers
#define I2C_DIVIDER   ((PCLK/I2C_SPEED)/2) 

// Bit definitions for the I2C Control Set Register (I2CONSET)
#define   AA_BIT 2  // Assert Acknowledge flag
#define   SI_BIT 3  // Serial Interrupt flag
#define  STO_BIT 4  // Stop flag
#define  STA_BIT 5  // Start flag
#define I2EN_BIT 6  // I2C Interface Enable flag

// Bit definitions for the I2C Control Clear Register (I2CONCLR)
#define   AAC_BIT 2 // Clear Assert Acknowledge flag
#define   SIC_BIT 3 // Clear Serial Interrupt flag
#define  STAC_BIT 5 // Clear Start flag
#define I2ENC_BIT 6 // Clear I2C Interface Enable flag

#endif