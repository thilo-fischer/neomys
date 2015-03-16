/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.

   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

#include <stddef.h>

#include "sendkeys.h"

#include "usb_keyboard.h"

#include "teensy_codelib/usb_keyboard/usb_keyboard.h" // FIXME: move all code dependent on this file to usb_keyboard.c

// internal symbols

uint8_t modifiers_current_in  = 0x00;

struct keyseq_step_s {
    uint8_t key;
    uint8_t modifiers;
    keystate_t change;
};

#define KEYSEQ_QUEUE_LENGTH 32
struct keyseq_step_s keyseq_queue[KEYSEQ_QUEUE_LENGTH] /*= {{0}}*/;
size_t keyseq_queue_start = 0;
size_t keyseq_queue_end   = 0;


// declaration of internal helper functions

// mask modifier keys that will affect the level of the target layout
static uint8_t mask_levelmod(uint8_t mod);

static bool keyseq_queue_empty();
static bool keyseq_queue_full();
static inline void keyseq_queue_enqueue(uint8_t key, keystate_t event, uint8_t modifiers);
static void keyseq_queue_dequeue();

// implementation of public functions

void keyseq_queue_progress() {
    if (!keyseq_queue_empty()) {
        const struct keyseq_step_s* next_step = &keyseq_queue[keyseq_queue_start];
#ifdef CHANGE_MODIFIERS_BEFORE_KEYEVENT
        if (keyboard_modifier_keys != next_step->modifiers) {
            keyboard_modifier_keys = next_step->modifiers;
            if (next_step->key == KEY_NONE) {
                keyseq_queue_dequeue();
            }
            send_keys_usb();
            return;
        }
#else
        keyboard_modifier_keys = next_step->modifiers;
#endif

        if (next_step->key != KEY_NONE) {
            if (next_step->change == KS_PRESS) {
                press_key(next_step->key);
            } else {
                release_key(next_step->key);
            }
        }
    
        keyseq_queue_dequeue();

        send_keys_usb();
    }
}

void kev_plain(uint8_t key, keystate_t event) {
    keyseq_queue_enqueue(key, event, MODIFIERS_NONE | mask_levelmod(modifiers_current_in));
}

void kev_w_shift(uint8_t key, keystate_t event) {
    keyseq_queue_enqueue(key, event, KEY_SHIFT      | mask_levelmod(modifiers_current_in));
}

void kev_w_altgr(uint8_t key, keystate_t event) {
    keyseq_queue_enqueue(key, event, KEY_RIGHT_ALT  | mask_levelmod(modifiers_current_in));
}

void kev_level2(uint8_t key, keystate_t event) {
    keyseq_queue_enqueue(key, event, KEY_SHIFT      | mask_levelmod(modifiers_current_in));
}

void kev_level3(uint8_t key, keystate_t event) {
    if (event == KS_PRESS) {
        keyseq_queue_enqueue(KEY_CAPS_LOCK, KS_PRESS  , modifiers_current_in);
        keyseq_queue_enqueue(key          , KS_PRESS  , modifiers_current_in);
    } else {
        keyseq_queue_enqueue(key          , KS_RELEASE, modifiers_current_in);
        keyseq_queue_enqueue(KEY_CAPS_LOCK, KS_RELEASE, modifiers_current_in);
    }
}

void kev_allow_modifiers(uint8_t key, keystate_t event) {
    keyseq_queue_enqueue(key, event, modifiers_current_in);
}

void kev_modifier(uint8_t key, keystate_t event) {
    if (event == KS_PRESS) {
        modifiers_current_in |=  key;
    } else {
        modifiers_current_in &= ~key;
    }
    keyseq_queue_enqueue(KEY_NONE, KS_PRESS, modifiers_current_in);
}


void kev_TODO() {
    // todo: log to uart, light up warning LED    
}






// implementation of internal helper functions

static uint8_t mask_levelmod(uint8_t mod) {
    return mod & ~(KEY_SHIFT | KEY_LEFT_SHIFT | KEY_RIGHT_SHIFT | KEY_RIGHT_ALT);
}




bool keyseq_queue_empty() {
    return keyseq_queue_start == keyseq_queue_end;
}

bool keyseq_queue_full() {
    if (keyseq_queue_start <= keyseq_queue_end) {
        return keyseq_queue_start == 0 && keyseq_queue_end == KEYSEQ_QUEUE_LENGTH - 1;
    } else {
        return keyseq_queue_end == keyseq_queue_start - 1;
    }
}

static inline void keyseq_queue_enqueue(uint8_t key, keystate_t event, uint8_t modifiers) {
    if (keyseq_queue_full()) {
        inform(IL_WARN, SC_WARN_TOO_MANY_KEYS);
        return;
    }
    keyseq_queue[keyseq_queue_end].key       = key;
    keyseq_queue[keyseq_queue_end].modifiers = modifiers;
    keyseq_queue[keyseq_queue_end].change    = event;
    ++keyseq_queue_end;
    if (keyseq_queue_end == KEYSEQ_QUEUE_LENGTH) {
        keyseq_queue_end = 0;
    }
}

void keyseq_queue_dequeue() {
    ++keyseq_queue_start;
    if (keyseq_queue_start == KEYSEQ_QUEUE_LENGTH) {
        keyseq_queue_start = 0;
    }
}


