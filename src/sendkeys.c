/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.

   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

/**
 * @file
 * Track and process the sequence of key events to send to the host.
 */

#include <stddef.h>

#include "sendkeys.h"

#include "usb_keyboard.h"

#include "teensy_codelib/usb_keyboard/usb_keyboard.h" // FIXME: move all code dependent on this file to usb_keyboard.c

#include "debug.h"

// FIXME replace with dbg_* commands
#define inform(a, b)
#define info_add(x)

// internal symbols

uint8_t modifiers_current_in  = 0x00;

// keys which are regular keys in a regular keyboard layout but act as level modifier keys in Neo layout
enum virtual_modifiers_e {
    VMOD_INVALID   =  0x00 ,
    VMOD_CAPS_LOCK = 1 << 0,
    VMOD_BACKSLASH = 1 << 1,
    VMOD_ISO_EXTRA = 1 << 2,
};
uint8_t virtual_modifiers_current_in  = 0x00;

struct keyseq_step_s {
    keycode_t key;
    uint8_t modifiers;
    keystate_t change;
};

#define KEYSEQ_QUEUE_LENGTH 32
struct keyseq_step_s keyseq_queue[KEYSEQ_QUEUE_LENGTH] /*= {{0}}*/;
size_t keyseq_queue_start = 0;
size_t keyseq_queue_end   = 0;


// declaration of internal helper functions

static bool keyseq_queue_empty();
static bool keyseq_queue_full();
static inline void keyseq_queue_enqueue(keycode_t key, keystate_t event, uint8_t modifiers);
static void keyseq_queue_dequeue();

// implementation of public functions

#define CHANGE_MODIFIERS_BEFORE_KEYEVENT

dbg_define_msg(HC_KEV_MOD, 0xE0,
               "^ kev mod %02hhX %s", sizeof(uint8_t), sizeof(char*));

dbg_define_msg(HC_KEV_SYM, 0xE1,
               "^ kev key%04hX ~mod%02hhx %s", sizeof(keycode_t), sizeof(uint8_t), sizeof(char*));

void progress_keyseq_queue() {
    if (!keyseq_queue_empty()) {
        const struct keyseq_step_s* next_step = &keyseq_queue[keyseq_queue_start];

        if (next_step->key == KEY_NONE) {

            dbg_debug(HC_KEV_MOD, keyboard_modifier_keys ^ next_step->modifiers, next_step->change == KS_PRESS ? "DN" : "UP");
            keyboard_modifier_keys = next_step->modifiers;
            
        } else {

            uint8_t modchange = keyboard_modifier_keys ^ next_step->modifiers;
            if (modchange > 0) {
                keyboard_modifier_keys = next_step->modifiers;
#ifdef CHANGE_MODIFIERS_BEFORE_KEYEVENT
                dbg_debug(HC_KEV_SYM, 0, modchange, next_step->change == KS_PRESS ? "dn" : "up");
                send_keys_usb();
                return;
#endif
            }
            
            dbg_debug(HC_KEV_SYM, next_step->key, modchange, next_step->change == KS_PRESS ? "dn" : "up");

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
    TLVL_PLAIN_L1,     ///> level1 of any layout
    TLVL_SHIFT_L2,     ///> level2 of basically all layouts
    TLVL_ALTGR_L3,     ///> level3 of TL_DE and similar
    TLVL_ALT_L3,       ///> level3 of TL_APPLE and similar
    TLVL_SHIFT_ALT_L4, ///> level4 of TL_APPLE and similar
    TLVL_NEO_L3,       ///> level3 of TL_NEO
    TLVL_NEO_L4,       ///> level4 of TL_NEO
    TLVL_NEO_L5,       ///> level5 of TL_NEO
    TLVL_NEO_L6,       ///> level6 of TL_NEO
};

// todo: take care of left alt key for apple target layouts
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
    case TLVL_ALT_L3:
        modifs &= ~(KEY_SHIFT | KEY_LEFT_SHIFT | KEY_RIGHT_SHIFT);
        modifs |= KEY_RIGHT_ALT; // use the RIGHT alt key to asure this will have the desired effect also in virtual machines in Parallels
        return modifs;
    case TLVL_SHIFT_ALT_L4:
        modifs |= KEY_SHIFT | KEY_RIGHT_ALT; // use the RIGHT alt key to asure this will have the desired effect also in virtual machines in Parallels
        return modifs;
    default:
        inform(IL_WARN, SC_WARN_KEY_NOT_YET_IMPLMTD);
        return modifs;
    }
}

