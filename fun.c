/******************************************************************************
 * Project: NextGen E-Notice: Secure GSM-Based Dynamic Display System
 * Author: Addala Hari Teja
 * Description: Security and string manipulation functions. Validates sender 
 * authentication and extracts data payloads utilizing pointer arithmetic.
 ******************************************************************************/
#include<string.h>
#include"fun.h"

// Verifies if the SMS is from the authorized number and checks the command syntax
int verify_format(u8 *msg,u8 *Author_num)
{
    // Check if the authorized number exists anywhere in the raw AT response string
    if(strstr((s8*)msg,(s8*)Author_num))
    {
        // Check if the string contains "1212D" (Display command) AND "." (Terminator)
        if((strstr((s8*)msg,"1212D"))&& (strstr((s8*)msg,".")))  
        {
            return 1; // Valid Display Command
        }
        // Check if the string contains "1212M" (Mobile Update command) AND "." (Terminator)
        else if((strstr((s8*)msg,"1212M"))&& (strstr((s8*)msg,".")))
        {
            return 2; // Valid Number Update Command
        }
        else
        {
            return 3; // Authorized user, but invalid command syntax
        }
    }
    else
        return 4; // Unauthorized sender detected
}

// Extracts the actual message text by stripping away the security header
void extract_content(u8 *msg1,u8 *output)
{
    u32 i,j=0;
    s8*msg=NULL;
    memset(output,'\0',400); // Clear the destination buffer
    
    // Find the starting pointer of the command "1212D"
    msg=strstr((s8*)msg1,"1212D");
    
    // Iterate through the string until the termination character '.' is found
    for(i=3;msg[i]!='.';i++)
    {
        if(i<5) // Skip the "2D" portion of "1212D"
            output[j++]=' ';
        // Replace unwanted control characters (form feed, newline, carriage return) with spaces
        else if(msg[i]=='\f' || msg[i]=='\n' || msg[i]=='\r' || msg[i]=='\t'|| msg[i]==' ')
        {
            output[j++]=' ';
        }
        else // Copy valid character to the output buffer
            output[j++]=msg[i];
    }
    // Append padding spaces at the end to ensure smooth scrolling off the display
    output[j++]=' ';
    output[j++]=' ';
    output[j++]=' ';
    output[j++]=' ';
    output[j]='\0'; // Null-terminate the string
}