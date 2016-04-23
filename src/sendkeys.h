/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.

   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

#ifndef SENDKEYS_H_
#define SENDKEYS_H_

#include <stdint.h>
#include <stdbool.h>

#include "keyhandling.h"

typedef uint16_t keycode_t;

void progress_keyseq_queue();

void kev_plain(keycode_t key, keystate_t event);
void kev_w_shift(keycode_t key, keystate_t event);
void kev_w_altgr(keycode_t key, keystate_t event);
void kev_w_alt(keycode_t key, keystate_t event);
void kev_w_shift_alt(keycode_t key, keystate_t event);
void kev_level2(keycode_t key, keystate_t event);
void kev_level3(keycode_t key, keystate_t event);
void kev_level4(keycode_t key, keystate_t event);
void kev_allow_modifiers(keycode_t key, keystate_t event);
void kev_modifier(keycode_t key, keystate_t event);
void kev_virtual_modifier(keycode_t key, keystate_t event);
void kev_TODO();

#endif /* SENDKEYS_H_ */
