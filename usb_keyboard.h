/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.

   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

#ifndef USB_KEYBOARD_H_
#define USB_KEYBOARD_H_

// fixme: move to usb_keyboard.c
#define MODIFIERS_NONE 0x00
#define KEY_NONE       0x00

void init_usb_keyboard();

void press_key(uint8_t key);
void release_key(uint8_t key);

void send_keys_usb();

#endif /* USB_KEYBOARD_H_ */
