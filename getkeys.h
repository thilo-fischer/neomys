/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.

   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

#ifndef GETKEYS_H_
#define GETKEYS_H_

#include "neomys.h"

struct keyevent_b {
    keystate_t event :1;
    uint8_t controller :1;
    uint8_t row :3;
    uint8_t col :3;
};


void update_own_key_states();
void process_key_states();

#endif /* GETKEYS_H_ */
