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

#include "neomys.h"
#include "delay_wrapper.h"

#define KEYBOARD_KEYS_CNT 6
//(sizeof(keyboard_keys)/sizeof(keyboard_keys[0]))

static inline uint8_t *find_keyboard_key(uint8_t key);
static inline void inform_usb_keys();

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
        _delay_ms(5);
    };
    // Wait an extra second for the PC's operating system to load drivers
    // and do whatever it does to actually be ready for input
    _delay_ms(1000);
}


void press_key(uint8_t key) {
    uint8_t *pos = find_keyboard_key(key);
    if (pos != NULL) {
        inform(IL_ERR, SC_PROGERR_ALREADY_PRESSED);
        return;
    }
    pos = find_keyboard_key(KEY_NONE);
    if (pos == NULL) {
        inform(IL_WARN, SC_WARN_TOO_MANY_KEYS);
        return;
    }
    *pos = key;
}

void release_key(uint8_t key) {
    uint8_t *pos = find_keyboard_key(key);
    if (pos == NULL) {
        inform(IL_ERR, SC_PROGERR_NOT_PRESSED);
        return;
    }
    *pos = KEY_NONE;
}

void clear_all_keys() {
    for (uint8_t i = 0; i < KEYBOARD_KEYS_CNT; ++i) {
        keyboard_keys[i] = 0;
    }    
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
    inform_usb_keys();
    usb_keyboard_send();
}


static inline void inform_usb_keys() {
    if (info_uart(IL_DBG)) {
        inform(IL_DBG, SC_DBG_USB_KEYS);
        info_add(keyboard_modifier_keys);
        for (uint8_t i = 0; i < KEYBOARD_KEYS_CNT; ++i) {
            info_add(keyboard_keys[i]);
        }
    }
}
