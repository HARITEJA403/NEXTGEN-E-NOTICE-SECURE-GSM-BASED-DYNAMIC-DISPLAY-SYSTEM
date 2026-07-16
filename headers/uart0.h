/******************************************************************************
 * File: uart0.h
 * Description: Basic UART0 function prototypes.
 ******************************************************************************/
#ifndef UART0_H
#define UART0_H

void UART0_init(void);
void UART0_Tx(unsigned char);
void UART0_Str(unsigned char *);

#endif