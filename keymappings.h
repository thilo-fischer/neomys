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
    KO_PHANTOM = 0,    ///< key does not exist
    KO_PLAIN,          ///< translate hardware keypress to one single key press
    KO_PLAIN_X,        ///< translate hardware keypress to a key press that may be combined with the shift modifier // FIXME find name for this
    KO_SHIFT,
    KO_ALTGR,
    //KO_COMPOSE,
    KO_LEVEL_MOD,
    KO_LEVEL_MOD_X, // FIXME find appropriate name
} kout_t;

union keyout_u {
    struct {
        kout_t type;
    } type;
    struct {
        kout_t type;
        enum neo_levels_e level;
    } level_mod;
    struct {
        kout_t type;
        enum neo_levels_e level;
        uint8_t key;
    } level_mod_X; // FIXME find appropriate name
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

const union keyout_u keymap[KMM_COUNT][ROW_COUNT][2][COL_COUNT][LEVEL_COUNT];

inline const union keyout_u *get_mapped_key(enum keymapping_mode_e mode, enum controller_e controller, enum row_e row, uint8_t col, enum neo_levels_e level) {
    return &(keymap[mode][row][controller][col][level]);
}

#endif // _KEYMAPPINGS_H_