void kev_plain(keycode_t key, keystate_t event) {
    keyseq_queue_enqueue(key, event, modifiers_with_level(modifiers_current_in, TLVL_PLAIN_L1));
}

void kev_w_shift(keycode_t key, keystate_t event) {
    keyseq_queue_enqueue(key, event, modifiers_with_level(modifiers_current_in, TLVL_SHIFT_L2));
    if (event == KS_RELEASE) {
        // make sure to send notification that modifier key was released
        keyseq_queue_enqueue(KEY_NONE, event, modifiers_current_in);
    }
}

// for TL_DE and similar
void kev_w_altgr(keycode_t key, keystate_t event) {
    keyseq_queue_enqueue(key, event, modifiers_with_level(modifiers_current_in, TLVL_ALTGR_L3));
    if (event == KS_RELEASE) {
        // make sure to send notification that modifier key was released
        keyseq_queue_enqueue(KEY_NONE, event, modifiers_current_in);
    }
}

// for TL_APPLE and similar
void kev_w_alt(keycode_t key, keystate_t event) {
    keyseq_queue_enqueue(key, event, modifiers_with_level(modifiers_current_in, TLVL_ALT_L3));
    if (event == KS_RELEASE) {
        // make sure to send notification that modifier key was released
        keyseq_queue_enqueue(KEY_NONE, event, modifiers_current_in);
    }
}

// for TL_APPLE and similar
void kev_w_shift_alt(keycode_t key, keystate_t event) {
    keyseq_queue_enqueue(key, event, modifiers_with_level(modifiers_current_in, TLVL_SHIFT_ALT_L4));
    if (event == KS_RELEASE) {
        // make sure to send notification that modifier key was released
        keyseq_queue_enqueue(KEY_NONE, event, modifiers_current_in);
    }
}

// for TL_NEO
void kev_level2(keycode_t key, keystate_t event) {
    keyseq_queue_enqueue(key, event, modifiers_with_level(modifiers_current_in, TLVL_SHIFT_L2));
    if (event == KS_RELEASE) {
        // make sure to send notification that modifier key was released
        keyseq_queue_enqueue(KEY_NONE, event, modifiers_current_in);
    }
}

// for TL_NEO
void kev_level3(keycode_t key, keystate_t event) {
    uint8_t modifiers = modifiers_with_level(modifiers_current_in, TLVL_PLAIN_L1);
    if (event == KS_PRESS) {
        kev_virtual_modifier(KEY_CAPS_LOCK, KS_PRESS);
        keyseq_queue_enqueue(key          , KS_PRESS  , modifiers);
    } else {
        keyseq_queue_enqueue(key          , KS_RELEASE, modifiers);
        kev_virtual_modifier(KEY_CAPS_LOCK, KS_RELEASE);
    }
}

// for TL_NEO
void kev_level4(keycode_t key, keystate_t event) {
    uint8_t modifiers = modifiers_with_level(modifiers_current_in, TLVL_PLAIN_L1);
    if (event == KS_PRESS) {
        kev_virtual_modifier(KEY_ISO_EXTRA, KS_PRESS);
        keyseq_queue_enqueue(key          , KS_PRESS  , modifiers);
    } else {
        keyseq_queue_enqueue(key          , KS_RELEASE, modifiers);
        kev_virtual_modifier(KEY_ISO_EXTRA, KS_RELEASE);
    }
}

void kev_allow_modifiers(keycode_t key, keystate_t event) {
    keyseq_queue_enqueue(key, event, modifiers_current_in);
}

