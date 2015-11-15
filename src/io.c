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


#if LOCAL_IO == LIO_GPIO
#  include "io_gpio.c"
#elif LOCAL_IO == LIO_SPI
#  include "io_spi.c"
#else
#  error Invalid configuration: Unknown LOCAL_IO.
#endif

// local function declarations

static void io_init_onboard_led();


// FIXME why are these symbols not known from iom32u4.h ?!?
#define DDRD  _SFR_IO8(0x0A)
#define PORTD _SFR_IO8(0x0B)
#define PIND  _SFR_IO8(0x09)

// function implementations

void io_init_onboard_led() {
    DDRD |= (1<<6);
}

void io_switch_onboard_led(bool on) {
    if (on == true) {
        PORTD |=  (1<<6);
    } else {
        PORTD &= ~(1<<6);
    }
}

void io_generic_init() {
    init_onboard_led();
}

