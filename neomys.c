/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

#define __DELAY_BACKWARD_COMPATIBLE__ // FIXME -- temporarily to be able to build with (probably) inconsistent toolchain setup ...

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
    if (warn_cntdn == -1) {
        warn_cntdn = WARN_CNTDN_START - 1;
        switch (code) {
        case W_TOO_MANY_KEYS:
            current_pattern = WP_MEDIUM;
            break;
        case W_COMMUNICATION_FAILURE:
            current_pattern = WP_LONG;
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

static inline void update_warn_led() {
    if (warn_cntdn > 0) {
        switch_warn_led((((uint8_t) current_pattern) & (1<<(warn_cntdn/WARN_CYCLE_MULTIPLIER))) > 0);
        //switch_warn_led(true);
        --warn_cntdn;
    } else if (warn_cntdn == 0) {
        switch_warn_led(false);
        warn_cntdn = -1;
    }
}


// UART

// common baudrates: 1200, 2400, 4800, 9600, 14400, 19200, 28800, 38400, 57600, 115200
// Baud rates higher than 4800 seems to cause problems, signal looks pretty messed up in my signal analyser. Is it the UART driver, the Teensy or just my signal analyser that does not work correctly at higher baud rates? FIXME.
//#define UART_BAUD_RATE 38400
#define UART_BAUD_RATE 4800

// Test pattern for experimenting with other baud rates:
#if 0
    while (true) {
        uart_putchar(0xAA);
        _delay_ms(1);
        uart_putchar(0x00);
        _delay_ms(1);
        uart_putchar(0xAA);
        _delay_ms(1);
        uart_putchar(0xFF);
        _delay_ms(1);
        uart_putchar(0xAA);
        _delay_ms(1);
        uart_putchar(0x0F);
        _delay_ms(1);
        uart_putchar(0xAA);
        _delay_ms(1);
        uart_putchar(0xF0);
        _delay_ms(10);
    }
#endif


// global symbols

/**
 * Keyboard layout the USB host is configured to use.
 */
enum keylayout_e keymapping_mode_current = TKL_DE;
enum neo_levels_e level_current = LEVEL1;

const uint8_t cycle_delay = 20;

static inline const union keyseq_u *get_current_mapped_key_ptr(uint8_t controller, enum row_e row, uint8_t col) {
    return get_mapped_key_ptr(keymapping_mode_current, controller, row, col, level_current);
}

static inline const struct keyleveltranslations_s *get_current_mapped_klt_ptr(uint8_t controller, enum row_e row, uint8_t col) {
    return get_mapped_klt_ptr(keymapping_mode_current, controller, row, col);
}

static inline struct keyleveltranslations_s get_current_mapped_klt(uint8_t controller, enum row_e row, uint8_t col) {
    struct keyleveltranslations_s klt;
    uint8_t *ptr = (uint8_t *) get_current_mapped_klt_ptr(controller, row, col);
    uint8_t i;
    for (i = 0; i < sizeof(struct keyleveltranslations_s); ++i) {
        ((uint8_t *) &klt)[i] = pgm_read_byte(ptr + i);
    }
    return klt;
}

#if (CONTROLLER == CTLR_MASTER)
#  define UART_LOGLEVEL 1
#else
#  define UART_LOGLEVEL 0
#endif

#if (UART_LOGLEVEL == 0)
#define dbg_uarttx_byte(b)
#define dbg_uarttx_usb_keys()

#elif (UART_LOGLEVEL == 1)
void dbg_uarttx_byte(uint8_t b) {
    if (b > 0x1F) {
        uart_putchar(b);
    }
}
#define dbg_uarttx_usb_keys()

#else
void dbg_uarttx_byte(uint8_t b) {
    uart_putchar(b);
}
void dbg_uarttx_usb_keys() {
    uart_putchar(0xFF);
    uart_putchar(keyboard_modifier_keys);
    int i;
    for (i = 0; i < 6; ++i) {
        uart_putchar(keyboard_keys[i]);
    }
}

#endif

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
            key_state[CONTROLLER][row] |= (test_col(col) << col);
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
        // FIXME: need 3ms delay at 4800 bauds becase transmission of 1 byte takes about 2ms
        //_delay_ms(1);
        _delay_ms(3);
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
    if (uart_available() > 0) {
        discard_uart();
        return 4;        
    }
    return 0;
}

// key changes

enum key_change_e { // FIXME rename to key_state
    KC_PRESS   = 0,
    KC_RELEASE = 1,
};

enum key_change_e get_key_state(uint8_t controller, enum row_e row, uint8_t col) {
    return ((key_state[controller][row] & (1 << col)) > 0) ? KC_PRESS : KC_RELEASE;
}

void set_key_state(uint8_t controller, enum row_e row, uint8_t col, enum key_change_e state) {
    if (state == KC_PRESS) {
        key_state[controller][row] |=  (1 << col);
    } else {
        key_state[controller][row] &= ~(1 << col);
    }
}

struct key_id_s {
    uint8_t controller :1;
    uint8_t row : 3;
    uint8_t col : 3;
};

struct key_change_s {
    uint8_t controller; // :1;
    uint8_t row; // :3;
    uint8_t col; // :3;
    enum key_change_e change; // :1;
};

bool level_mod [LEVEL_COUNT] = { false };
bool level_lock[LEVEL_COUNT] = { false };

#define CHANGED_KEYS_CNT_MAX 8
struct key_change_s changed_keys[CHANGED_KEYS_CNT_MAX] = {{ 0 }}; // XXX initialization is debugging aid only
uint8_t keychange_cnt = 0;

void add_keychange(uint8_t row, uint8_t controller, uint8_t col, enum key_change_e change) {
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

    if (level_mod[l] && level_lock[l]) {
        if (l != LEVEL2 && level_mod[LEVEL2]) {
            l = LEVEL2;
        } else {
            l = LEVEL1;
        }
    }

    return l;
}

struct klt_changes_s {
    struct keyleveltranslations_s klt;
    enum key_change_e change;
};

struct klt_changes_s klt_charge[CHANGED_KEYS_CNT_MAX];
uint8_t klt_charge_cnt = 0;

void clear_klt_charge() {
    klt_charge_cnt = 0;
}

void add_klt_charge(struct keyleveltranslations_s klt, enum key_change_e kchange) {
    klt_charge[klt_charge_cnt].klt = klt;
    klt_charge[klt_charge_cnt].change = kchange;
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
struct key_seq_step_s key_seq_queue[KEY_SEQ_QUEUE_LENGTH] = {{0}};
size_t key_seq_queue_start = 0;
size_t key_seq_queue_end   = 0;

bool key_seq_queue_empty() {
    return key_seq_queue_start == key_seq_queue_end;
}

bool key_seq_queue_full() {
    if (key_seq_queue_start <= key_seq_queue_end) {
        return key_seq_queue_start == 0 && key_seq_queue_end == KEY_SEQ_QUEUE_LENGTH - 1;
    } else {
        return key_seq_queue_end == key_seq_queue_start - 1;
    }
}

void key_seq_queue_enqueue(const struct key_seq_step_s *step) {
    if (key_seq_queue_full()) {
        warning(W_TOO_MANY_KEYS);
        return;
    }
    key_seq_queue[key_seq_queue_end] = *step;
    ++key_seq_queue_end;
    if (key_seq_queue_end == KEY_SEQ_QUEUE_LENGTH) {
        key_seq_queue_end = 0;
    }
}

const struct key_seq_step_s NULL_STEP = { KC_PRESS, 0, 0}; // FIXME

struct key_seq_step_s key_seq_queue_dequeue() {
    if (key_seq_queue_empty()) {
        warning(W_PROGRAMMING_ERROR);
        return NULL_STEP; // FIXME
    }
    struct key_seq_step_s* result = &key_seq_queue[key_seq_queue_start];
    ++key_seq_queue_start;
    if (key_seq_queue_start == KEY_SEQ_QUEUE_LENGTH) {
        key_seq_queue_start = 0;
    }
    return *result;
}

#define KEY_ANY_SHIFT (KEY_SHIFT | KEY_LEFT_SHIFT | KEY_RIGHT_SHIFT)
uint8_t modifiers = 0;
bool modifiers_changed = false;

void process_klt_charge(enum neo_levels_e level) {
    uint8_t i;
    for (i = 0; i < klt_charge_cnt; ++i) {
        const union keyseq_u *seq = &klt_charge[i].klt.seq[level];
        switch (seq->type.type) {
        case KO_PHANTOM:
            // do nothing
            break;
        case KO_PLAIN:
            {
                struct key_seq_step_s step = { .change = klt_charge[i].change, .key = seq->single.key, .modifier = (modifiers & ~KEY_ANY_SHIFT)};
                key_seq_queue_enqueue(&step);
                break;
            }
        case KO_PLAIN_X:
            {
                struct key_seq_step_s step = { .change = klt_charge[i].change, .key = seq->single.key, .modifier = modifiers};
                key_seq_queue_enqueue(&step);
                break;
            }
        case KO_SHIFT:
            {
                struct key_seq_step_s step = { .change = klt_charge[i].change, .key = seq->single.key, .modifier = (modifiers | KEY_SHIFT)};
                key_seq_queue_enqueue(&step);
                break;
            }
        case KO_ALTGR:
            {
                struct key_seq_step_s step = { .change = klt_charge[i].change, .key = seq->single.key, .modifier = (modifiers | KEY_CTRL | KEY_ALT)}; // FIXME !! need AltGr !!
                key_seq_queue_enqueue(&step);
                break;
            }
        case KO_LEVEL_MOD:
            warning(W_PROGRAMMING_ERROR);
            break;
        case KO_MODIFIER:
        case KO_LEVEL_MOD_X:
            warning(W_PROGRAMMING_ERROR);
            break;
        default:
            warning(W_PROGRAMMING_ERROR);
        }
    }
}


void process_keychange(uint8_t row, uint8_t controller, uint8_t col) {
    const struct keyleveltranslations_s klt = get_current_mapped_klt(controller, row, col);
    enum key_change_e kchange = get_key_state(controller, row, col);
    if (klt.special == TT_LEVEL_MOD) {
        if (klt.seq[0].type.type == KO_LEVEL_MOD || klt.seq[0].type.type == KO_LEVEL_MOD_X) {
        enum neo_levels_e level = klt.seq[0].level_mod.level;
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
        }
        if (klt.seq[0].type.type == KO_MODIFIER || klt.seq[0].type.type == KO_LEVEL_MOD_X) {
            uint8_t key;
            if (klt.seq[0].type.type == KO_MODIFIER) {
                key = klt.seq[0].single.key;
            } else {
                key = klt.seq[0].level_mod_X.key;
            }
            if (kchange == KC_PRESS) {
                modifiers |=  key;
            } else {
                modifiers &= ~key;
            }
            modifiers_changed = true;
        }
    } else {
        add_klt_charge(klt, kchange);
    }
}


void process_key_states() {
    // find changes

    if (memcmp(prev_key_state, key_state, sizeof(key_state))) {

        clear_klt_charge();

        uint8_t controller;
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

        if (modifiers_changed == true) {
            struct key_seq_step_s step = { .change = KC_PRESS, .key = 0, .modifier = modifiers};
            key_seq_queue_enqueue(&step);            
            modifiers_changed = false;
        }

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

#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))

static inline void init() {
    CPU_PRESCALE(0);  // run at 16 MHz // TODO good idea?

    uint8_t row, col;

    for (row = 0; row < ROW_COUNT; ++row) {
        init_row_io(row);
    }
    for (col = 0; col < COL_COUNT; ++col) {
        init_col_io(col);
    }

    // initialize state variables
    clear_changed_keys();

    init_warn_led();

    // blink LED to destinct master from slave controller
#if (CONTROLLER == CTLR_MASTER)
    init_usb_keyboard();
    warning(W_MASTER); // FIXME function and symbol names
#else
    warning(W_SLAVE);  // FIXME function and symbol names
#endif

    uint8_t i;
    for (i = 0; i < 8; ++i) {
        update_warn_led();
        _delay_ms(cycle_delay);        
    }

    // Initialize UART only after blinking LED. The delay before UART initialization will reduce the chance of latch up effects (at least if both controllers get powered simultaneously).
    uart_init(UART_BAUD_RATE);
}

uint8_t *find_keyboard_key(uint8_t key) {
    uint8_t i;
    for (i = 0; i < 6; ++i) {
        if (keyboard_keys[i] == key) {
            return &keyboard_keys[i];
        }
    }
    return NULL;
}

int main(void) {
    init();
    while (true) {
        update_warn_led();
#if (CONTROLLER == CTLR_MASTER)
        int rx_result = rx_keystates();
        if (rx_result == 0) {
            update_own_key_states();
            process_key_states();
        } else {
            warning(W_COMMUNICATION_FAILURE);
        }

        if (! key_seq_queue_empty()) {
            struct key_seq_step_s step = key_seq_queue_dequeue();
            if (step.change == KC_PRESS) {
                uint8_t *free = find_keyboard_key(0);
                if (free == NULL) {
                    warning(W_TOO_MANY_KEYS);
                } else {
                    *free = step.key;
                }
            } else {
                uint8_t *pos = find_keyboard_key(step.key);
                if (pos == NULL) {
                    warning(W_PROGRAMMING_ERROR);
                } else {
                    *pos = 0;
                }
            }
            keyboard_modifier_keys = step.modifier;

            usb_keyboard_send();
        }
#else // ! (CONTROLLER == CTLR_MASTER)
        update_own_key_states();
        tx_keystates();
        // Slave induces the delay between loop iterations, master waits for slave in rx_keystates.
        _delay_ms(cycle_delay);
#endif // CONTROLLER == CTLR_MASTER

    }
    return 0;
}
