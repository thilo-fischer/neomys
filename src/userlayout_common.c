/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

/**
 * @file
 * Commenly used key functions. 
 */

#include "userlayout.h"

KF(nop) {}

KF(TODO) {
    // FIXME signal error state
}

KF(next_target_layout) {
    if (event == KS_PRESS) {
        ++target_layout;
        if (target_layout == TL_COUNT) {
            target_layout = TL_NEO;
        }
        inform(IL_INFO, SC_INFO_SWITCH_TARGET_LAYOUT);
        info_add(target_layout);
    }
}

KF(prev_target_layout) {
    if (event == KS_PRESS) {
        if (target_layout == TL_NEO) {
            target_layout = TL_COUNT;
        }
        --target_layout;
        inform(IL_INFO, SC_INFO_SWITCH_TARGET_LAYOUT);
        info_add(target_layout);
    }
}

