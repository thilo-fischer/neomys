/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.

   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

#ifndef _KEYMATRIX_H_
#define _KEYMATRIX_H_

#include "neomys.h"

#define MATRIX_MAX_COUNT 4

enum row_e {
  ROW_VIRTUL_ID = 0,
  ROW_NUM       = 1,
  ROW_TOP       = 2,
  ROW_HOME      = 3,
  ROW_BTM       = 4,
  ROW_SPACE     = 5,
  ROW_EXTRA_A   = 6,
  ROW_EXTRA_B   = 7,
  ROW_COUNT
};

#define COL_COUNT 8

typedef uint8_t keymatrix_t[ROW_COUNT];

keymatrix_t keystates[MATRIX_MAX_COUNT];

#endif // _KEYMATRIX_H_
