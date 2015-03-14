/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.

   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

#ifndef SENDKEYS_H_
#define SENDKEYS_H_

#include "neomys.h"

void add_klt_charge(struct keyleveltranslations_s klt, enum key_change_e kchange);
void process_keyseqqueue();

#endif /* SENDKEYS_H_ */
