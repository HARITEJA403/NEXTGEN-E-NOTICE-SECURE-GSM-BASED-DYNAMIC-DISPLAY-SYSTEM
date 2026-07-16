/******************************************************************************
 * File: security.h
 * Description: Function prototypes for authentication and message parsing.
 * Handles the extraction of payloads and validation of authorized senders.
 ******************************************************************************/
#ifndef SECURITY_H
#define SECURITY_H

#include"types.h"

int verify_format(u8 *msg,u8*Author_num);
void extract_content(u8 *msg, u8 *output);
void extract_num(u8 *msg,u8 *num);
void Invalid_msg(u8*msg,u8*invalid_msg);
void Invalid_num(u8*msg,u8*invalid_msg);

#endif