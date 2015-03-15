/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.

   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

#ifndef _KEYHANDLING_H_
#define _KEYHANDLING_H_

typedef enum {
    KS_PRESS,
    KS_RELEASE,
} keystate_t;


enum neo_levels_e {
    LEVEL1         = 0x01,
    LEVEL2         = 0x02,
    LEVEL3         = 0x03,
    LEVEL4         = 0x04,
    LEVEL4_MOUSE   = 0x14,
    LEVEL5         = 0x05,
    LEVEL6         = 0x06,
    LEVEL_COUNT
};

extern enum neo_levels_e locked_level;

enum neo_level_modifiers_e {
    LM2_L = 0x01,
    LM2_R = 0x02,
    LM3_L = 0x04,
    LM3_R = 0x08,
    LM4_L = 0x10,
    LM4_R = 0x20,
};

extern uint8_t level_modifiers;



#endif // _KEYHANDLING_H_
