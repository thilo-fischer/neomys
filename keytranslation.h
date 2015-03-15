/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

/**
 * @file
 * Defines those symbols used to specify the key presses (or sequences of key presses) to be sent
 * to the USB host as reaction to the key presses done on the Neomys keyboard.
 *
 * Key presses on the Neomys keyboard can be translated to key presses (or sequences of key presses)
 * that will make the USB host the Neomys is connected to (e.g. a PC) act as if it uses the Neo2
 * keyboard layout even if it uses a different layout, e.g. DE ,
 * US [TODO] or US-international [TODO]. The Neomys software running on
 * the keyboard will take care of these translations, the USB host does not need any special
 * modifications or software. This file defines the symbols used to specify the necessary
 * translation tables in keymappings.c.
 */

#ifndef _KEYTRANSLATION_H_
#define _KEYTRANSLATION_H_

#include "neomys.h"
#include "getkeys.h"


typedef enum {
   TL_NEO,       ///< Neo2 (http://www.neo-layout.org/)
   TL_DE,        ///< DIN 2137:2012-06 T1 (with dead keys)
   TL_DE_NODEAD,
   //TL_DE_APPLE,
   TL_US,        ///< ANSI-INCITS 154-1988
   //TL_US_APPLE,
   TL_COUNT
} target_layout_t;



typedef void (*keyfunc_t)();


keyfunc_t get_keyfunc();



inline const union keyseq_u *get_mapped_key_ptr(enum keylayout_e mode, uint8_t controller, enum row_e row, uint8_t col, enum neo_levels_e level) {
    return &(keymap[mode][row][controller][col].seq[level]);
}

inline const struct keyleveltranslations_s *get_mapped_klt_ptr(enum keylayout_e mode, uint8_t controller, enum row_e row, uint8_t col) {
    return &(keymap[mode][row][controller][col]);
}

#endif // _KEYMAPPINGS_H_
