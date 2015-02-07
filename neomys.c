/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include "usb_keyboard.h"
#include "uart.h"
#include "neomys.h"
#include "keymappings.h"

// FIXME why are these symbols not known from iom32u4 ?!?
#define DDRB _SFR_IO8(0x04)
#define PORTB _SFR_IO8(0x05)
#define PINB _SFR_IO8(0x03)
#define DDRF _SFR_IO8(0x10)
#define PORTF _SFR_IO8(0x11)
#define PINF _SFR_IO8(0x0F)

// Data structures for addressing rows

volatile uint8_t * const ROW_PORT_DDR [ROW_COUNT] = { & DDRF, & DDRF, & DDRF, & DDRF, & DDRF };
volatile uint8_t * const ROW_PORT_PORT[ROW_COUNT] = { &PORTF, &PORTF, &PORTF, &PORTF, &PORTF };
volatile uint8_t * const ROW_PORT_PIN [ROW_COUNT] = { & PINF, & PINF, & PINF, & PINF, & PINF };
const    uint8_t         ROW_PORT_BIT [ROW_COUNT] = {      0,      1,      4,      5,      6 };

// Functions for addressing rows

inline void init_row_io(uint8_t row) {
    // set up "open collector"
    *ROW_PORT_DDR [row] &= ~(1 << ROW_PORT_BIT[row]);
    *ROW_PORT_PORT[row] &= ~(1 << ROW_PORT_BIT[row]);
}

inline void activate_row(uint8_t row) {
    // output low
    *ROW_PORT_DDR [row] |=  (1 << ROW_PORT_BIT[row]);
}

inline void deactivate_row(uint8_t row) {
    // input (open collector)
    *ROW_PORT_DDR [row] &= ~(1 << ROW_PORT_BIT[row]);
}

// Data structures for addressing columns

volatile uint8_t * const COL_PORT_DDR [COL_COUNT] = { & DDRB, & DDRB, & DDRB, & DDRB, & DDRB, & DDRB, & DDRB, & DDRB };
volatile uint8_t * const COL_PORT_PORT[COL_COUNT] = { &PORTB, &PORTB, &PORTB, &PORTB, &PORTB, &PORTB, &PORTB, &PORTB };
volatile uint8_t * const COL_PORT_PIN [COL_COUNT] = { & PINB, & PINB, & PINB, & PINB, & PINB, & PINB, & PINB, & PINB };
const    uint8_t         COL_PORT_BIT [COL_COUNT] = {      0,      1,      2,      3,      4,      5,      6,      7 };

// Functions for addressing cols

inline void init_col_io(uint8_t col) {
    // set up input with pull up
    *COL_PORT_DDR [col] &= ~(1 << COL_PORT_BIT[col]);
    *COL_PORT_PORT[col] &=  (1 << COL_PORT_BIT[col]);
}

inline char test_col(uint8_t col) {
    // return 0 when the pin is high (pull up resistor), 1 when the pin is low (shut to ground by key switch)
    return (*COL_PORT_PIN[col] &  (1 << COL_PORT_BIT[col])) ? 0 : 1 ;
}

// UART

const uint32_t UART_BAUD_RATE = 9600;

// global symbols

enum keymapping_mode_e keymapping_mode_current = KMM_DE;


// global functions

inline void init() {
    uint8_t row, col;

    uart_init(UART_BAUD_RATE);

    for (row = 0; row < ROW_COUNT; ++row) {
        init_row_io(row);
    }
    for (col = 0; col < COL_COUNT; ++col) {
        init_col_io(col);
    }

    clear_active_keys();
}

struct key_id_s {
    uint8_t row :4;
    uint8_t col :4;
};

// Master and slave will write their active keys' ids to active_keys[0..ACTIVE_KEYS_CNT_MAX-1].
// Master will write the active keys' ids received from slave in the following part of active_keys[].
const size_t ACTIVE_KEYS_CNT_MAX = 8;
struct key_id_s active_keys[2 * ACTIVE_KEYS_CNT_MAX] = { 0xFF };
uint8_t io_keys_cnt = 0;
uint8_t rx_keys_cnt = 0;

void add_key(uint8_t row, uint8_t col) {
    if (io_keys_cnt < ACTIVE_KEYS_CNT_MAX) {
        active_keys[io_keys_cnt].row = row;
        active_keys[io_keys_cnt].col = col;
        ++io_keys_cnt;
    } else {
        warning();
    }
}

