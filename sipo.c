/******************************************************************************
 * Project: NextGen E-Notice: Secure GSM-Based Dynamic Display System
 * Author: Addala Hari Teja
 * Description: Bit-banging Serial-In Parallel-Out (SIPO) driver for the 
 * 74HC164 shift registers, which drive the dot matrix cathode columns.
 ******************************************************************************/
#include <LPC21xx.H>
#include "delay.h"
#include "defines.h"
#include "types.h"

// Define GPIO pin mappings for the 4 cascading shift registers (Data and Clock pins)
#define SIN_1 8   // Data in for Register 1
#define CP_1  9   // Clock for Register 1
#define SIN_2 10  // Data in for Register 2
#define CP_2  11  // Clock for Register 2
#define SIN_3 12  // Data in for Register 3
#define CP_3  13  // Clock for Register 3
#define SIN_4 14  // Data in for Register 4
#define CP_4  15  // Clock for Register 4

// Configures the mapped pins as GPIO outputs
void Init_SIPO_74HC164(void)
{
    SETBIT(IODIR0,SIN_1);
    SETBIT(IODIR0,CP_1);
    SETBIT(IODIR0,SIN_2);
    SETBIT(IODIR0,CP_2);
    SETBIT(IODIR0,SIN_3);
    SETBIT(IODIR0,CP_3);
    SETBIT(IODIR0,SIN_4);
    SETBIT(IODIR0,CP_4);
}

// Bit-bangs 1 byte of data into Shift Register 1
void SIPO_74HC164_1(u8 sDat)
{
    u8 i;
    
    for(i=0;i<8;i++) // Shift out MSB (Most Significant Bit) first
    {
        // Extract the bit and set the data pin accordingly
        WRITEBIT(IOPIN0,SIN_1,((sDat>>(7-i))&1));
        
        // Generate a clock pulse to shift the data bit into the 74HC164
        IOCLR0 = 1<<CP_1; // Clock line Low
        delay_us(1);
        IOSET0 = 1<<CP_1; // Clock line High (rising edge triggers the shift)
        delay_us(1);
    }
}

// Bit-bangs 1 byte of data into Shift Register 2
void SIPO_74HC164_2(u8 sDat)
{
    u8 i;
    for(i=0;i<8;i++)
    {
        WRITEBIT(IOPIN0,SIN_2,((sDat>>(7-i))&1));
        IOCLR0 = 1<<CP_2;
        delay_us(1);
        IOSET0 = 1<<CP_2;
        delay_us(1);
    }	
}

// Bit-bangs 1 byte of data into Shift Register 3
void SIPO_74HC164_3(u8 sDat)
{
    u8 i;
    for(i=0;i<8;i++)
    {
        WRITEBIT(IOPIN0,SIN_3,((sDat>>(7-i))&1));
        IOCLR0 = 1<<CP_3;
        delay_us(1);
        IOSET0 = 1<<CP_3;
        delay_us(1);
    }	
}

// Bit-bangs 1 byte of data into Shift Register 4
void SIPO_74HC164_4(u8 sDat)
{
    u8 i;
    for(i=0;i<8;i++)
    {
        WRITEBIT(IOPIN0,SIN_4,((sDat>>(7-i))&1));
        IOCLR0 = 1<<CP_4;
        delay_us(1);
        IOSET0 = 1<<CP_4;
        delay_us(1);
    }	
}