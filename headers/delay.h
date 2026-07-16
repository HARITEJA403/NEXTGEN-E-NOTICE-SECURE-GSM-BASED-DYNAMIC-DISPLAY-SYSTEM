/******************************************************************************
 * File: delay.h
 * Description: Function prototypes for hardware blocking delays.
 ******************************************************************************/
#ifndef DELAY_H
#define DELAY_H

// Generates a delay in microseconds (us)
void delay_us(unsigned int);

// Generates a delay in milliseconds (ms)
void delay_ms(unsigned int);

// Generates a delay in seconds (s)
void delay_s(unsigned int);

#endif