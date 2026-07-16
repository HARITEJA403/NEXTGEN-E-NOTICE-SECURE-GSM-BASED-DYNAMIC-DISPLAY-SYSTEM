/******************************************************************************
 * File: gsm.h
 * Description: Function prototypes for the M660A GSM Module driver.
 ******************************************************************************/
#ifndef GSM_H
#define GSM_H

#include "types.h"

// Initializes the GSM module via UART and sets it to text mode
void gsm_init(void);

// Formats and transmits an SMS to a specified mobile number
void send_sms(u8 *num, u8* info, u8 *msg);

// Deletes the SMS at memory location 1 on the SIM card
void delete_sms(void);

// Sends the AT command to read an unread SMS into a buffer
void Read_sms(u8*sms);

#endif