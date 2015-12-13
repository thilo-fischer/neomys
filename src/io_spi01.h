/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.

   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

#ifndef _IO_SPI01_H_
#define _IO_SPI01_H_

#include "ucontroller.h"
#include "ucontroller_teensy-2.0.h" // FIXME

typedef struct {
  gpio_pin_t rst_pin;
  // TODO baudrate
} io_spi01_cfg_t;

#endif // _IO_SPI01_H_
