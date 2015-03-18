/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.

   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

#ifndef SENDKEYS_H_
#define SENDKEYS_H_

#include "neomys.h"
#include "keyhandling.h"

void keyseq_queue_progress();

void kev_plain(uint8_t key, keystate_t event);
void kev_w_shift(uint8_t key, keystate_t event);
void kev_w_altgr(uint8_t key, keystate_t event);
void kev_level2(uint8_t key, keystate_t event);
void kev_level3(uint8_t key, keystate_t event);
void kev_allow_modifiers(uint8_t key, keystate_t event);
void kev_modifier(uint8_t key, keystate_t event);
void kev_TODO();

// note: kev_virtual_modifier is just an alias for kev_allow_modifiers defined in keytranslation.h

#endif /* SENDKEYS_H_ */
