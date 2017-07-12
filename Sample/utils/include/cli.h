#ifndef _CLI__H__
#define _CLI__H__

#include "mbed.h"
#include "pc_buffer.h"

#define NEWLINE_GUARD   (curr == '\n' && prev != '\r') || (curr == '\r' && prev != '\n')
#define BUFFER_SIZE     100

extern Serial usb_uart;
bool messageAvailable(void);
void getMessage(char *message, int maxLength);
void init_cli(void);
void receiveHandler(void);

#endif
