/******************************************************************************
 * File: dotmatrix.h
 * Description: Function prototypes for controlling the 8x8 Dot Matrix displays.
 ******************************************************************************/
#ifndef DOTMATRIX_H
#define DOTMATRIX_H

#include "types.h"

// Initializes the GPIO pins and Shift Registers required to drive the rows/columns
void Init_dm_rows(void);

// Renders a static 4-character chunk onto the multiplexed displays
void display_str(u8 *str,u32 dly);

// Main orchestrator for shifting characters to create the scrolling text effect
void Display(u8*ptr,u32 num);

#endif