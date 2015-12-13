/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.

   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

#ifndef USB_KEYBOARD_H_
#define USB_KEYBOARD_H_

// add definitions for additional scancodes we wanna use not included in teensy usb_keyboard.h

#include "../extern/SDL/SDL_scancode.h"

#define KEY_ISO_EXTRA SDL_SCANCODE_NONUSBACKSLASH

#define KEY_APP       SDL_SCANCODE_APPLICATION

#define KEY_REDO      SDL_SCANCODE_AGAIN
#define KEY_UNDO      SDL_SCANCODE_UNDO
#define KEY_CUT       SDL_SCANCODE_CUT
#define KEY_COPY      SDL_SCANCODE_COPY
#define KEY_PASTE     SDL_SCANCODE_PASTE
#define KEY_FIND      SDL_SCANCODE_FIND
#define KEY_SEARCH    SDL_SCANCODE_AC_SEARCH

#define KEY_FORWARD   SDL_SCANCODE_AC_FORWARD
#define KEY_BACK      SDL_SCANCODE_AC_BACK

// not yet mapped, but might nice to have in future:
// SDL_SCANCODE_SLEEP SDL_SCANCODE_CALCULATOR SDL_SCANCODE_MUTE


// XXX send errorcodes when errors occure
#define SCANCODE_ERR_ROLLOVER     1
#define SCANCODE_ERR_POST_FAIL    2
#define SCANCODE_ERR_UNDEFINED    3

// XXX use KEY_NUMBER/SDL_SCANCODE_NONUSHASH instead of KEY_BACKSLASH ?? (see comment on SDL_SCANCODE_NONUSHASH in SDL_scancode.h)


// fixme: move to usb_keyboard.c
#define MODIFIERS_NONE 0x00
#define KEY_NONE       0x00

void init_usb_keyboard();

void press_key(uint8_t key);
void release_key(uint8_t key);

void send_keys_usb();

#endif /* USB_KEYBOARD_H_ */
