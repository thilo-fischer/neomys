/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

#ifndef _KEYMAPPINGS_H_
#define _KEYMAPPINGS_H_

#include "neomys.h"

enum keymapping_mode_e {
   KMM_DE,
   KMM_NEO,
   KMM_US,
   KMM_DE_APPLE,
   KMM_US_APPLE,
   KMM_COUNT
};

typedef enum keyout_type_e {
    KO_PHANTOM = 0,
    KO_PLAIN,
    KO_PLAIN_X, // key may be combined with shift key // FIXME find name for this
    KO_SHIFT,
    KO_ALTGR,
    //KO_COMPOSE,
    KO_MOD_SHIFT_L,
    KO_MOD_SHIFT_R,
    KO_MOD3_L,
    KO_MOD3_R,
    KO_MOD4_L,
    KO_MOD4_MOUSE,
} kout_t;

union keyout_u {
    struct {
        kout_t type;
    } type;
    struct {
        kout_t type;
        uint8_t key;
    } single;
    struct {
        kout_t  dead_type;
        uint8_t dead_key;
        kout_t  main_type;
        uint8_t main_key;
    } compose;
};

const union keyout_u keymap[KMM_COUNT][LEVEL_COUNT][ROW_COUNT][2][COL_COUNT];

inline union keyout_u get_mapped_key(enum keymapping_mode_e mode, enum neo_levels_e level, enum row_e row, uint8_t side, uint8_t col) {
    return keymap[mode][level][row][side][col];
}

#endif // _KEYMAPPINGS_H_
