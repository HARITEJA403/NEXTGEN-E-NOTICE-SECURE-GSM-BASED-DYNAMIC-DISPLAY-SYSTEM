/******************************************************************************
 * File: types.h
 * Description: Standardized data type definitions for the project. Using these 
 * exact-width integer types ensures predictable memory allocation across 
 * different compilers and embedded architectures.
 ******************************************************************************/
#ifndef TYPES_H
#define TYPES_H

typedef unsigned char u8;   // 8-bit unsigned (0 to 255)
typedef char  s8;           // 8-bit signed (-128 to 127)
typedef unsigned int u32;   // 32-bit unsigned (0 to 4,294,967,295)
typedef unsigned short int u16; // 16-bit unsigned (0 to 65,535)
typedef signed int s32;     // 32-bit signed
typedef float f32;          // 32-bit floating point
typedef double f64;         // 64-bit double precision floating point

// Custom string length function prototype
u32 mystrlen(u8*mstr);

#endif