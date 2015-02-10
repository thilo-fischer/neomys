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
    *COL_PORT_PORT[col] |=  (1 << COL_PORT_BIT[col]);
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

enum key_change_e { // FIXME rename to key_state
    KC_PRESS   = 0,
    KC_RELEASE = 1,
};

enum key_change_e get_key_state(enum controller_e controller, enum row_e row, uint8_t col) {
    return ((key_states[controller][row] & (1 << col)) > 0) ? KC_PRESS : KC_RELEASE;
}

void set_key_state(enum controller_e controller, enum row_e row, uint8_t col, enum key_change_e state) {
    if (state == KC_PRESS) {
        key_states[controller][row] |=  (1 << col);
    } else {
        key_states[controller][row] &= ~(1 << col);
    }
}

struct key_id_s {
    enum controller_e controller :1;
    uint8_t row : 3;
    uint8_t col : 3;
};

struct key_change_s {
    enum controller_e controller; // :1;
    uint8_t row; // :3;
    uint8_t col; // :3;
    enum key_change_e change; // :1;
};

bool level_mod [LEVEL_COUNT] = { false };
bool level_lock[LEVEL_COUNT] = { false };

#define CHANGED_KEYS_CNT_MAX 8
struct key_change_s changed_keys[CHANGED_KEYS_CNT_MAX] = {{ 0 }}; // XXX initialization is debugging aid only
uint8_t keychange_cnt = 0;

#define MAX_MOD_KEYS_PER_LEVEL 4
struct key_id_s levelmod_keys[LEVEL_COUNT][MAX_MOD_KEYS_PER_LEVEL];

void update_levelmod_keys() {
    memset(levelmod_keys, 0xFF, sizeof(levelmod_keys));

    enum controller_e controller;
    for (controller = CTLR_MASTER; controller < CTLR_COUNT; ++controller) {
        uint8_t row;
        for (row = 0; row < ROW_COUNT; ++row) {
            uint8_t col;
            for (col = 0; col < COL_COUNT; ++col) {
                const struct keyleveltranslations_s *klt = get_mapped_klt(controller, row, col);
                if (klt->special == TT_LEVEL_MOD) {
                    enum neo_levels_e level = klt->seq[0].level_mod.level;
                    uint8_t i = 0;
                    while ((*(uint8_t *) &levelmod_keys[level][i]) == 0xFF) {
                        ++i;
                        if (i >= MAX_MOD_KEYS_PER_LEVEL) {
                            warning(W_PROGRAMMING_ERROR);
                            return;
                        }
                    }
                    levelmod_keys[level][i].controller = controller;
                    levelmod_keys[level][i].row = row;
                    levelmod_keys[level][i].col = col;
                }
            } // col loop
        } // row loop
    } // controller loop
}

void switch_layout(enum keylayout_e layout) {
    // ...
    update_levelmod_keys();
}

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

// FIXME
enum neo_levels_e determine_current_level() {
    enum neo_levels_e l = LEVEL1;

    if (level_lock[LEVEL3]) {
        if (level_lock[LEVEL4] || level_lock[LEVEL4_MOUSE]) {
            l = LEVEL6;
        } else if (level_lock[LEVEL2]) {
            l = LEVEL5;
        } else {
            l = LEVEL3;
        }
    } else if (level_lock[LEVEL4]) {
        l = LEVEL4;
    } else if (level_lock[LEVEL4_MOUSE]) {
        l = LEVEL4_MOUSE;
    } else if (level_lock[LEVEL2]) {
        l = LEVEL2;
    }

    if (level_mod[LEVEL3]) {
        if (level_mod[LEVEL4] || level_mod[LEVEL4_MOUSE]) {
            l = LEVEL6;
        } else if (level_mod[LEVEL2]) {
            l = LEVEL5;
        } else {
            l = LEVEL3;
        }
    } else if (level_mod[LEVEL4]) {
        l = LEVEL4;
    } else if (level_mod[LEVEL4_MOUSE]) {
        l = LEVEL4_MOUSE;
    } else if (level_mod[LEVEL2]) {
        l = LEVEL2;
    }

    if (level_mod[level] && level_lock[level]) {
        if (level != LEVEL2 && level_mod[LEVEL2]) {
            l = LEVEL2;
        } else {
            l = LEVEL1;
        }
    }

    return l;
}

