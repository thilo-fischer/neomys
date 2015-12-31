/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

/** @file
 * Implements the okey adaptation to run on the 2nd version of 2015 of the neomys keyboard hardware.
 */

#include "adaptation.h"
#include "io_spi01.h"

io_spi01_cfg_t neomys_io_cfg = {
  .rst_pin = { IOPORT_B, 0 },
  // TODO .baudrate = { ... }
};


void adp_await_next_cycle() {
    uc_sleep(10);
}

