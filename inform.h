/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.

   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

#ifndef INFORM_H_
#define INFORM_H_

#include <stdbool.h>

#include "neomys.h"


enum status_code_e {
    SC_BOOT_MASTER               = 0x00,
    SC_BOOT_SLAVE                = 0x01,
    
    SC_ERR_COMMUNICATION_FAILURE = 0x20,
    SC_ERR_PROGRAMMING_ERROR     = 0x30,
    SC_PROGERR_ALREADY_PRESSED   = 0x31,
    SC_PROGERR_NOT_PRESSED       = 0x32,
    
    SC_WARN_TOO_MANY_KEYS        = 0x10,
    SC_WARN_NOT_YET_IMPLEMENTED  = 0x80,
    SC_WARN_KEY_NOT_YET_IMPLMTD  = 0x81,

    SC_INFO_KEYCHANGE            = 0xC1,
    SC_INFO_SWITCH_TARGET_LAYOUT = 0xC5,

    SC_DBG_KEYSTATES             = 0xE1,
    SC_DBG_USB_KEYS              = 0xE2,

    SC_TRC_MARK_0                = 0xF0,
    SC_TRC_MARK_1                = 0xF1,
    SC_TRC_MARK_2                = 0xF2,
    SC_TRC_MARK_3                = 0xF3,
    SC_TRC_MARK_4                = 0xF4,
    SC_TRC_MARK_5                = 0xF5,
    SC_TRC_MARK_6                = 0xF6,
    SC_TRC_MARK_7                = 0xF7,
    SC_TRC_MARK_8                = 0xF8,
    SC_TRC_MARK_9                = 0xF9,
    SC_TRC_MARK_A                = 0xFA,
    SC_TRC_MARK_B                = 0xFB,
    SC_TRC_MARK_C                = 0xFC,
    SC_TRC_MARK_D                = 0xFD,
    SC_TRC_MARK_E                = 0xFE,
    SC_TRC_MARK_F                = 0xFF,
};

static inline bool is_code_disabled(enum status_code_e code) {
    switch (code) {
    case SC_DBG_KEYSTATES:
        return true;
    default:
        return false;
    }
}

enum infolevel_e {
    IL_DISABLE = 0x00,
    IL_TRACE   = 0x01,
    IL_DBG     = 0x02,
    IL_INFO    = 0x03,
    IL_WARN    = 0x04,
    IL_ERR     = 0x05,
    IL_FATAL   = 0x06,
};

extern const enum infolevel_e UART_INFOLEVEL;
extern const enum infolevel_e BLINK_INFOLEVEL;


#define inform_programming_error() {                     \
        inform(IL_FATAL, SC_ERR_PROGRAMMING_ERROR);      \
        info_add(__FILE__[0]);                           \
        info_add(__FILE__[1]);                           \
        info_add(__FILE__[2]);                           \
        info_add(__LINE__);                              \
    }

static inline bool info_blink(enum infolevel_e il) {
    return il >= BLINK_INFOLEVEL;
}

static inline bool info_uart(enum infolevel_e il) {
    return il >= UART_INFOLEVEL;
}

void inform(enum infolevel_e il, enum status_code_e code);
void info_add(uint8_t v);

void inform_blink(enum status_code_e code);
void flash_led();

void progress_blink_pattern();


#endif /* INFORM_H_ */
