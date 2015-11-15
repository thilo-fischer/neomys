/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.

   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

/**
 * @file
 * Drive and query the GPIO pins of the teensy boards.
 */

#include <avr/io.h>

#include "io.h"


// local function declarations

static void activate_row(uint8_t row);
static void deactivate_row(uint8_t row);
static char test_col(uint8_t col);


// FIXME why are these symbols not known from iom32u4.h ?!?
#define DDRB  _SFR_IO8(0x04)
#define PORTB _SFR_IO8(0x05)
#define PINB  _SFR_IO8(0x03)
#define DDRC  _SFR_IO8(0x07)
#define PORTC _SFR_IO8(0x08)
#define PINC  _SFR_IO8(0x06)
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

void activate_row(uint8_t row) {
    // output low
    *ROW_PORT_DDR [row] |=  (1 << ROW_PORT_BIT[row]);
}

void deactivate_row(uint8_t row) {
    // input (open collector)
    *ROW_PORT_DDR [row] &= ~(1 << ROW_PORT_BIT[row]);
}

// Data structures for addressing columns

volatile uint8_t * const COL_PORT_DDR [COL_COUNT] = { & DDRB, & DDRB, & DDRB, & DDRB, & DDRB, & DDRB, & DDRB, & DDRB };
volatile uint8_t * const COL_PORT_PORT[COL_COUNT] = { &PORTB, &PORTB, &PORTB, &PORTB, &PORTB, &PORTB, &PORTB, &PORTB };
volatile uint8_t * const COL_PORT_PIN [COL_COUNT] = { & PINB, & PINB, & PINB, & PINB, & PINB, & PINB, & PINB, & PINB };
const    uint8_t         COL_PORT_BIT [COL_COUNT] = {      0,      1,      2,      3,      4,      5,      6,      7 };

// Functions for addressing cols

void init_col_io(uint8_t col) {
    // set up input with pull up
    *COL_PORT_DDR [col] &= ~(1 << COL_PORT_BIT[col]);
    *COL_PORT_PORT[col] |=  (1 << COL_PORT_BIT[col]);
}

char test_col(uint8_t col) {
    // return 0 when the pin is high (pull up resistor => key not pressed), 1 when the pin is low (shut to ground => key pressed)
    return (*COL_PORT_PIN[col] & (1 << COL_PORT_BIT[col])) ? 0 : 1 ;
}

void io_init() {
  io_generic_init();
  
  uint8_t row, col;
  for (row = 0; row < ROW_COUNT; ++row) {
    init_row_io(row);
  }
  for (col = 0; col < COL_COUNT; ++col) {
    init_col_io(col);
  }
}

void io_read_switches(kmatrix_raw_t destination) {
  uint8_t row;
  for (row = 0; row < ROW_COUNT; ++row) {
    activate_row(row);
    // set all switches of that row to KS_RELEASE (KS_RELEASE == 0x00)
    key_states[CTLR_MASTER][row] = 0x00;
    uint8_t col;
    for (col = 0; col < COL_COUNT; ++col) {
      if (test_col(col) == 1)
	keystate_set(destination, row, col, KS_PRESS);
    }
    deactivate_row(row);
  }
}
