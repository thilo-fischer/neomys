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

// FIXME why are these symbols not known from iom32u4.h ?!?
#define DDRB  _SFR_IO8(0x04)
#define PORTB _SFR_IO8(0x05)
#define PINB  _SFR_IO8(0x03)
#define DDRC  _SFR_IO8(0x07)
#define PORTC _SFR_IO8(0x08)
#define PINC  _SFR_IO8(0x06)
#define DDRD  _SFR_IO8(0x0A)
#define PORTD _SFR_IO8(0x0B)
#define PIND  _SFR_IO8(0x09)
#define DDRF  _SFR_IO8(0x10)
#define PORTF _SFR_IO8(0x11)
#define PINF  _SFR_IO8(0x0F)

// Data structures for addressing rows

volatile uint8_t * const ROW_PORT_DDR [ROW_COUNT] = { & DDRF, & DDRF, & DDRF, & DDRF, & DDRF };
volatile uint8_t * const ROW_PORT_PORT[ROW_COUNT] = { &PORTF, &PORTF, &PORTF, &PORTF, &PORTF };
volatile uint8_t * const ROW_PORT_PIN [ROW_COUNT] = { & PINF, & PINF, & PINF, & PINF, & PINF };
const    uint8_t         ROW_PORT_BIT [ROW_COUNT] = {      0,      1,      4,      5,      6 };

// Functions for addressing rows

static inline void init_row_io(uint8_t row) {
    // set up "open collector"
    *ROW_PORT_DDR [row] &= ~(1 << ROW_PORT_BIT[row]);
    *ROW_PORT_PORT[row] &= ~(1 << ROW_PORT_BIT[row]);
}

static inline void activate_row(uint8_t row) {
    // output low
    *ROW_PORT_DDR [row] |=  (1 << ROW_PORT_BIT[row]);
}

static inline void deactivate_row(uint8_t row) {
    // input (open collector)
    *ROW_PORT_DDR [row] &= ~(1 << ROW_PORT_BIT[row]);
}

// Data structures for addressing columns

volatile uint8_t * const COL_PORT_DDR [COL_COUNT] = { & DDRB, & DDRB, & DDRB, & DDRB, & DDRB, & DDRB, & DDRB, & DDRB };
volatile uint8_t * const COL_PORT_PORT[COL_COUNT] = { &PORTB, &PORTB, &PORTB, &PORTB, &PORTB, &PORTB, &PORTB, &PORTB };
volatile uint8_t * const COL_PORT_PIN [COL_COUNT] = { & PINB, & PINB, & PINB, & PINB, & PINB, & PINB, & PINB, & PINB };
const    uint8_t         COL_PORT_BIT [COL_COUNT] = {      0,      1,      2,      3,      4,      5,      6,      7 };

// Functions for addressing cols

static inline void init_col_io(uint8_t col) {
    // set up input with pull up
    *COL_PORT_DDR [col] &= ~(1 << COL_PORT_BIT[col]);
    *COL_PORT_PORT[col] &=  (1 << COL_PORT_BIT[col]);
}

static inline char test_col(uint8_t col) {
    // return 0 when the pin is high (pull up resistor), 1 when the pin is low (shut to ground by key switch)
    return (*COL_PORT_PIN[col] &  (1 << COL_PORT_BIT[col])) ? 0 : 1 ;
}

// warning LED

const int WARN_CNTDN_START = 10;
int warn_cntdn = 0;

static inline void init_warn_led() {
    DDRD |= (1<<6);
}

static inline void switch_warn_led(bool on) {
    if (on == true) {
        PORTD |= (1<<6);
    } else {
        PORTD &= ~(1<<6);
    }
}

static inline void warning(enum warnings_e code) {
    switch_warn_led(true);
    warn_cntdn = WARN_CNTDN_START;
}

static inline void update_warn_led() {
    if (warn_cntdn > 0) {
        --warn_cntdn;
        if (warn_cntdn == 0) {
            switch_warn_led(false);
        }
    }
}


// UART

const uint32_t UART_BAUD_RATE = 9600;

// global symbols

