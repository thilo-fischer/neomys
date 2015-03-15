/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.

   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

#ifndef _KEYHANDLING_H_
#define _KEYHANDLING_H_

typedef enum {
   TL_NEO,       ///< Neo2 (http://www.neo-layout.org/)
   TL_DE,        ///< DIN 2137:2012-06 T1 (with dead keys)
   TL_DE_NODEAD,
   //TL_DE_APPLE,
   TL_US,        ///< ANSI-INCITS 154-1988
   //TL_US_APPLE,
   TL_COUNT
} target_layout_t;


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

enum neo_level_modifiers_e {
    LM2_L = 0x01,
    LM2_R = 0x02,
    LM3_L = 0x04,
    LM3_R = 0x08,
    LM4_L = 0x10,
    LM4_R = 0x20,
};


extern enum neo_levels_e locked_level;
extern uint8_t level_modifiers;


#endif // _KEYHANDLING_H_
