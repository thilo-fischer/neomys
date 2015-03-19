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

enum virtual_modifiers_e {
    VMOD_INVALID   =  0x00 ,
    VMOD_CAPS_LOCK = 1 << 0,
    VMOD_BACKSLASH = 1 << 1,
    VMOD_ISO_EXTRA = 1 << 2,
};
uint8_t virtual_modifiers_current_in  = 0x00;

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
        modifs |= KEY_RIGHT_ALT;
        return modifs;
    case TLVL_SHIFT_ALT_L4:
        modifs |= KEY_SHIFT | KEY_RIGHT_ALT;
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

// for TL_DE and similar
void kev_w_altgr(uint8_t key, keystate_t event) {
    keyseq_queue_enqueue(key, event, modifiers_with_level(modifiers_current_in, TLVL_ALTGR_L3));
}

// for TL_APPLE and similar
void kev_w_alt(uint8_t key, keystate_t event) {
    keyseq_queue_enqueue(key, event, modifiers_with_level(modifiers_current_in, TLVL_ALT_L3));
}

// for TL_APPLE and similar
void kev_w_shift_alt(uint8_t key, keystate_t event) {
    keyseq_queue_enqueue(key, event, modifiers_with_level(modifiers_current_in, TLVL_SHIFT_ALT_L4));
}

// for TL_NEO
void kev_level2(uint8_t key, keystate_t event) {
    keyseq_queue_enqueue(key, event, modifiers_with_level(modifiers_current_in, TLVL_SHIFT_L2));
}

// for TL_NEO
void kev_level3(uint8_t key, keystate_t event) {
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
void kev_level4(uint8_t key, keystate_t event) {
    uint8_t modifiers = modifiers_with_level(modifiers_current_in, TLVL_PLAIN_L1);
    if (event == KS_PRESS) {
        kev_virtual_modifier(KEY_ISO_EXTRA, KS_PRESS);
        keyseq_queue_enqueue(key          , KS_PRESS  , modifiers);
    } else {
        keyseq_queue_enqueue(key          , KS_RELEASE, modifiers);
        kev_virtual_modifier(KEY_ISO_EXTRA, KS_RELEASE);
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
    keyseq_queue_enqueue(KEY_NONE, event, modifiers_current_in);
}

enum virtual_modifiers_e get_virtmod_of_vmkey(uint8_t key) {
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

#if 0 // unused
uint8_t get_vmkey_of_virtmod(enum virtual_modifiers_e mod) {
    switch (mod) {
    case VMOD_CAPS_LOCK:
        return KEY_CAPS_LOCK;
    case VMOD_BACKSLASH:
        return KEY_BACKSLASH;
    case VMOD_ISO_EXTRA:
        return KEY_ISO_EXTRA;
    default:
        inform(IL_WARN, SC_WARN_KEY_NOT_YET_IMPLMTD);
        return KEY_NONE;
    }
}
#endif

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

#if 0 // unused
enum targetlevel_e get_level_of_vmkey(uint8_t key) {
    return get_level_of_virtmod( get_virtmod_of_vmkey(key));
}

void activate_virtmod(enum virtual_modifiers_e vmod) {
    keyseq_queue_enqueue(key, KS_PRESS, modifiers_current_in);
    virtual_modifiers_current_in |=  mod;
}

void deactivate_virtmod(enum virtual_modifiers_e vmod) {
    keyseq_queue_enqueue(key, KS_RELEASE, modifiers_current_in);
    virtual_modifiers_current_in &= ~mod;
}
#endif

void press_vmkey(uint8_t key, enum virtual_modifiers_e vmod) {
    keyseq_queue_enqueue(key, KS_PRESS, modifiers_current_in);
    virtual_modifiers_current_in |=  vmod;
}

void release_vmkey(uint8_t key, enum virtual_modifiers_e vmod) {
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

// neo level modifier events that are not located on regular modifier keys (KEY_CAPS_LOCK, KEY_BACKSLASH, KEY_ISO_EXTRA)
void kev_virtual_modifier(uint8_t key, keystate_t event) {
    enum virtual_modifiers_e vmod = get_virtmod_of_vmkey(key);
    enum targetlevel_e vmlvl = get_level_of_virtmod(vmod);
    if (event == KS_PRESS) {
        if (is_vmodlevel_active(vmlvl)) {
            // TODO inform(INFO, "ignore keypress");
        } else {
            press_vmkey(key, vmod);
        }
    } else {
        if (vmkey_state(vmod) == KS_PRESS) {
            release_vmkey(key, vmod);
        } else {
            // TODO inform(INFO, "ignore keyrelease");
        }        
    }
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