/**
 * Keyboard layout the USB host is configured to use.
 */
enum keylayout_e keymapping_mode_current = TKL_DE;
enum neo_levels_e level_current = LEVEL1;

// key states
// Transmit states of all keys from slave to master. This is the simplest, most deterministic and probably most fail-safe approach (compared to sending only pressed keys or key state changes).

uint8_t key_state[2][ROW_COUNT] = {{0}, {0}};
uint8_t prev_key_state[2][ROW_COUNT] = {{0}, {0}};

void update_own_key_states() {
    uint8_t row;
    for (row = 0; row < ROW_COUNT; ++row) {
        activate_row(row);
        key_state[CONTROLLER][row] = 0;
        uint8_t col;
        for (col = 0; col < COL_COUNT; ++col) {
            key_state[CONTROLLER][row] |= (test_col(col) << row);
        }
        deactivate_row(row);
    }
}

// No row has 8 keys (COL_COUNT < 8), so every row state byte will always have at least one 0-bit in it. 0xFF is an impossible row byte value, so if can be used to mark beginning and end of a transmission.
const uint8_t startendbyte = 0xFF;

void tx_keystates() {
    uint8_t row;
    uart_putchar(startendbyte);
    for (row = 0; row < ROW_COUNT; ++row) {
        uart_putchar(key_state[CTLR_SLAVE][row]);
    }
    uart_putchar(startendbyte);
}

void discard_uart() {
    uint8_t available;
    do {
        _delay_ms(1);
        available = uart_available();
        int i;
        for (i = 0; i < available; ++i) {
            uart_getchar();
        }
    } while (available != 0);
}

/**
 * @return 0 on success, error code if transmission failure detected: 1 -- start byte not found; 2 -- end byte too early; 3 -- end byte not found.
 */
int rx_keystates() {
    while (uart_available() == 0);
    uint8_t rx_byte;
    rx_byte = uart_getchar();
    if (rx_byte != startendbyte) {
        discard_uart();
        return 1;
    }
    uint8_t row;
    for (row = 0; row < ROW_COUNT; ++row) {
        rx_byte = uart_getchar();
        if (rx_byte == startendbyte) {
            discard_uart();
            return 2;
        }
        key_state[CTLR_SLAVE][row] = rx_byte;
    }
    rx_byte = uart_getchar();
    if (rx_byte != startendbyte) {
        discard_uart();
        return 3;
    }
    return 0;
}


// key changes

enum key_change_e {
    KC_PRESS   = 0,
    KC_RELEASE = 1,
};

struct key_change_s {
    enum key_change_e change; // :1;
    enum controller_e controller; // :1;
    uint8_t row; // :3;
    uint8_t col; // :3;
};

#define CHANGED_KEYS_CNT_MAX 8
struct key_change_s changed_keys[CHANGED_KEYS_CNT_MAX] = {{ 0 }}; // XXX initialization is debugging aid only
uint8_t keychange_cnt = 0;

void add_levelchange(uint8_t row, enum controller_e controller, uint8_t col, enum key_change_e kchange) {};

void add_keychange(uint8_t row, enum controller_e controller, uint8_t col, enum key_change_e change) {
    if (keychange_cnt < CHANGED_KEYS_CNT_MAX) {
        changed_keys[keychange_cnt].change = change;
        changed_keys[keychange_cnt].controller = controller;
        changed_keys[keychange_cnt].row = row;
        changed_keys[keychange_cnt].col = col;
        ++keychange_cnt;
    } else {
        warning(W_TOO_MANY_KEYS);
    }
}

void clear_changed_keys() {
    memset(changed_keys, 0, sizeof(changed_keys)); // XXX debugging aid only
    keychange_cnt = 0;
}


// bitfield
uint8_t level_modifiers = 0;


const size_t KEYBOARD_KEYS_CNT = sizeof(keyboard_keys) / sizeof(keyboard_keys[0]);

struct keyset_out_s {
    uint8_t keyboard_modifier_keys;
    uint8_t keyboard_keys[6];
};