const struct keyleveltranslations_s *klt_charge[CHANGED_KEYS_CNT_MAX];
uint8_t klt_charge_cnt = 0;

void clear_klt_charge() {
    klt_charge_cnt = 0;
}

void add_klt_charge(const struct keyleveltranslations_s *klt) {
    klt_charge[klt_charge_cnt] = klt;
    ++klt_charge_cnt;
    if (klt_charge_cnt >= CHANGED_KEYS_CNT_MAX) {
        warning(W_TOO_MANY_KEYS);
    }
}

struct key_seq_step_s {
    enum key_change_e change;
    uint8_t key;
    uint8_t modifier;
};

#define KEY_SEQ_QUEUE_LENGTH 32
struct key_seq_step_s key_seq_queue[KEY_SEQ_QUEUE_LENGTH] = {0};
size_t key_seq_queue_start = 0;
size_t key_seq_queue_end   = 0;

void key_seq_queue_enqueue(const struct key_seq_step_s *step) {
    if (key_seq_queue_end <= key_seq_queue_start) {
        key_seq_queue[end] = *step;
        ++key_seq_queue_end;
    }
}

struct key_seq_step_s step key_seq_queue_dequeue() {
    
}


void process_klt_charge(enum neo_levels_e level) {
    uint8_t i;
    for (i = 0; i < klt_charge_cnt; ++i) {
        const union keyseq_u *seq = &klt_charge[i]->seq[level];
        switch (seq->type) {
        case KO_PHANTOM:
            // do nothing
            break;
        case KO_PLAIN:
            seq->single.key;
            break;
        case KO_PLAIN_X:
            break;
        case KO_SHIFT:
            break;
        case KO_ALTGR:
            break;
        case KO_LEVEL_MOD:
            warning(W_PROGRAMMING_ERROR);
            break;
        case KO_LEVEL_MOD_X:
            seq->level_mod_X.key;
            break;
        default:
            warning(W_PROGRAMMING_ERROR);
        }
    }
}


void process_keychange(row, controller, col) {
    const struct keyleveltranslations_s *klt = get_mapped_klt(controller, row, col);
    if (klt->special == TT_LEVEL_MOD) {
        enum key_change_e kchange = get_key_state(controller, row, col);
        enum neo_levels_e level = klt->seq[0].level_mod.level;
        switch (level) {
        case LEVEL4: // XXX
            if (kchange == KC_PRESS) {
                if (level_mod[LEVEL4_MOUSE] == true) {
                    level_lock[LEVEL4_MOUSE] = true;
                }
                level_mod [level] = true;
            } else {
                level_mod[level] = !level_mod[level];
            }
            break;
        case LEVEL4_MOUSE: // XXX
            if (kchange == KC_PRESS) {
                if (level_mod[LEVEL4] == true) {
                    level_lock[LEVEL4] = true;
                }
                level_mod [level] = true;
            } else {
                level_mod[level] = !level_mod[level];
            }
            break;
        default:
            if (kchange == KC_PRESS) {
                if (level_mod[level] == true) {
                    level_lock[level] = !level_lock[level];
                    level_mod [level] = false;
                } else {
                    level_mod [level] = true;
                }
            } else {
                level_mod[level] = !level_mod[level];
            }
        }
        if (klt->seq[0].type == LEVEL_MOD_X) {
            add_klt_charge(klt);
        }
    } else {
        add_klt_charge(klt);
    }
}


void process_key_states() {
    // find changes

    if (memcmp(prev_key_state, key_state, sizeof(key_state))) {

        clear_klt_charge();

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
                            process_keychange(row, controller, col);
                        }
                    } // col loop
                } // xor > 0
            } // row loop
        } // controller loop

        enum neo_levels_e level = determine_current_level();
        process_klt_charge(level);

        memcpy(prev_key_state, key_state, sizeof(key_state));
    } // memcmp
}

static inline void init_usb_keyboard() {
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

// global functions

static inline void init() {
    uint8_t row, col;

    for (row = 0; row < ROW_COUNT; ++row) {
        init_row_io(row);
    }
    for (col = 0; col < COL_COUNT; ++col) {
        init_col_io(col);
    }

    update_levelmod_keys();

    clear_changed_keys();

    init_warn_led();

    uart_init(UART_BAUD_RATE);

	init_usb_keyboard();
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
