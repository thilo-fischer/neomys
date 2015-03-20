/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.

   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

#ifndef SENDKEYS_H_
#define SENDKEYS_H_

#include "neomys.h"
#include "keyhandling.h"

void progress_keyseq_queue();

void kev_plain(uint8_t key, keystate_t event);
void kev_w_shift(uint8_t key, keystate_t event);
void kev_w_altgr(uint8_t key, keystate_t event);
void kev_w_alt(uint8_t key, keystate_t event);
void kev_w_shift_alt(uint8_t key, keystate_t event);
void kev_level2(uint8_t key, keystate_t event);
void kev_level3(uint8_t key, keystate_t event);
void kev_level4(uint8_t key, keystate_t event);
void kev_allow_modifiers(uint8_t key, keystate_t event);
void kev_modifier(uint8_t key, keystate_t event);
void kev_virtual_modifier(uint8_t key, keystate_t event);
void kev_TODO();

#endif /* SENDKEYS_H_ */
