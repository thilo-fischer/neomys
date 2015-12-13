/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.

   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

#ifndef _KEYHANDLING_H_
#define _KEYHANDLING_H_

typedef enum {
   TL_NEO       = 0x00,  ///< Neo2 (http://www.neo-layout.org/)
   TL_DE        = 0x01,  ///< DIN 2137:2012-06 T1 (with dead keys)
   TL_DE_NODEAD = 0x02,
   TL_DE_APPLE  = 0x03,
   TL_US        = 0x04,  ///< ANSI-INCITS 154-1988
   //TL_US_APPLE,
   TL_COUNT
} target_layout_t;


typedef enum {
    KS_PRESS   = 0x01,
    KS_RELEASE = 0x00,
} keystate_t;



// FIXME neomys-specific

enum neo_levels_e {
    // As we use level values as array indices, LEVEL1 must have value 0x00. (Using value 0x01 for LEVEL1 would make reading binary data during debugging somewhat more intuitive, but makes using values for array indexing more error prone.)
    LEVEL1 = 0x00,
    LEVEL2,
    LEVEL3,
    LEVEL4,
    LEVEL4_MOUSE,
    LEVEL5,
    LEVEL6,
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

/**
 * Keyboard layout the USB host is configured to use.
 */
extern target_layout_t target_layout;


#endif // _KEYHANDLING_H_
