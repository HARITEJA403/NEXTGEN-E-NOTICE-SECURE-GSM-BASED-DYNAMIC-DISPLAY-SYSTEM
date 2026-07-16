/******************************************************************************
 * File: fun.h
 * Description: Function prototypes for string parsing and security validation.
 ******************************************************************************/
#ifndef FUN_H
#define FUN_H

#include "types.h" // Ensure standard data types (u8, u32) are available

// Validates command format and verifies sender authorization
int verify_format(u8*msg,u8*Author_num);

// Extracts the actual display text by stripping the security command header
void extract_content(u8 *msg, u8 *output);

// Extracts the new mobile number from a master update SMS command
void extract_num(u8 *msg,u8 *num);

// Extracts the malformed command string to send back as an error report
void Invalid_msg(u8*msg,u8*invalid_msg);

// Extracts the unauthorized phone number to alert the master administrator
void Invalid_num(u8*msg,u8*invalid_msg);

#endif