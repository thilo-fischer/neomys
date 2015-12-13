/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.

   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

#ifndef _IO_H_
#define _IO_H_

#include "neomys.h"

// implemented in io_*.c

void io_init();

void io_read_switches(kmatrix_rawdata_t destination);


// implemented in io.c

void io_switch_onboard_led(bool on);

// io-internal functions / XXX should not be part of public header

void io_generic_init();

#endif /* IO_H_ */
