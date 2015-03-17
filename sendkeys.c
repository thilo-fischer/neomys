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

#if 0 // unused
// mask modifier keys that will affect the level of the target layout
static uint8_t mask_levelmod(uint8_t mod);
#endif

static bool keyseq_queue_empty();
static bool keyseq_queue_full();
static inline void keyseq_queue_enqueue(uint8_t key, keystate_t event, uint8_t modifiers);
static void keyseq_queue_dequeue();

// implementation of public functions

#define CHANGE_MODIFIERS_BEFORE_KEYEVENT

void keyseq_queue_progress() {
    if (!keyseq_queue_empty()) {
        const struct keyseq_step_s* next_step = &keyseq_queue[keyseq_queue_start];

        if (next_step->key == KEY_NONE) {
            
            inform(IL_DBG, next_step->change == KS_PRESS ? SC_DBG_USB_MOD_PRESS : SC_DBG_USB_MOD_RELEASE);
            info_add(keyboard_modifier_keys ^ next_step->modifiers);
            keyboard_modifier_keys = next_step->modifiers;
            
        } else {
        
            if (keyboard_modifier_keys != next_step->modifiers) {
                inform(IL_DBG, next_step->change == KS_PRESS ? SC_DBG_USB_MOD_PRESS : SC_DBG_USB_MOD_RELEASE);
                info_add(keyboard_modifier_keys ^ next_step->modifiers);
                keyboard_modifier_keys = next_step->modifiers;
#ifdef CHANGE_MODIFIERS_BEFORE_KEYEVENT
                send_keys_usb();
                return;
#endif
            }
            
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

enum targetlevel_e {
    TLVL_PLAIN_L1,
    TLVL_SHIFT_L2,
    TLVL_ALTGR_L3,
    TLVL_NEO_L3,
    TLVL_NEO_L4,
    TLVL_NEO_L5,
    TLVL_NEO_L6,
};

#if 0 // unused
static inline bool has_level(uint8_t modifs, enum targetlevel_e lvl) {
    switch (lvl) {
    case TLVL_PLAIN_L1:
        return modifs & (KEY_SHIFT | KEY_LEFT_SHIFT | KEY_RIGHT_SHIFT | KEY_RIGHT_ALT) == 0;
    case TLVL_SHIFT_L2:
        return modifs & (KEY_SHIFT | KEY_LEFT_SHIFT | KEY_RIGHT_SHIFT) > 0 && modifs & (KEY_RIGHT_ALT) == 0;
    case TLVL_ALTGR_L3:
        return modifs & (KEY_RIGHT_ALT) > 0 && modifs & (KEY_SHIFT | KEY_LEFT_SHIFT | KEY_RIGHT_SHIFT) == 0;
    default:
        inform(IL_WARN, SC_WARN_KEY_NOT_YET_IMPLMTD);
    }
}
#endif

static inline uint8_t modifiers_with_level(uint8_t modifs, enum targetlevel_e lvl) {
    switch (lvl) {
    case TLVL_PLAIN_L1:
        return modifs & ~(KEY_SHIFT | KEY_LEFT_SHIFT | KEY_RIGHT_SHIFT | KEY_RIGHT_ALT);
    case TLVL_SHIFT_L2:
        modifs &= ~(KEY_RIGHT_ALT);
        if ((modifs & (KEY_SHIFT | KEY_LEFT_SHIFT | KEY_RIGHT_SHIFT)) == 0) {
            modifs |= KEY_SHIFT;
        }
        return modifs;
    case TLVL_ALTGR_L3:
        modifs &= ~(KEY_SHIFT | KEY_LEFT_SHIFT | KEY_RIGHT_SHIFT);
        modifs |= KEY_RIGHT_ALT;
        return modifs;
    default:
        inform(IL_WARN, SC_WARN_KEY_NOT_YET_IMPLMTD);
        return modifs;
    }
}

void kev_plain(uint8_t key, keystate_t event) {
    keyseq_queue_enqueue(key, event, modifiers_with_level(modifiers_current_in, TLVL_PLAIN_L1));
}

void kev_w_shift(uint8_t key, keystate_t event) {
    keyseq_queue_enqueue(key, event, modifiers_with_level(modifiers_current_in, TLVL_SHIFT_L2));
}

void kev_w_altgr(uint8_t key, keystate_t event) {
    keyseq_queue_enqueue(key, event, modifiers_with_level(modifiers_current_in, TLVL_ALTGR_L3));
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
    keyseq_queue_enqueue(KEY_NONE, event, modifiers_current_in);
}


void kev_TODO() {
    // todo: log to uart, light up warning LED    
}






// implementation of internal helper functions

#if 0 // unused
static uint8_t mask_levelmod(uint8_t mod) {
    return mod & ~(KEY_SHIFT | KEY_LEFT_SHIFT | KEY_RIGHT_SHIFT | KEY_RIGHT_ALT);
}
#endif




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

static inline void inform_enqueue(uint8_t key, keystate_t event, uint8_t modifiers) {
    inform(IL_DBG, SC_DBG_KEYSEQ_ENQUEUE);
    info_add(key);
    info_add(event);
    info_add(modifiers);
}

static inline void keyseq_queue_enqueue(uint8_t key, keystate_t event, uint8_t modifiers) {
    if (keyseq_queue_full()) {
        inform(IL_WARN, SC_WARN_TOO_MANY_KEYS);
        return;
    }
    inform_enqueue(key, event, modifiers);
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


