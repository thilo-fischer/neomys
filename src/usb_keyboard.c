/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.

   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

/**
 * @file
 * Send key events to host using the USB HID protocol.
 */

#include <stddef.h>

#include "teensy_codelib/usb_keyboard/usb_keyboard.h"

#include "usb_keyboard.h"

#include "ucontroller.h"
#include "debug.h"


#define KEYBOARD_KEYS_CNT 6
//(sizeof(keyboard_keys)/sizeof(keyboard_keys[0]))


static inline uint8_t *find_keyboard_key(uint8_t key);

void init_usb_keyboard() {
    keyboard_modifier_keys = 0x00;
    for (uint8_t i = 0; i < KEYBOARD_KEYS_CNT; ++i) {
        keyboard_keys[i] = 0x00;
    }
    
    // Initialize the USB, and then wait for the host to set configuration.
    // If the Teensy is powered without a PC connected to the USB port,
    // this will wait forever.
    usb_init();
    while (!usb_configured()) {
        uc_sleep(5);
    };
    // Wait an extra second for the PC's operating system to load drivers
    // and do whatever it does to actually be ready for input
    uc_sleep(1000);
}

dbg_define_msg(USB_ERR_ALREADY_PRESSED, 0xF0,
               "USB.ERROR: Already pressed: %02hhX", sizeof(uint8_t));

dbg_define_msg(USB_ERR_TOO_MANY_KEYS, 0xF1,
               "USB.ERROR: Too many keys, ignore %02hhX", sizeof(uint8_t));

dbg_define_msg(USB_ERR_NOT_PRESSED, 0xF2,
               "USB.ERROR: Inconsistent: not pressed: %02hhX", sizeof(uint8_t));

dbg_define_msg(USB_KEV, 0xF3,
               "USB %02hhX %s", sizeof(uint8_t), sizeof(char*));

dbg_define_msg(USB_SEND, 0xF4,
               "^USB mod%02hhX keys %02hhX %02hhX %02hhX %02hhX %02hhX %02hhX",
               sizeof(uint8_t),
               sizeof(uint8_t), sizeof(uint8_t), sizeof(uint8_t),
               sizeof(uint8_t), sizeof(uint8_t), sizeof(uint8_t)
               );

void press_key(uint8_t key) {
    uint8_t *pos = find_keyboard_key(key);
    if (pos != NULL) {
        dbg_error(USB_ERR_ALREADY_PRESSED, key);
        return;
    }
    pos = find_keyboard_key(KEY_NONE);
    if (pos == NULL) {
        dbg_warn(USB_ERR_TOO_MANY_KEYS, key);
        return;
    }
    dbg_debug(USB_KEV, key, "press");
    *pos = key;
}

void release_key(uint8_t key) {
    uint8_t *pos = find_keyboard_key(key);
    if (pos == NULL) {
        dbg_error(USB_ERR_NOT_PRESSED, key);
        return;
    }
    dbg_debug(USB_KEV, key, "release");
    *pos = KEY_NONE;
}

static inline uint8_t *find_keyboard_key(uint8_t key) {
    for (uint8_t i = 0; i < KEYBOARD_KEYS_CNT; ++i) {
        if (keyboard_keys[i] == key) {
            return &keyboard_keys[i];
        }
    }
    return NULL;
}

void send_keys_usb() {
  dbg_debug(USB_SEND, keyboard_modifier_keys,
            keyboard_keys[0], keyboard_keys[1], keyboard_keys[2],
            keyboard_keys[3], keyboard_keys[4], keyboard_keys[5]);
  usb_keyboard_send();
}