void clear_active_keys() {
    memset(active_keys, 0xFF, sizeof(active_keys));
    io_keys_cnt = 0;
    rx_keys_cnt = 0;
}

void tx_keys() {
    int i;
    for (i = 0; i < ACTIVE_KEYS_CNT_MAX; ++i) {
        uart_putchar(i);
        uart_putchar(active_keys[i]);
    }
}

void rx_keys() {
    int rx_cnt = 0;
    while (uart_available() == 0) {
        _delay_ms(5);
    }
    int i = 0;
    while (i < ACTIVE_KEYS_CNT_MAX - 1 || rx_cnt < ACTIVE_KEYS_CNT_MAX) {
        i = uart_getchar();
        if (i >= ACTIVE_KEYS_CNT_MAX) {
            // probabld received key id instead of i => next char should be a valid i
            i = uart_getchar();
            warning();
        }
        active_keys[io_keys_cnt + i] = uart_getchar();
        if (active_keys[io_keys_cnt + i] != 0xFF) {
            rx_keys_cnt = i + 1;
        }
    }
    if (rx_cnt > ACTIVE_KEYS_CNT_MAX) {
        warning();
    }
}

const size_t KEYBOARD_KEYS_CNT = sizeof(keyboard_keys) / sizeof(keyboard_keys[0]);

struct keyset_out_s {
    uint8_t keyboard_modifier_keys;
    uint8_t keyboard_keys[6];
};

const size_t KEYSET_QUEUE_CNT_MAX = 8;
struct keyset_out_s keyset_queue[KEYSET_QUEUE_CNT_MAX];
size_t keyset_queue_first = 0;
size_t keyset_queue_last = 0;

void process_keys() {
    int i;

    // find level
    enum neo_levels_e level = LEVEL1;
    for (i = 0; i < io_keys_cnt + rx_keys_cnt; ++i) {
        if (active_keys[i] != 0xFF) { // XXX this check should not be necessary ...
            union keyout_u kout = get_mapped_key(keymapping_mode_current, LEVEL0, active_keys[i].row, i < io_keys_cnt ? SIDE_MASTER : SIDE_SLAVE, active_keys[i].col);
            if (kout.type.type == KO_LEVEL_MOD) {
                if (level == LEVEL1) {
                    level = kout.level_mod.level;
                } else if (level == kout.level_mod.level) {
                    levellock(level);
                    // TODO
                }
            }
        }
    }

    // fill keyboard_keys
    for (i = 0; i < io_keys_cnt + rx_keys_cnt; ++i) {
        if (active_keys[i] != 0xFF) { // XXX this check should not be necessary ...
            union keyout_u kout = get_mapped_key(keymapping_mode_current, LEVEL0, active_keys[i].row, i < io_keys_cnt ? SIDE_MASTER : SIDE_SLAVE, active_keys[i].col);
            if (kout.type.type == KO_LEVEL_MOD) {
                if (level == LEVEL1) {
                    level = kout.level_mod.level;
                } else if (level == kout.level_mod.level) {
                    levellock(level);
                    // TODO
                }
            }
        }
    }
    

    if (memcmp(prev_row_state, row_state, 2*ROW_SPACE*sizeof(row_state[0][0]))) {

        uint8_t side;
        for (side = 0; side < 2; ++side) {
            uint8_t row;
            for (row = 0; row < ROW_COUNT; ++row) {
                uint8_t xor = prev_row_state[side][row] ^ row_state[side][row];
                if (xor > 0) {
                    uint8_t col;
                    for (col = 0; col < COL_COUNT; ++col) {
                        if (xor & (1 << col) > 0) {
                            // key state at [row,col] has changed
                            if (row_state[side][row] & (1 << col) > 0) {
                                // key press
                            } else {
                                // key release
                            }
                        }
                    } // col loop
                } // xor > 0
            } // row loop
        } // side loop

        memcpy(prev_row_state, row_state, 2*ROW_SPACE*sizeof(row_state[0][0]));
    } // memcmp
}

int main(void) {
    uint8_t row;
    for (row = 0; row < ROW_COUNT; ++row) {
        activate_row(row);
        row_state[CONTROLLER][row] = 0;
        uint8_t col;
        for (col = 0; col < COL_COUNT; ++col) {
            row_state[CONTROLLER][row] |= (test_col(col) << row);
        }
        deactivate_row(row);
    }
#if (CONTROLLER == CTLR_MASTER)
    //    rx_slave(row_state[CTLR_SLAVE]);
    process_states();
#else
    tx_states(row_state[CONTROLLER]);
#endif
    return 0;
}