#define KEYSET_QUEUE_CNT_MAX 8
struct keyset_out_s keyset_queue[KEYSET_QUEUE_CNT_MAX];
size_t keyset_queue_first = 0;
size_t keyset_queue_last = 0;

void process_key_states_deprecated() {
    int i;

    // find level
    enum neo_levels_e level = LEVEL1;
    for (i = 0; i < keychange_cnt; ++i) {
        if ((*(uint8_t*) &changed_keys[i]) != 0xFF) { // XXX this check should not be necessary ...
            const union keyseq_u *kout = get_mapped_key(keymapping_mode_current, LEVEL1, changed_keys[i].row, true ? CTLR_MASTER : CTLR_SLAVE, changed_keys[i].col);
            if (kout->type.type == KO_LEVEL_MOD) {
                if (level == LEVEL1) {
                    level = kout->level_mod.level;
                } else if (level == kout->level_mod.level) {
                    //levellock(level);
                    // TODO
                }
            }
        }
    }

    // fill keyboard_keys
    for (i = 0; i < keychange_cnt; ++i) {
        if ((*(uint8_t*) &changed_keys[i]) != 0xFF) { // XXX this check should not be necessary ...
            const union keyseq_u *kout = get_mapped_key(keymapping_mode_current, LEVEL1, changed_keys[i].row, true ? CTLR_MASTER : CTLR_SLAVE, changed_keys[i].col);
            if (kout->type.type == KO_LEVEL_MOD) {
                if (level == LEVEL1) {
                    level = kout->level_mod.level;
                } else if (level == kout->level_mod.level) {
                    //levellock(level);
                    // TODO
                }
            }
        }
    }
}    

static inline const union keyseq_u *get_current_mapped_key(enum controller_e controller, enum row_e row, uint8_t col) {
    return get_mapped_key(keymapping_mode_current, controller, row, col, level_current);
}

void process_key_states() {
    // find changes

    if (memcmp(prev_key_state, key_state, sizeof(key_state))) {

        enum controller_e controller;
        for (controller = CTLR_MASTER; controller < CTLR_COUNT; ++controller) {
            uint8_t row;
            for (row = 0; row < ROW_COUNT; ++row) {
                uint8_t xor = prev_key_state[controller][row] ^ key_state[controller][row];
                if (xor > 0) {
                    uint8_t col;
                    for (col = 0; col < COL_COUNT; ++col) {
                        if ((xor & (1 << col)) > 0) {
                            // key state at [row,col] has changed
                            const union keyseq_u *kout = get_current_mapped_key(controller, row, col);
                            enum key_change_e kchange = (key_state[controller][row] & (1 << col)) > 0 ?
                                KC_PRESS :
                                KC_RELEASE;
                            if (kout->type.type == KO_LEVEL_MOD) {
                                add_levelchange(row, controller, col, kchange);
                            } else {
                                add_keychange(row, controller, col, kchange);
                            }
                        }
                    } // col loop
                } // xor > 0
            } // row loop
        } // side loop

        memcpy(prev_key_state, key_state, sizeof(key_state));
    } // memcmp
}

// global functions

static inline void init() {
    uint8_t row, col;

    for (row = 0; row < ROW_COUNT; ++row) {
        init_row_io(row);
    }
    for (col = 0; col < COL_COUNT; ++col) {
        init_col_io(col);
    }

    clear_changed_keys();

    init_warn_led();

    uart_init(UART_BAUD_RATE);

    // Initialize the USB, and then wait for the host to set configuration.
    // If the Teensy is powered without a PC connected to the USB port,
    // this will wait forever.
    usb_init();
    while (!usb_configured()) {
        _delay_ms(5);
    };
    // Wait an extra second for the PC's operating system to load drivers
    // and do whatever it does to actually be ready for input
    _delay_ms(1000);

}

int main(void) {
    init();
    while (true) {
        update_warn_led();
        update_own_key_states();
#if (CONTROLLER == CTLR_MASTER)
        int rx_result = rx_keystates();
        if (rx_result == 0) {
            process_key_states();
        } else {
            warning(W_COMMUNICATION_FAILURE);
        }
#else
        tx_keystates();
#endif
    }
    return 0;
}
