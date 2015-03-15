/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.

   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

#include <avr/io.h>

#include "inform.h"

#include "getkeys.h"
#include "io.h"

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
#define BLINK_CNTDN_START = 8 * BLINK_CYCLE_MULTIPLIER;
int blink_cntdn = -1;
uint8_t blink_pattern = BP_OFF;


void flash_led() {
    if (blink_cntdn == -1) {
        blink_pattern = BP_CONSTANT;
        blink_cntdn = 1;
    }
}

void blink_led(enum blink_pattern_e pattern) {
    if (blink_cntdn == -1) {
        blink_pattern = pattern;
        blink_cntdn = BLINK_CNTDN_START - 1;
    }
}

void progress_blink_pattern() {
    if (blink_cntdn > 0) {
        switch_blink_led((((uint8_t) current_pattern) & (1<<(blink_cntdn/BLINK_CYCLE_MULTIPLIER))) > 0);
        --blink_cntdn;
    } else if (blink_cntdn == 0) {
        switch_blink_led(false);
        blink_cntdn = -1;
    }
}

enum blink_pattern_e get_blink_pattern(enum status_code_e code) {
    switch (code) {
    case SC_BOOT_MASTER:
        return BP_LONG_BREAK;
    case SC_BOOT_SLAVE:
        return BP_SHORT_BREAK;
    case SC_ERR_TOO_MANY_KEYS:
        return BP_SHORT;
    case SC_ERR_COMMUNICATION_FAIURE:
        return BP_MEDIUM;
    case SC_ERR_PROGRAMMING_ERROR:
    default:
        return WP_CONSTANT;
    }
}

// how to spread information


void inform(enum infolevel_e il, enum status_code_e code) {
    if (il >= BLINK_INFOLEVEL) {
        blink_led(get_pattern(code));
    }
    if (il >= UART_INFOLEVEL) {
        //uart_putchar(0xA0 | il);
        uart_putchar(code);
    }
}

void info_add(enum infolevel_e il, uint8_t v) {
    if (il >= UART_INFOLEVEL) {
        uart_putchar(v);
    }
}


#if 0
// FIXME redundant to key_change_s
struct keychange_byte_b {
    enum key_change_e kchange : 1;
    uint8_t controller : 1;
    uint8_t row : 3;
    uint8_t col : 3;
};

struct keychange_byte_b keychange_byte(enum key_change_e kchange, uint8_t row, uint8_t controller, uint8_t col) {
    struct keychange_byte_b result = {
        .kchange = kchange,
        .controller = controller,
        .row = row,
        .col = col,
    };
    return result;
}

char keychange_char(enum key_change_e kchange, uint8_t row, uint8_t controller, uint8_t col) {
    struct keychange_byte_b var = keychange_byte(kchange, row, controller, col);
    return * (char *) &var;
}
#endif
