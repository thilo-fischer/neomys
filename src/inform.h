/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.

   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

#ifndef INFORM_H_
#define INFORM_H_


#define inform(il, code)
#define info_add(v)

#define inform_blink(code)
#define flash_led()

#define progress_blink_pattern()


#if 0

#include <stdbool.h>

#include "neomys.h"

// event: KS_PRESS == 1 or KS_RELEASE == 0

enum status_code_e {
    SC_BOOT_MASTER               = 0x00, // =>   0 | nil
    SC_BOOT_SLAVE                = 0x01, // =>   1 | nil

    SC_ERR_COMMUNICATION_FAILURE = 0x20, // =>  32 | 
    SC_ERR_PROGRAMMING_ERROR     = 0x30, // =>  48 | 
    SC_PROGERR_ALREADY_PRESSED   = 0x31, // =>  49 | 
    SC_PROGERR_NOT_PRESSED       = 0x32, // =>  50 | 

    SC_WARN_TOO_MANY_KEYS        = 0x10, // =>  16 | 
    SC_WARN_NOT_YET_IMPLEMENTED  = 0x80, // => 128 | 
    SC_WARN_KEY_NOT_YET_IMPLMTD  = 0x81, // => 129 | 

    SC_INFO_KEYCHANGE            = 0xC1, // => 193 | event:1 ctlr:1 row:3 col:3
    SC_INFO_SWITCH_TARGET_LAYOUT = 0xC5, // => 197 | 

    SC_DBG_KEYSTATES             = 0xE1, // => 225 | 
    SC_DBG_USB_KEYS              = 0xE2, // => 226 | modifiers | keys[6]
    SC_DBG_KEYSEQ_ENQUEUE        = 0xE4, // => 228 | key | event | modifiers
    SC_DBG_USB_MOD_PRESS         = 0xE8, // => 232 | modifier-XOR
    SC_DBG_USB_MOD_RELEASE       = 0xE9, // => 233 | modifier-XOR
    SC_DBG_USB_MOD_AUTOCHANGE    = 0xEA, // => 234 | 

    SC_TRC_MARK_0                = 0xF0, // => 240
    SC_TRC_MARK_1                = 0xF1, // => 241
    SC_TRC_MARK_2                = 0xF2, // => 242
    SC_TRC_MARK_3                = 0xF3, // => 243
    SC_TRC_MARK_4                = 0xF4, // => 244
    SC_TRC_MARK_5                = 0xF5, // => 245
    SC_TRC_MARK_6                = 0xF6, // => 246
    SC_TRC_MARK_7                = 0xF7, // => 247
    SC_TRC_MARK_8                = 0xF8, // => 248
    SC_TRC_MARK_9                = 0xF9, // => 249
    SC_TRC_MARK_A                = 0xFA, // => 250
    sc_TRC_MARK_B                = 0xFB, // => 251
    SC_TRC_MARK_C                = 0xFC, // => 252
    SC_TRC_MARK_D                = 0xFD, // => 253
    SC_TRC_MARK_E                = 0xFE, // => 254
    SC_TRC_MARK_F                = 0xFF, // => 255
};

enum infolevel_e {
    IL_DISABLE = 0x00,  ///< informs of this level will never be issued
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
        info_add((char) (__LINE__>>8)&0xFF);             \
        info_add((char) (__LINE__   )&0xFF);             \
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

#endif

#endif /* INFORM_H_ */
