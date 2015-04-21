/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.

   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

/**
 * @file
 * Mechanisms to send information on the current state of the firmware program to the outside world, i.e. trigger LED blinking, send debug information via UART, etc.
 */

#include <avr/io.h>
#include "teensy_codelib/uart/uart.h"

#include "inform.h"

#include "getkeys.h"
#include "io.h"

// fixme: move to header file
const enum infolevel_e UART_INFOLEVEL =
#if (CONTROLLER == CTLR_MASTER)
    //IL_INFO
    IL_DBG
    //IL_TRACE
    // #error this is MASTER
#else
    IL_FATAL
    //IL_DBG
    //IL_TRACE
    // #error this is SLAVE
#endif
    ;
const enum infolevel_e BLINK_INFOLEVEL = IL_WARN;


static inline bool is_code_disabled(enum status_code_e code) {
    switch (code) {
#if 0
    case SC_DBG_KEYSTATES:
        return true;
#endif
    default:
        return false;
    }
}


// status LED

enum blink_pattern_e {
    BP_OFF = 0x00,
    BP_SHORT = 0xAA,
    BP_MEDIUM = 0xCC,
    BP_LONG = 0xF0,
    BP_CONSTANT = 0xFF,
    BP_SHORT_BREAK = 0xA5,
    BP_LONG_BREAK = 0xC3,
};

#define BLINK_CYCLE_MULTIPLIER 4
#define BLINK_CNTDN_START (8 * BLINK_CYCLE_MULTIPLIER)
int blink_cntdn = -1;
enum blink_pattern_e blink_pattern = BP_OFF;


void flash_led() {
    if (blink_cntdn == -1) {
        blink_pattern = BP_CONSTANT;
        blink_cntdn = 1;
    }
}

void blink_led(enum blink_pattern_e pattern) {
    if (blink_cntdn < 1) {
        blink_pattern = pattern;
        blink_cntdn = BLINK_CNTDN_START - 1;
    }
}

void progress_blink_pattern() {
    if (blink_cntdn > 0) {
        switch_onboard_led((((uint8_t) blink_pattern) & (1<<(blink_cntdn/BLINK_CYCLE_MULTIPLIER))) > 0);
        --blink_cntdn;
    } else if (blink_cntdn == 0) {
        switch_onboard_led(false);
        blink_cntdn = -1;
    }
}

enum blink_pattern_e get_blink_pattern(enum status_code_e code) {
    switch (code) {
    case SC_BOOT_MASTER:
        return BP_LONG_BREAK;
    case SC_BOOT_SLAVE:
        return BP_SHORT_BREAK;
    case SC_ERR_COMMUNICATION_FAILURE:
        return BP_MEDIUM;
    case SC_ERR_PROGRAMMING_ERROR:
        return BP_CONSTANT;
    case SC_WARN_TOO_MANY_KEYS:
        return BP_SHORT;
    case SC_WARN_NOT_YET_IMPLEMENTED:
        return BP_CONSTANT;
    case SC_WARN_KEY_NOT_YET_IMPLMTD:
        return BP_SHORT;
    case SC_INFO_SWITCH_TARGET_LAYOUT :
        return BP_MEDIUM;
    default:
        return BP_OFF;
    }
}

// how to spread information

void inform_blink(enum status_code_e code) {
    uint8_t pattern = get_blink_pattern(code);
    if (pattern == BP_OFF)
        inform_programming_error();
    blink_led(pattern);
}

enum infolevel_e current_level = IL_DISABLE;

void inform(enum infolevel_e il, enum status_code_e code) {
    if (is_code_disabled(code)) {
        current_level = IL_DISABLE;
        return;
    }
    if (il >= BLINK_INFOLEVEL) {
        uint8_t pattern = get_blink_pattern(code);
        if (pattern != BP_OFF)
            blink_led(pattern);
    }
    if (il >= UART_INFOLEVEL) {
        uart_putchar(code);
    }
    current_level = il;
}

void info_add(uint8_t v) {
    if (current_level >= UART_INFOLEVEL) {
        uart_putchar(v);
    }
}


