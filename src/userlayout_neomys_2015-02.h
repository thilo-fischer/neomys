/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

/**
 * @file Declares the user layout symbols of the okey adaptation to
 * run on the 2nd version of 2015 of the neomys keyboard hardware.
 */

#ifndef _USERLAYOUT_NEOMYS_2015_02_H_
#define _USERLAYOUT_NEOMYS_2015_02_H_

enum level_enum {
    LVL_DEFAULT =  0, ///< the default level active when no level modifiers are active
    LVL_SHIFT   =  1, ///< the level associated with the shift modifier
    LVL_3       =  2, ///< Neo2 level 3
    LVL_4       =  4, ///< Neo2 level 4
    LVL_4M      =  8, ///< neomys special mouse level derived from Neo2 level 4
    LVL_5       = 16, ///< Neo2 level 5
    LVL_6       = 32, ///< Neo2 level 6
};

#include "userlayout.h"

extern const userlayout_t ulo_neomys_left;
extern const userlayout_t ulo_neomys_right;

extern level_t g_effective_levels[]; // XXX move elsewhere

#endif // _USERLAYOUT_NEOMYS_2015_02_H_
