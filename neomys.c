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

inline void init_row(uint8_t row) {
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

inline void init_col(uint8_t col) {
    // set up input with pull up
    *COL_PORT_DDR [col] &= ~(1 << COL_PORT_BIT[col]);
    *COL_PORT_PORT[col] &=  (1 << COL_PORT_BIT[col]);
}

inline char test_col(uint8_t col) {
    return (*COL_PORT_PIN[col] &  (1 << COL_PORT_BIT[col])) ? 1 : 0 ;
}

// UART

const uint32_t UART_BAUD_RATE = 9600;

// global symbols

enum kb_out_e kb_out = KB_DE;


// global functions

inline void init() {
    uint8_t row, col;

    uart_init(UART_BAUD_RATE);

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

void process_states() {
    if (memcmp(prev_row_state, row_state, 2*ROW_SPACE*sizeof(row_state[0][0]))) {

        for (row = 0; row < ROW_COUNT; ++row) {
            uint8_t col;
            for (col = 0; col < COL_COUNT; ++col) {
                
            }
        }
        
        memcpy(prev_row_state, row_state, 2*ROW_SPACE*sizeof(row_state[0][0]));
    }
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
