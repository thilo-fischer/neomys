/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.

   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

#ifndef _KEYHANDLING_H_
#define _KEYHANDLING_H_


typedef enum {
    KS_PRESS   = 0x01,
    KS_RELEASE = 0x00,
    KS_MODCHANGE = 0x04,
} keystate_t;

#endif // _KEYHANDLING_H_
