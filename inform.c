/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.

   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

#include <avr/io.h>

#include "inform.h"

#include "getkeys.h"
#include "io.h"

// warning LED

enum blink_pattern_e {
    WP_OFF = 0x00,
    WP_SHORT = 0xAA,
    WP_MEDIUM = 0xCC,
    WP_LONG = 0xF0,
    WP_CONSTANT = 0xFF,
    WP_SHORT_BREAK = 0xA5,
    WP_LONG_BREAK = 0xC3,
};

#define WARN_CYCLE_MULTIPLIER 4
const int WARN_CNTDN_START = 8 * WARN_CYCLE_MULTIPLIER;
int warn_cntdn = -1;
uint8_t current_pattern = WP_OFF;

void init_warn_led() {
    DDRD |= (1<<6);
}

static inline void switch_warn_led(bool on) {
    if (on == true) {
        PORTD |= (1<<6);
    } else {
        PORTD &= ~(1<<6);
    }
}

void warning(enum warnings_e code) {
    if (warn_cntdn == -1) {
        dbg_uarttx_byte(0xE0 | code);
        warn_cntdn = WARN_CNTDN_START - 1;
        switch (code) {
        case W_TOO_MANY_KEYS:
            current_pattern = WP_MEDIUM;
            break;
        case W_COMMUNICATION_FAILURE:
            current_pattern = WP_LONG_BREAK;
            break;
        case W_PROGRAMMING_ERROR:
            current_pattern = WP_SHORT;
            break;
        case W_MASTER:
            current_pattern = WP_LONG;
            break;
        case W_SLAVE:
            current_pattern = WP_SHORT;
            break;
        default:
            current_pattern = WP_CONSTANT;
        }
    }
}

void flash_led() {
    if (warn_cntdn == -1) {
        warn_cntdn = 0;
        switch_warn_led(true);
    }
}

void update_warn_led() {
    if (warn_cntdn > 0) {
        switch_warn_led((((uint8_t) current_pattern) & (1<<(warn_cntdn/WARN_CYCLE_MULTIPLIER))) > 0);
        //switch_warn_led(true);
        --warn_cntdn;
    } else if (warn_cntdn == 0) {
        switch_warn_led(false);
        warn_cntdn = -1;
    }
}

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

