/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

/**
 */

#ifndef _KEYSTATES_H_
#define _KEYSTATES_H_

enum row_e {
  ROW_VIRTUAL_ID = 0,
  ROW_NUM        = 1,
  ROW_TOP        = 2,
  ROW_HOME       = 3,
  ROW_BTM        = 4,
  ROW_SPACE      = 5,
  ROW_EXTRA_A    = 6,
  ROW_EXTRA_B    = 7,
  ROW_COUNT
};

/// Number of columns a key matrix may have at most.
/// This is not a configuration value one may tune,
/// it is just to give a semantically relevant name to
/// the number of bits in a byte.
/// Implementation requires this values must be less than
/// or equal to the number of bits in a uint8_t.
#define COL_COUNT 8

typedef uint8_t kmatrix_raw_t[ROW_COUNT];
typedef kmatrix_raw_t allkeys_raw_t[MAX_ELEMENT_COUNT];


#if 0 // deprecated
keystate_t get_keystate(uint8_t element, enum row_e row, uint8_t col);
void set_keystate(uint8_t element, enum row_e row, uint8_t col, keystate_t state);
#endif

keystate_t keystate_get(const kmatrix_raw_t from, enum row_e row, uint8_t col);
void keystate_set(kmatrix_raw_t target, enum row_e row, uint8_t col, keystate_t state);

bool keystates_changed();
bool keystates_changed_element(uint8_t element);
uint8_t keystate_row_changes(uint8_t element, row_e row);
bool keystate_changed_col(uint8_t col, uint8_t row_changes);

void keystate_buffer();

#endif // _KEYSTATES_H_
