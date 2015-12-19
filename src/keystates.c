/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

/**
 * @file
 */

#include "keystates.h"


#if 0
bool keystates_changed() {
  return memcmp(prev_key_states, key_states, sizeof(*key_states)) != 0;
}

bool keystates_changed_element(uint8_t element) {
  return memcmp(prev_key_states[element], key_states[element], sizeof(**key_states)) != 0;
}

uint8_t keystate_row_changes(uint8_t element, row_e row) {
  return prev_key_states[element][row] ^ key_states[element][row];
}

bool keystate_changed_col(uint8_t col, uint8_t row_changes) {
  return row_changes & (1 << col)) > 0;
}

void keystate_buffer() {
  // switch buffers
  kmatrix_rawdata_t *tmp = key_states_prev;
  key_states_prev = key_states;
  key_states = tmp;
}
#endif
