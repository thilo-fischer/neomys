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

#ifndef _KEYMAPPINGS_H_
#define _KEYMAPPINGS_H_

#include "neomys.h"

enum keylayout_e {
   TKL_DE,        ///< DIN 2137:2012-06 T1 (with dead keys)
//   TKL_NEO,       ///< Neo2 (http://www.neo-layout.org/)
//   TKL_US,        ///< ANSI-INCITS 154-1988
//   TKL_DE_APPLE,
//   TKL_US_APPLE,
   TKL_COUNT
};

typedef enum keyseq_type_e {
    KO_PHANTOM = 0,    ///< key does not exist
    KO_PLAIN,          ///< translate hardware key press to one single key press
    KO_PLAIN_X,        ///< translate hardware key press to a key press that may be combined with the shift modifier // FIXME find name for this
    KO_SHIFT,          ///< translate hardware key press to a SHIFT+key press
    KO_ALTGR,          ///< translate hardware key press to a AltGr+key press
    KO_LEVEL_MOD,      ///< This key operates as a level modifier and will not be sent to the USB host if a different target layout than Neo2 is being used.
    KO_LEVEL_MOD_X,    ///< This key operates as a level modifier that will be sent to the USB host if combined with KO_PLAIN_X even if a different target layout than Neo2 is being used. (This applies to the SHIFT key.) // FIXME find appropriate name
    KO_MODIFIER,      ///< A modifier key that does not have any effect on the current level.
} kseq_type_t;

union keyseq_u {
    struct {
        kseq_type_t type;
    } type;
    struct {
        kseq_type_t type;
        enum neo_levels_e level;
    } level_mod;
    struct {
        kseq_type_t type;
        enum neo_levels_e level;
        uint8_t key;
    } level_mod_X; // FIXME find appropriate name
    struct {
        kseq_type_t type;
        uint8_t key;
    } single;
    struct {
        kseq_type_t  dead_type;
        uint8_t dead_key;
        kseq_type_t  main_type;
        uint8_t main_key;
    } compose;
};

enum translation_type_e {
    TT_DEFAULT = 0,
    TT_IGNORE_SHIFTLOCK, ///< Ignore if level2 is locked, i.e. use level1 key seq even if level2 lock is active. E.g. produce 6 instead of $ if level2 lock is active.
    // FIXME merge TT_LEVEL_MOD and TT_MODIFIER !!
    TT_LEVEL_MOD,        ///< Key is level modifier key -> won't be translated and (except for level_mod_X keys) won't be communicated to USB host at all if a different target layout than Neo2 is being used.
    TT_MODIFIER,         ///< A modifier key that does not have any effect on and is not effected by the current level.
};

struct keyleveltranslations_s {
    union keyseq_u seq[LEVEL_COUNT];
    enum translation_type_e special; // will be initialized with 0 == TT_DEFAULT if not given explicitly
};

const struct keyleveltranslations_s keymap[TKL_COUNT][ROW_COUNT][2][COL_COUNT];

inline const union keyseq_u *get_mapped_key_ptr(enum keylayout_e mode, uint8_t controller, enum row_e row, uint8_t col, enum neo_levels_e level) {
    return &(keymap[mode][row][controller][col].seq[level]);
}

inline const struct keyleveltranslations_s *get_mapped_klt_ptr(enum keylayout_e mode, uint8_t controller, enum row_e row, uint8_t col) {
    return &(keymap[mode][row][controller][col]);
}

#endif // _KEYMAPPINGS_H_
