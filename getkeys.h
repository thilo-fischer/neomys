/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.

   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

#ifndef GETKEYS_H_
#define GETKEYS_H_

#include "neomys.h"

enum neo_levels_e {
    LEVEL1,
    LEVEL2,
    LEVEL3,
    LEVEL4,
    LEVEL4_MOUSE,
    LEVEL5,
    LEVEL6,
    LEVEL_COUNT
};

enum key_change_e { // FIXME rename to key_state
    KC_PRESS   = 0,
    KC_RELEASE = 1,
};

struct key_id_s {
    uint8_t controller :1;
    uint8_t row : 3;
    uint8_t col : 3;
};

struct key_change_s {
    uint8_t controller; // :1;
    uint8_t row; // :3;
    uint8_t col; // :3;
    enum key_change_e change; // :1;
};


void update_own_key_states();
void process_key_states();

#endif /* GETKEYS_H_ */
