/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

#ifndef _KEYMAPPINGS_H_
#define _KEYMAPPINGS_H_

#include "neomys.h"

enum kb_out_e {
   KB_DE,
   KB_NEO,
   KB_US,
   KB_DE_APPLE,
   KB_US_APPLE,
   KB_COUNT
};

typedef enum keymapping_type_e {
    KMT_PHANTOM = 0,
    KMT_PLAIN,
    KMT_PLAIN_X, // key may be combined with shift key // FIXME find name for this
    KMT_SHIFT,
    KMT_ALTGR,
    // KMT_COMPOSE,
    KMT_MOD_SHIFT_L,
    KMT_MOD_SHIFT_R,
    KMT_MOD3_L,
    KMT_MOD3_R,
    KMT_MOD4_L,
    KMT_MOD4_MOUSE,
} kmap_t;

union keymapping_u {
    struct {
        kmap_t type;
    } type;
    struct {
        kmap_t type;
        uint8_t key;
    } single;
    struct {
        kmap_t  dead_type;
        uint8_t dead_key;
        kmap_t  main_type;
        uint8_t main_key;
    } compose;
};

const union keymapping_u keymapping[KB_COUNT][LEVEL_COUNT][ROW_COUNT][2][COL_COUNT];


#endif // _KEYMAPPINGS_H_
