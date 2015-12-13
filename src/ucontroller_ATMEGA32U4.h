/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

/** @file
 * Implements the ucontroller.h API for the ATMEGA32U4 microcontroller (and probably other microcontrollers of the same family).
 */

#include "ucontroller.h"

/// the GPIO ports (groups of 8 GPIO pins) of this micro controller
typedef enum {
  IOPORT_B,
  IOPORT_C,
  IOPORT_D,
  IOPORT_E,
  IOPORT_F,
  IOPORT_COUNT
} ioport_t;

/// @see ucontroller.h:gpio_pin_t
struct gpio_pin_struct {
    ioport_t port;  ///< port the GPIO pin belongs to
    uint8_t bitpos; ///< bit position of the pin in its port
};


