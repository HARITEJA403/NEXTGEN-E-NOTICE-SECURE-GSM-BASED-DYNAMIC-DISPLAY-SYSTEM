/******************************************************************************
 * Project: NextGen E-Notice: Secure GSM-Based Dynamic Display System
 * Author: Addala Hari Teja
 * Description: Hardware UART0 configuration and Interrupt Service Routine (ISR).
 * Facilitates asynchronous communication with the M660A GSM module.
 ******************************************************************************/
#include "uart_def.h"
#include <LPC21xx.H>
#include "types.h"
#include <string.h>
#include "delay.h"
#include "fun.h"

u8 rx_buf[400],new_var;
u32 index;
u8 sms_flag=0,t_flag,ch;

// UART0 Interrupt Service Routine (ISR)
void UART0_interrupt(void) __irq
{
    new_var=U0IIR; // Read Interrupt Identification Register
    
    // Check if interrupt is for 'Receive Data Available' (RDA)
    if((new_var & 0x04))
    {
        ch=U0RBR; // Read incoming byte from Receive Buffer Register

        if(index<300)
        {
            rx_buf[index++]=ch; // Store byte in global buffer

            // "+CMTI" indicates a new SMS has arrived. Flag the main loop to stop scrolling.
            if(strstr((s8*)rx_buf,"+CMTI"))
            {
               sms_flag=1;
            }
        }
    }
    // Check if interrupt is for 'Transmit Holding Register Empty' (THRE)
    else if(new_var &0x02)
    {
        t_flag=1; // Transmission complete flag
    }
    VICVectAddr=0; // Acknowledge the interrupt to the Vectored Interrupt Controller
}

// Configures UART0 baud rate, pin selection, and VIC interrupts
void UART0_Init()
{
    PINSEL0 |= (TXD0_EN | RXD0_EN); // Enable UART0 TX and RX on Port 0

    U0LCR = (WORD_LEN_SEL | (1<<DLAB_BIT)); // Enable Divisor Latch Access for baud rate setup
    U0DLL = 97; // Set Baud Rate (Requires specific peripheral clock configuration)
    U0DLM = 0;
    U0LCR &= ~(1<<DLAB_BIT); // Disable Divisor Latch Access

    // Configure Vectored Interrupt Controller for UART0
    VICVectAddr0 = (unsigned)UART0_interrupt;
    VICVectCntl0 = 0x20 | UART0_CHNO;
    VICIntEnable = 1<<UART0_CHNO;

    U0IER = RBR_INTERRUPT_EN|THRE_INTERRUPT_EN; // Enable RX and TX interrupts
}

// Transmits a single byte via UART0
void UART0_Tx(u8 ch)
{
    t_flag = 0;
    U0THR = ch;
    while(t_flag == 0); // Wait for THRE interrupt to set the flag
}

// Transmits a complete null-terminated string
void UART0_Str(u8 *str)
{
    while(*str)
        UART0_Tx(*str++);	
}

// Blocking function to read a character (Not used during interrupt-driven mode)
char UART0_Rx(void)
{                     
    while (!(U0LSR & 0x01)); // Wait until RDR bit is set
    return (U0RBR);
}