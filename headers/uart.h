/******************************************************************************
 * File: uart.h
 * Description: Function prototypes and global buffers for the UART0 
 * peripheral, enabling asynchronous communication with the GSM module.
 ******************************************************************************/
#ifndef UART_H
#define UART_H

#include"types.h"

void UART0_Init(void);
void UART0_Tx(u8);
void UART0_Str(u8 *);
char UART0_Rx(void); // Polling read function

// Global buffer holding raw data received from the GSM module via ISR
extern u8 rx_buf[300];

#endif