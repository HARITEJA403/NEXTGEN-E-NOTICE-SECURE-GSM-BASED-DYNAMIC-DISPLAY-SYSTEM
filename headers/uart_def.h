/******************************************************************************
 * File: uart_def.h
 * Description: Hardware register bit configurations, baud rate math, and 
 * Vectored Interrupt Controller (VIC) definitions for the LPC2148 UART0.
 ******************************************************************************/
#ifndef UART_DEF_H
#define UART_DEF_H

// Debug LED mappings
#define TX_LED 16 // Port 1.16
#define RX_LED 17 // Port 1.17

// System Clock and Baud Rate Generation Math
#define FOSC 12000000        // Crystal Oscillator frequency (12 MHz)
#define CCLK (5*FOSC)        // CPU Clock (60 MHz via PLL)
#define PCLK (CCLK/4)        // Peripheral Clock (15 MHz)
#define BAUD 9600            // Target Baud Rate for GSM Module
#define DIVISOR (PCLK/(16*BAUD)) // Divisor Latch Value calculation

#define UART0_CHNO 6         // VIC Channel number for UART0 Interrupts

// PINSEL register bit definitions for UART0
#define TXD0_EN (1<<0)       // Enable TXD0 on P0.0
#define RXD0_EN (1<<2)       // Enable RXD0 on P0.1

// UART Line Control Register (U0LCR) configurations
#define _8BIT 3              // 8-bit character length
#define WORD_LEN_SEL _8BIT
#define DLAB_BIT 7           // Divisor Latch Access Bit (1 = enabled)

// UART Line Status Register (U0LSR) bits
#define DR_BIT 0             // Data Ready (RDR)
#define THRE_BIT 5           // Transmit Holding Register Empty
#define TEMT_BIT 6           // Transmitter Empty

// UART Interrupt Enable Register (U0IER) masks
#define RBR_INTERRUPT_EN (1<<0)  // Receive Data Available interrupt
#define THRE_INTERRUPT_EN (1<<1) // THRE interrupt

#endif