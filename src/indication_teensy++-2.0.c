/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

#include "indication.h"

// FIXME => #include <assert.h>

#include "ucontroller_teensy++-2.0.h"

typedef uint16_t ind_signal_pattern;

static const ind_signal_pattern patterns[IND_SIGS_COUNT] = {
  [IND_SIG_NONE]        = 0x0000,
  [IND_SIG_OKEY_INIT]   = 0xF0F0,
  [IND_SIG_DBG_MSG_BUF] = 0xFFFF,
};

static const ind_signal_pattern IND_PATTERN_NONE = 0x0000; // XXX => patterns[IND_SIG_NONE];
static ind_signal_pattern ind_current_pattern = 0x0000; // XXX => IND_PATTERN_NONE;


void ind_init() {
  uc_io_init_onboard_led();
}

bool ind_pattern_msb() {
  return ind_current_pattern & 0x8000;
}

void ind_cycle() {
  uc_io_switch_onboard_led(ind_pattern_msb());
  ind_current_pattern <<= 1;
}

void ind_signal(uint8_t signal) {
  // FIXME => assert(signal < IND_SIGS_COUNT);
  ind_current_pattern = patterns[signal];
}
