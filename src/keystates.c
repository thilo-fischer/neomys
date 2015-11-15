/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

/**
 * @file
 */

#include "keystates.h"


allkeys_raw_t key_state_buffers[2] = {{{0}}, {{0}}};
allkeys_raw_t *key_states      = key_state_buffers[0];
allkeys_raw_t *prev_key_states = key_state_buffers[1];

#if 0 // deprecated
keystate_t get_keystate(uint8_t element, enum row_e row, uint8_t col) {
    return ((key_states[element][row] & (1 << col)) > 0) ? KS_PRESS : KS_RELEASE;
}

void set_keystate(uint8_t element, enum row_e row, uint8_t col, keystate_t state) {
    if (state == KS_PRESS) {
        key_states[element][row] |=  (1 << col);
    } else {
        key_states[element][row] &= ~(1 << col);
    }
}
#endif

keystate_t keystate_get(const kmatrix_raw_t from, enum row_e row, uint8_t col) {
    return ((from[row] & (1 << col)) > 0) ? KS_PRESS : KS_RELEASE;
}

void keystate_set(kmatrix_raw_t target, enum row_e row, uint8_t col, keystate_t state) {
    if (state == KS_PRESS) {
        target[row] |=  (1 << col);
    } else {
        target[row] &= ~(1 << col);
    }
}

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
