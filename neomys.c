/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "usb_keyboard.h"

// Data structures for addressing rows

enum row_e {
    ROW_FUNC,
    ROW_NUM,
    ROW_TOP,
    ROW_HOME,
    ROW_BTM,
    ROW_SPACE,
    ROW_COUNT
};

const int ROW_PORT_DDR [ROW_COUNT] = {  DDRF,  DDRF,  DDRF,  DDRF,  DDRF,  DDRF };
const int ROW_PORT_PORT[ROW_COUNT] = { PORTF, PORTF, PORTF, PORTF, PORTF, PORTF };
const int ROW_PORT_PIN [ROW_COUNT] = {  PINF,  PINF,  PINF,  PINF,  PINF,  PINF };
const int ROW_PORT_BIT [ROW_COUNT] = {     0,     1,     4,     5,     6,     7 };

// Functions for addressing rows

inline void init_row(uint8_t row) {
    // set up "open collector"
    ROW_PORT_DDR [row] &= ~(1 << ROW_PORT_BIT[row]);
    ROW_PORT_PORT[row] &= ~(1 << ROW_PORT_BIT[row]);
}

inline void activate_row(uint8_t row) {
    // output low
    ROW_PORT_DDR [row] |=  (1 << ROW_PORT_BIT[row]);
}

inline void deactivate_row(uint8_t row) {
    // input (open collector)
    ROW_PORT_DDR [row] &= ~(1 << ROW_PORT_BIT[row]);
}

// Data structures for addressing columns

#define COL_COUNT 8

const int COL_PORT_DDR [COL_COUNT] = {  DDRB,  DDRB,  DDRB,  DDRB,  DDRB,  DDRB,  DDRB,  DDRB };
const int COL_PORT_PORT[COL_COUNT] = { PORTB, PORTB, PORTB, PORTB, PORTB, PORTB, PORTB, PORTB };
const int COL_PORT_PIN [COL_COUNT] = {  PINB,  PINB,  PINB,  PINB,  PINB,  PINB,  PINB,  PINB };
const int COL_PORT_BIT [COL_COUNT] = {     0,     1,     2,     3,     4,     5,     6,     7 };

// Functions for addressing cols

inline void init_col(uint8_t col) {
    // set up input with pull up
    COL_PORT_DDR [col] &= ~(1 << COL_PORT_BIT[col]);
    COL_PORT_PORT[col] &=  (1 << COL_PORT_BIT[col]);
}

inline char test_col(uint8_t col) {
    return (COL_PORT_PIN[col] &  (1 << COL_PORT_BIT[col])) ? 1 : 0 ;
}

// global symbols

enum kb_out_e {
   KB_DE,
   KB_NEO,
   KB_US,
   KB_DE_APPLE,
   KB_US_APPLE,
   KB_COUNT
};

enum kb_out_e kb_out = KB_DE;

enum neo_levels_e {
    LEVEL1,
    LEVEL2,
    LEVEL3,
    LEVEL4,
    LEVEL5,
    LEVEL6,
    LEVEL_COUNT
};

typedef enum keymapping_type_e {
    KMT_PHANTOM = 0,
    KMT_SINGLE,
    KMT_SHIFT,
    KMT_ALTGR,
    KMT_COMPOSE,
} kmap_t;

union keymapping_u {
    struct {
        kmap_t type;
    } type;
    struct {
        kmap_t type;
    } phantom;
    struct {
        kmap_t type;
        uint8_t key;
    } single;
    struct {
        kmap_t type;
        uint8_t key;
    } shift;
    struct {
        kmap_t type;
        uint8_t key;
    } altgr;
    struct {
        kmap_t type;
        uint8_t dead_key;
        uint8_t main_key;
    } compose;
};

const union keymapping_u keymapping[KB_COUNT][LEVEL_COUNT][ROW_COUNT][2][COL_COUNT] = {
    // KB_DE
    {
        // DE level1
        {
            // DE level1 row func
            {
                // left
                {
                    /* 0 */ { .single = {KMT_SINGLE, KEY_F1}},
                    /* 1 */ { .single = {KMT_SINGLE, KEY_F2}},
                    /* 2 */ { .single = {KMT_SINGLE, KEY_F3}},
                    /* 3 */ { .single = {KMT_SINGLE, KEY_F4}},
                    /* 4 */ { .single = {KMT_SINGLE, KEY_F5}},
                    /* 5 */ { .single = {KMT_SINGLE, KEY_F6}},
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
                // right
                {
                    /* 0 */ { .single = {KMT_SINGLE, KEY_F7}},
                    /* 1 */ { .single = {KMT_SINGLE, KEY_F8}},
                    /* 2 */ { .single = {KMT_SINGLE, KEY_F9}},
                    /* 3 */ { .single = {KMT_SINGLE, KEY_F10}},
                    /* 4 */ { .single = {KMT_SINGLE, KEY_F11}},
                    /* 5 */ { .single = {KMT_SINGLE, KEY_F12}},
                    // remaining will be initialzed with zeros (=> KMT_PHANTOM)
                },
            },
            // DE level1 row num
            {
            },
            // DE level1 row top
            {
            },
            // DE level1 row home
            {
            },
            // DE level1 row btm
            {
            },
            // DE level1 row space
            {
            },
        },
        // DE level2
        {
        },
        // DE level3
        {
        },
        // DE level4
        {
        },
        // all remaining levels will be initialzed with zeros (=> KMT_PHANTOM)
    },
   // KB_NEO
   // KB_US
   // KB_DE_APPLE
   // KB_US_APPLE
};

// global functions

inline void init() {
    uint8_t row, col;
    for (row = 0; row < ROW_COUNT; ++row) {
        init_row(row);
    }
    for (col = 0; col < COL_COUNT; ++col) {
        init_col(col);
    }
}

#define SIDE_LEFT  0
#define SIDE_RIGHT 1

enum controller_t {
    CTLR_MASTER,
    CTLR_SLAVE
};

char row_state[2][ROW_COUNT];
char prev_row_state[2][ROW_COUNT];

// shall be defined by compiler switch (-DSIDE=SIDE_xyz)
//#define SIDE SIDE_LEFT
//#define SIDE SIDE_RIGHT

#if (SIDE == SIDE_LEFT)
#  define CONTROLLER CTLR_MASTER
#else
#  define CONTROLLER CTLR_SLAVE
#endif

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
    rx_slave(row_state[CTLR_SLAVE]);
    process_states();
#else
    tx_states(row_state[CONTROLLER]);
#endif
    return 0;
}

void process_states() {
    if (memcmp(prev_row_state, row_state, 2*ROW_SPACE*sizeof(row_state[0][0]))) {
        memcpy(prev_row_state, row_state, 2*ROW_SPACE*sizeof(row_state[0][0]));
    }
}
