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
#include "keyhandling.h"


typedef void (*keyfunc_t)(target_layout_t tl, keystate_t event);

typedef enum {
    KT_DUMB, // fixme -- rename: PHANTOM
    KT_PLAIN,
    KT_IGNORE_SHIFTLOCK,
    KT_IGNORE_LEVEL,
    KT_LEVELMOD,
} keytype_t;

typedef struct {
    keytype_t type;
    keyfunc_t kf[LEVEL_COUNT];
} keyrecord_t;


const keyrecord_t *get_keyrecord(uint8_t controller, uint8_t row, uint8_t col);


#endif // _KEYMAPPINGS_H_