void kev_modifier(keycode_t key, keystate_t event) {
    if (event == KS_PRESS) {
        modifiers_current_in |=  key;
    } else {
        modifiers_current_in &= ~key;
    }
    keyseq_queue_enqueue(KEY_NONE, event, modifiers_current_in);
}

enum virtual_modifiers_e get_virtmod_of_vmkey(keycode_t key) {
    switch (key) {
    case KEY_CAPS_LOCK:
        return VMOD_CAPS_LOCK;
    case KEY_BACKSLASH:
        return VMOD_BACKSLASH;
    case KEY_ISO_EXTRA:
        return VMOD_ISO_EXTRA;
    default:
        inform(IL_WARN, SC_WARN_KEY_NOT_YET_IMPLMTD);
        return VMOD_INVALID;
    }
}

enum targetlevel_e get_level_of_virtmod(enum virtual_modifiers_e vmod) {
    switch (vmod) {
    case VMOD_CAPS_LOCK:
    case VMOD_BACKSLASH:
        return TLVL_NEO_L3;
    case VMOD_ISO_EXTRA:
        return TLVL_NEO_L4;
    default:
        inform(IL_WARN, SC_WARN_KEY_NOT_YET_IMPLMTD);
        return TLVL_PLAIN_L1;
    }
}

void press_vmkey(keycode_t key, enum virtual_modifiers_e vmod) {
    keyseq_queue_enqueue(key, KS_PRESS, modifiers_current_in);
    virtual_modifiers_current_in |=  vmod;
}

void release_vmkey(keycode_t key, enum virtual_modifiers_e vmod) {
    keyseq_queue_enqueue(key, KS_RELEASE, modifiers_current_in);
    virtual_modifiers_current_in &= ~vmod;
}

keystate_t vmkey_state(enum virtual_modifiers_e vmod) {
    return (virtual_modifiers_current_in & vmod) > 0 ? KS_PRESS : KS_RELEASE;
}

bool is_vmodlevel_active(enum targetlevel_e tlvl) {
    enum virtual_modifiers_e modL, modR;
    switch (tlvl) {
    case TLVL_NEO_L3:
        modL = VMOD_CAPS_LOCK;
        modR = VMOD_BACKSLASH;
        break;
    case TLVL_NEO_L4:
        modL = VMOD_ISO_EXTRA;
        modR = VMOD_INVALID;
        break;
    default:
        inform(IL_WARN, SC_WARN_KEY_NOT_YET_IMPLMTD);
        return false;
     
    };
    return (virtual_modifiers_current_in & (modL | modR)) > 0;
}

dbg_define_msg(KEV_DBG_IGNORE, 0xD7,
               "kevIgnr:%s:%d",
               sizeof(char *),
               sizeof(keycode_t)
               );

// neo level modifier events that are not located on regular modifier keys (KEY_CAPS_LOCK, KEY_BACKSLASH, KEY_ISO_EXTRA)
void kev_virtual_modifier(keycode_t key, keystate_t event) {
    enum virtual_modifiers_e vmod = get_virtmod_of_vmkey(key);
    enum targetlevel_e vmlvl = get_level_of_virtmod(vmod);
    if (event == KS_PRESS) {
        if (is_vmodlevel_active(vmlvl)) {
          dbg_warn(KEV_DBG_IGNORE, "P", key);
        } else {
            press_vmkey(key, vmod);
        }
    } else {
        if (vmkey_state(vmod) == KS_PRESS) {
            release_vmkey(key, vmod);
        } else {
          dbg_warn(KEV_DBG_IGNORE, "R", key);
        }        
    }
}


void kev_TODO() {
    // todo: log to uart, light up warning LED    
}






// implementation of internal helper functions


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

static inline void inform_enqueue(keycode_t key, keystate_t event, uint8_t modifiers) {
    inform(IL_DBG, SC_DBG_KEYSEQ_ENQUEUE);
    info_add(key);
    info_add(event);
    info_add(modifiers);
}

static inline void keyseq_queue_enqueue(keycode_t key, keystate_t event, uint8_t modifiers) {
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


