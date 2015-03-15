/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.

   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

#ifndef INFORM_H_
#define INFORM_H_

// TODO
#include "teensy_codelib/uart/uart.h"

enum status_code_e {
    SC_BOOT_MASTER               = 0x00,
    SC_BOOT_SLAVE                = 0x01,
    
    SC_ERR_TOO_MANY_KEYS         = 0x10,
    SC_ERR_COMMUNICATION_FAILURE = 0x20,
    SC_ERR_PROGRAMMING_ERROR     = 0x30,
    
    SC_DBG_KEYSTATES             = 0xF1,
    SC_DBG_USB_KEYS              = 0xF2,
};

enum infolevel_e {
    IL_DBG   = 0x00,
    IL_INFO  = 0x01,
    IL_WARN  = 0x02,
    IL_ERR   = 0x03,
    IL_FATAL = 0x04,
    IL_OFF   = 0x05
};

#if (CONTROLLER == CTLR_MASTER)
#  define UART_INFOLEVEL IL_INFO
#else
#  define UART_INFOLEVEL IL_OFF
#endif

#define BLINK_INFOLEVEL IL_WARN


void inform(enum infolevel_e il, enum status_code_e code);
void info_add(enum infolevel_e il, uint8_t v);

void flash_led();

void update_warn_led();


#endif /* INFORM_H_ */
