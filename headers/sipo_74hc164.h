/******************************************************************************
 * File: sipo_74hc164.h
 * Description: Function prototypes for the bit-banging Serial-In Parallel-Out 
 * driver controlling the 4 chained 74HC164 shift registers.
 ******************************************************************************/
#ifndef SIPO_74HC164_H
#define SIPO_74HC164_H

void Init_SIPO_74HC164(void);
void SIPO_74HC164_1(unsigned char);
void SIPO_74HC164_2(unsigned char);
void SIPO_74HC164_3(unsigned char);
void SIPO_74HC164_4(unsigned char);

#endif