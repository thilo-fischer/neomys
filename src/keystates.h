/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

/**
 */

#ifndef _KEYSTATES_H_
#define _KEYSTATES_H_

#include <stdint.h>
#include <stdbool.h>

#if 0 // deprecated
bool keystates_changed();
bool keystates_changed_element(uint8_t element);
uint8_t keystate_row_changes(uint8_t element, row_e row);
bool keystate_changed_col(uint8_t col, uint8_t row_changes);

void keystate_buffer();
#endif 

#endif // _KEYSTATES_H_
