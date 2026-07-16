/******************************************************************************
 * Project: NextGen E-Notice: Secure GSM-Based Dynamic Display System
 * Author: Addala Hari Teja
 * Description: Orchestrates the visual output by multiplexing data across 
 * 4 chained 8x8 dot matrix LED boards, creating a scrolling text effect.
 ******************************************************************************/
#include "types.h"
#include <LPC21xx.H>
#include <string.h>
#include "delay.h"
#include "defines.h"
#include "sipo_74hc164.h"
#include "dot_mat_def.h"
#include "dotmatrix.h"

extern u8 sms_flag;

// Initializes the shift registers and sets the microcontroller pins to output
void Init_dm_rows(void)
{
    Init_SIPO_74HC164();
    WRITEBYTE(IODIR0,ROWS,0xFF); // Set all row pins as output
}

// Handles the persistence of vision (POV) multiplexing for 4 characters
void display_str(u8 *str,u32 delay)
{
    u8 i;
    u32 d;
    
    for(d=0;d<delay;d++) // Static delay before the characters shift left
    {
        for(i=0;i<8;i++) // Quickly cycle through all 8 rows
        {
            if(sms_flag==1) // Abort display rendering immediately if SMS interrupt occurs
                break;
                
            WRITEBYTE(IOPIN0,ROWS,0x00); // Turn off all rows to clear previous state

            // Look up character in font array (offsetting ASCII by 32) and shift out row data
            SIPO_74HC164_1(font[str[0]-32][i]);
            SIPO_74HC164_2(font[str[1]-32][i]);
            SIPO_74HC164_3(font[str[2]-32][i]);
            SIPO_74HC164_4(font[str[3]-32][i]);

            WRITEBYTE(IOPIN0,ROWS,(1<<i)); // Turn on the specific row being rendered
            delay_us(40); // Small delay to allow the LEDs to brighten visibly
        }
    }	
}

// Drives the main scrolling effect by advancing the string pointer
void Display(u8*ptr,u32 num)
{
    s32 j;
    u32 len;
    len=mystrlen(ptr);
    
    // Loop through the string, moving the 4-character viewing window by 1 character
    for(j=0;j<len-3;j++)
    {
        if(sms_flag==1)
            break;

        display_str(ptr+j,500); // Display current 4-character window
    } 
}

// Custom string length function to avoid standard library overhead
u32 mystrlen(u8 * str)
{
    u32 i,cnt=0;
    for(i=0;str[i]!='\0';i++)
        cnt++;
    return cnt;
}