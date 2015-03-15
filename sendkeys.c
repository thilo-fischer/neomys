/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.

   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

#include "sendkeys.h"

#include "keytranslation.h"
#include "teensy_codelib/usb_keyboard/usb_keyboard.h"


#define MODIFIERS_NONE 0x00
#define KEY_NONE       0x00

uint8_t modifiers_current_in  = 0x00;

void kev_plain(uint8_t key, keystate_t event) {
    keyseq_queue_enqueue(key, event, MODIFIERS_NONE);
}

void kev_w_shift(uint8_t key, keystate_t event) {
    keyseq_queue_enqueue(key, event, KEY_SHIFT);
}

void kev_w_altgr(uint8_t key, keystate_t event) {
    keyseq_queue_enqueue(key, event, KEY_RIGHT_ALT);
}

void kev_level2(uint8_t key, keystate_t event) {
    keyseq_queue_enqueue(key, event, KEY_SHIFT);
}

void kev_level3(uint8_t key, keystate_t event) {
    if (event == KS_PRESS) {
        keyseq_queue_enqueue(KEY_CAPS_LOCK, KS_PRESS  , modifiers_current);
        keyseq_queue_enqueue(key          , KS_PRESS  , modifiers_current);
    } else {
        keyseq_queue_enqueue(key          , KS_RELEASE, modifiers_current);
        keyseq_queue_enqueue(KEY_CAPS_LOCK, KS_RELEASE, modifiers_current);
    }
}

// just an alias for kev_allow_modifiers
#define kev_virtual_modifier(k, e) kev_allow_modifiers(k, e)

void kev_allow_modifiers(uint8_t key, keystate_t event) {
    keyseq_queue_enqueue(key, event, modifiers_current_in);
}

void kev_modifier(uint8_t key, keystate_t event) {
    if (event == KS_PRESS) {
        modifiers_current_in |=  key;
    } else {
        modifiers_current_in &= ~key;
    }
    keyseq_queue_enqueue(KEY_NONE, KS_PRESS, modifiers_current);
}


void kev_TODO() {
    // todo: log to uart, light up warning LED    
}



struct keyseq_step_s {
    uint8_t key;
    uint8_t modifiers;
    enum keystate_e change : 1;
    bool virtual_mod : 1;
};

#define KEYSEQ_QUEUE_LENGTH 32
struct keyseq_step_s keyseq_queue[KEYSEQ_QUEUE_LENGTH] /*= {{0}}*/;
size_t keyseq_queue_start = 0;
size_t keyseq_queue_end   = 0;

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

static inline void keyseq_queue_enqueue_internal(uint8_t key, keystate_t event, uint8_t modifiers, bool virtual_mod) {
    if (keyseq_queue_full()) {
        warning(W_TOO_MANY_KEYS);
        return;
    }
    keyseq_queue[keyseq_queue_end].key = key;
    keyseq_queue[keyseq_queue_end].modifiers = modifiers;
    keyseq_queue[keyseq_queue_end].change = event;
    keyseq_queue[keyseq_queue_end].virtual_mod = virtual_mod;
    ++keyseq_queue_end;
    if (keyseq_queue_end == KEY_SEQ_QUEUE_LENGTH) {
        keyseq_queue_end = 0;
    }
}

void keyseq_queue_enqueue(uint8_t key, keystate_t event, uint8_t modifiers) {
    keyseq_queue_enqueue_internal(key, event, modifiers, false);
}

void keyseq_queue_enqueue_virtual_mod(uint8_t key, keystate_t event, uint8_t modifiers) {
    keyseq_queue_enqueue_internal(key, event, modifiers, true);
}

void keyseq_queue_dequeue() {
    ++keyseq_queue_start;
    if (keyseq_queue_start == KEY_SEQ_QUEUE_LENGTH) {
        keyseq_queue_start = 0;
    }
}

void keyseq_queue_progress() {
    if (!key_seq_queue_empty()) {
        const struct keyseq_step_s* next_step = &key_seq_queue[key_seq_queue_start];
        if (next_step->virtual_mod) {
            if (find_keyboard_key(next_step->modifiers) == NULL) {
                press_key(next_step->modifiers);
                usb_keyboard_send();
                return;
            }
            if (next_step->change == KS_PRESS) {
                if (find_keyboard_key(next_step->key) == NULL) {
                    press_key(next_step->key);
                    usb_keyboard_send();
                    return;
                }
            } else {
                
            } else if (find_keyboard_key(next_step->key) == NULL) {
                press_key(next_step->key);
                usb_keyboard_send();
                return;
                
                
        } else {
#ifdef CHANGE_MODIFIERS_BEFORE_KEYEVENT
        if (keyboard_modifier_keys != next_step->modifiers) {
            keyboard_modifier_keys = next_step->modifiers;
            usb_keyboard_send();
            if (next_step->key == KEY_NONE) {
                keyseq_queue_dequeue();
            }
            usb_keyboard_send();
            return;
        }
#else
        keyboard_modifier_keys = next_step->modifiers;
#end
        }

        if (next_step->key != KEY_NONE) {
            if (next_step->change == KS_PRESS) {
                press_key(key);
            } else {
                release_key(key);
            }
        }
    
        keyseq_queue_dequeue();
 
        usb_keyboard_send();
    }
}

uint8_t *find_keyboard_key(uint8_t key) {
    uint8_t i;
    for (i = 0; i < 6; ++i) {
        if (keyboard_keys[i] == key) {
            return &keyboard_keys[i];
        }
    }
    return NULL;
}

void press_key(uint8_t key) {
    uint8_t *pos = find_keyboard_key(KEY_NONE);
    if (pos == NULL) {
        // todo: warn too many keys
        return;
    }
    *pos = key;
}

void release_key(uint8_t key) {
    uint8_t *pos = find_keyboard_key(key);
    if (pos == NULL) {
        // todo: warn invalid key state
        return;
    }
    *pos = KEY_NONE;
}
