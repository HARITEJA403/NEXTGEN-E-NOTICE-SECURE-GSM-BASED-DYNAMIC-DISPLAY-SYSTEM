/******************************************************************************
 * File: defines.h
 * Description: Standardized bit-manipulation macros used across the project 
 * to directly modify hardware registers safely and efficiently.
 ******************************************************************************/
#ifndef DEFINES_H
#define DEFINES_H

// Sets a specific bit to 1 without altering other bits
#define SETBIT(WORD,BP) WORD|=(1<<BP)

// Clears a specific bit to 0 without altering other bits
#define CLRBIT(WORD,BP) WORD&=~(1<<BP)

// Toggles (complements) a specific bit (1 becomes 0, 0 becomes 1)
#define CPLBIT(WORD,BP) WORD^=(1<<BP)

// Writes a specific bit value (0 or 1) to a specific bit position
#define WRITEBIT(WORD,BP,BIT) WORD=((WORD&~(1<<BP))|(BIT<<BP))

// Writes a 4-bit nibble starting at a specific bit position
#define WRITENIBBLE(WORD,SBP,NIBBLE) WORD=((WORD&~(0xf<<SBP))|(NIBBLE<<SBP))

// Writes an 8-bit byte starting at a specific bit position
#define WRITEBYTE(WORD,SBP,BYTE) WORD=((WORD&~(0xff<<SBP))|(BYTE<<SBP))

// Writes a 16-bit half-word starting at a specific bit position
#define WRITEHWORD(WORD,SBP,HWORD) WORD=((WORD&~(0xffff<<SBP))|(HWORD<<SBP))

#endif