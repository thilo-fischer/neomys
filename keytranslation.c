/*
  Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
  Copyright (c) 2015 Thilo Fischer
  This program is licenced under GPLv3.
*/

#include <stddef.h>

#include "teensy_codelib/usb_keyboard/usb_keyboard.h"

#include "keytranslation.h"

#include "usb_keyboard.h"
#include "sendkeys.h"


/**
 * Keyboard layout the USB host is configured to use.
 */
target_layout_t target_layout = TL_NEO;


// KEY FUNCTIONS

#define KF(name) static void kf_##name(target_layout_t tl, keystate_t event)

// special purpose

KF(nop) {}

KF(TODO) {
    inform(IL_WARN, SC_WARN_KEY_NOT_YET_IMPLMTD);
}

KF(next_target_layout) {
    if (event == KS_PRESS) {
        ++target_layout;
        if (target_layout == TL_COUNT) {
            target_layout = TL_NEO;
        }
        inform(IL_INFO, SC_INFO_SWITCH_TARGET_LAYOUT);
        info_add(target_layout);
    }
}

KF(prev_target_layout) {
    if (event == KS_PRESS) {
        if (target_layout == TL_NEO) {
            target_layout = TL_COUNT;
        }
        --target_layout;
        inform(IL_INFO, SC_INFO_SWITCH_TARGET_LAYOUT);
        info_add(target_layout);
    }
}

// statechange drivers for regular keyboards

KF(numlock) {
    switch (tl) {
    default:
        kev_allow_modifiers(KEY_NUM_LOCK, event);
    }    
}

KF(scrolllock) {
    switch (tl) {
    default:
        kev_allow_modifiers(KEY_SCROLL_LOCK, event);
    }    
}

KF(capslock) {
    switch (tl) {
    default:
        kev_allow_modifiers(KEY_CAPS_LOCK, event);
    }    
}

// level modifiers

static inline void set_modifier_bit(enum neo_level_modifiers_e mod, keystate_t event) {
    if (event == KS_PRESS) {
        level_modifiers |=  mod;
    } else {
        level_modifiers &= ~mod;
    }
}

// Currently no support to lock levels 5 and 6.
static inline void toggle_levellock(enum neo_levels_e level) {
    if (
        locked_level == level
        ||
        (locked_level == LEVEL4       && level == LEVEL4_MOUSE)
        ||
        (locked_level == LEVEL4_MOUSE && level == LEVEL4      )
        ) {
        locked_level = LEVEL1;
    } else {
        locked_level = level;
    }
}

static inline void affect_levellock(enum neo_level_modifiers_e mod, enum neo_level_modifiers_e also_mod, enum neo_levels_e level, keystate_t event) {
    if (event == KS_PRESS) {
        if (level_modifiers & also_mod) {
            toggle_levellock(level);
        }
    }
}


/**
   @return true if the modifier event may be communicated to the host without causing any trouble (because we have a non-Neo host which would not understand Neo-specific level modifier keys or because it would cause level-locking on a Neo host), false otherwise.
 */
static inline bool handle_level_mod(target_layout_t tl, enum neo_level_modifiers_e mod, enum neo_level_modifiers_e also_mod, enum neo_levels_e lock_candidate, keystate_t event) {
    set_modifier_bit(mod, event);
    affect_levellock(mod, also_mod, lock_candidate, event);
    // Inform the host about the modifier event only if it uses the NEO layout and thus knows how to handle the modifier correctly. It is very unlikely the user wants to use modifier+mouseclick or modifier+return, esp. if the host uses another layout than the NEO layout.
    // Inform the host about the modifier event only if this won't affect a levellock. We will take care of level locking in the neomys firmware and hide any level locking events from the Neo driver on the host. We want to assure locking state of neomys and of the host's Neo driver can never go out of sync, also Neo driver does not always allow locking of all levels and does not even know of LEVEL4_MOUSE (which we also want to be able lock).
    return (tl == TL_NEO) && ((level_modifiers & also_mod) == 0);
}

KF(level2mod_left) {
    handle_level_mod(tl, LM2_L, LM2_R, LEVEL2, event);
    // Inform the host about the shift modifier event -- any host will understand the shift modifier and users will want to be able to use e.g. shift+mouseclick shift+return.
    kev_modifier(KEY_LEFT_SHIFT, event);
}

KF(level2mod_right) {
    handle_level_mod(tl, LM2_R, LM2_L, LEVEL2, event);
    // Inform the host about the shift modifier event -- any host will understand the shift modifier and users will want to be able to use e.g. shift+mouseclick shift+return.
    kev_modifier(KEY_RIGHT_SHIFT, event);
}

KF(level3mod_left) {
    if (handle_level_mod(tl, LM3_L, LM3_R, LEVEL3, event))
        kev_virtual_modifier(KEY_CAPS_LOCK, event);
}

KF(level3mod_right) {
    if (handle_level_mod(tl, LM3_R, LM3_L, LEVEL3, event))
        kev_virtual_modifier(KEY_BACKSLASH, event);
}

KF(level4mod_left) {
    // If LM4_L is getting pressed while LM4_R is already pressed, lock LEVEL4_MOUSE.
    if (handle_level_mod(tl, LM4_L, LM4_R, LEVEL4_MOUSE, event) && locked_level != LEVEL4_MOUSE)
    // Inform even a Neo host about the modifier event only if we have not a LEVEL4_MOUSE-lock. (Neo host does not know about LEVEL4_MOUSE and would take wrong actions.)
        kev_virtual_modifier(KEY_ISO_EXTRA, event);
}

KF(level4mod_right) {
    // If LM4_R is getting pressed while LM4_L is already pressed, lock LEVEL4.
    handle_level_mod(tl, LM4_R, LM4_L, LEVEL4, event);
    // Do not inform any host about this modifier event, also Neo host does not know about LEVEL4_MOUSE.
}

// modifiers

KF(ctrl_left) {
    switch (tl) {
    default:
        kev_modifier(KEY_LEFT_CTRL, event);
    }
}

KF(ctrl_right) {
    switch (tl) {
    default:
        kev_modifier(KEY_RIGHT_CTRL, event);
    }
}

KF(alt_left) {
    switch (tl) {
    default:
        kev_modifier(KEY_LEFT_ALT, event);
    }
}

KF(alt_right) {
    switch (tl) {
    case TL_NEO:
    case TL_DE:
    case TL_DE_NODEAD:
        kev_modifier(KEY_ALT, event);
        break;
    default:
        // KEY_RIGHT_ALT is AltGr key on some target layouts and may affect the level => use KEY_ALT instead of KEY_RIGHT_ALT to avoid further confusion ...
        // kev_modifier(KEY_RIGHT_ALT, event);
        kev_modifier(KEY_ALT, event);
    }
}

KF(gui_left) {
    switch (tl) {
    default:
        kev_modifier(KEY_LEFT_GUI, event);
    }
}

KF(gui_right) {
    switch (tl) {
    default:
        kev_modifier(KEY_RIGHT_GUI, event);
    }
}


// numbers

KF(1) {
    switch (tl) {
    default:
        kev_plain(KEY_1, event);
    }
}

KF(2) {
    switch (tl) {
    default:
        kev_plain(KEY_2, event);
    }
}

KF(3) {
    switch (tl) {
    default:
        kev_plain(KEY_3, event);
    }
}

KF(4) {
    switch (tl) {
    default:
        kev_plain(KEY_4, event);
    }
}

KF(5) {
    switch (tl) {
    default:
        kev_plain(KEY_5, event);
    }
}

KF(6) {
    switch (tl) {
    default:
        kev_plain(KEY_6, event);
    }
}

KF(7) {
    switch (tl) {
    default:
        kev_plain(KEY_7, event);
    }
}

KF(8) {
    switch (tl) {
    default:
        kev_plain(KEY_8, event);
    }
}

KF(9) {
    switch (tl) {
    default:
        kev_plain(KEY_9, event);
    }
}

KF(0) {
    switch (tl) {
    default:
        kev_plain(KEY_0, event);
    }
}

// letters
// upper case

KF(A) {
    switch (tl) {
    case TL_NEO:
        kev_level2(KEY_D, event);
        break;
    default:
        kev_w_shift(KEY_A, event);
    }
}

KF(B) {
    switch (tl) {
    case TL_NEO:
        kev_level2(KEY_N, event);
        break;
    default:
        kev_w_shift(KEY_B, event);
    }
}

KF(C) {
    switch (tl) {
    case TL_NEO:
        kev_level2(KEY_R, event);
        break;
    default:
        kev_w_shift(KEY_C, event);
    }
}

KF(D) {
    switch (tl) {
    case TL_NEO:
        kev_level2(KEY_SEMICOLON, event);
        break;
    default:
        kev_w_shift(KEY_D, event);
    }
}

KF(E) {
    switch (tl) {
    case TL_NEO:
        kev_level2(KEY_F, event);
        break;
    default:
        kev_w_shift(KEY_E, event);
    }
}

KF(F) {
    switch (tl) {
    case TL_NEO:
        kev_level2(KEY_O, event);
        break;
    default:
        kev_w_shift(KEY_F, event);
    }
}

KF(G) {
    switch (tl) {
    case TL_NEO:
        kev_level2(KEY_I, event);
        break;
    default:
        kev_w_shift(KEY_G, event);
    }
}

KF(H) {
    switch (tl) {
    case TL_NEO:
        kev_level2(KEY_U, event);
        break;
    default:
        kev_w_shift(KEY_H, event);
    }
}

KF(I) {
    switch (tl) {
    case TL_NEO:
        kev_level2(KEY_S, event);
        break;
    default:
        kev_w_shift(KEY_I, event);
    }
}

KF(J) {
    switch (tl) {
    case TL_NEO:
        kev_level2(KEY_SLASH, event);
        break;
    default:
        kev_w_shift(KEY_J, event);
    }
}

KF(K) {
    switch (tl) {
    case TL_NEO:
        kev_level2(KEY_Y, event);
        break;
    default:
        kev_w_shift(KEY_K, event);
    }
}

KF(L) {
    switch (tl) {
    case TL_NEO:
        kev_level2(KEY_E, event);
        break;
    default:
        kev_w_shift(KEY_L, event);
    }
}

KF(M) {
    switch (tl) {
    case TL_NEO:
        kev_level2(KEY_M, event);
        break;
    default:
        kev_w_shift(KEY_M, event);
    }
}

KF(N) {
    switch (tl) {
    case TL_NEO:
        kev_level2(KEY_J, event);
        break;
    default:
        kev_w_shift(KEY_N, event);
    }
}

KF(O) {
    switch (tl) {
    case TL_NEO:
        kev_level2(KEY_G, event);
        break;
    default:
        kev_w_shift(KEY_O, event);
    }
}

KF(P) {
    switch (tl) {
    case TL_NEO:
        kev_level2(KEY_V, event);
        break;
    default:
        kev_w_shift(KEY_P, event);
    }
}

KF(Q) {
    switch (tl) {
    case TL_NEO:
        kev_level2(KEY_P, event);
        break;
    default:
        kev_w_shift(KEY_Q, event);
    }
}

KF(R) {
    switch (tl) {
    case TL_NEO:
        kev_level2(KEY_K, event);
        break;
    default:
        kev_w_shift(KEY_R, event);
    }
}

KF(S) {
    switch (tl) {
    case TL_NEO:
        kev_level2(KEY_H, event);
        break;
    default:
        kev_w_shift(KEY_S, event);
    }
}

KF(T) {
    switch (tl) {
    case TL_NEO:
        kev_level2(KEY_L, event);
        break;
    default:
        kev_w_shift(KEY_T, event);
    }
}

KF(U) {
    switch (tl) {
    case TL_NEO:
        kev_level2(KEY_A, event);
        break;
    default:
        kev_w_shift(KEY_U, event);
    }
}

KF(V) {
    switch (tl) {
    case TL_NEO:
        kev_level2(KEY_W, event);
        break;
    default:
        kev_w_shift(KEY_V, event);
    }
}

KF(W) {
    switch (tl) {
    case TL_NEO:
        kev_level2(KEY_T, event);
        break;
    default:
        kev_w_shift(KEY_W, event);
    }
}

KF(X) {
    switch (tl) {
    case TL_NEO:
        kev_level2(KEY_Q, event);
        break;
    default:
        kev_w_shift(KEY_X, event);
    }
}

KF(Y) {
    switch (tl) {
    case TL_NEO:
        kev_level2(KEY_QUOTE, event);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
    case TL_DE_APPLE:
        kev_w_shift(KEY_Z, event);
        break;
    default:
        kev_w_shift(KEY_Y, event);
    }
}

KF(Z) {
    switch (tl) {
    case TL_NEO:
        kev_level2(KEY_B, event);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
    case TL_DE_APPLE:
        kev_w_shift(KEY_Y, event);
        break;
    default:
        kev_w_shift(KEY_Z, event);
    }
}

KF(AUML) {
    switch (tl) {
    case TL_NEO:
        kev_level2(KEY_C, event);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
    case TL_DE_APPLE:
        kev_w_shift(KEY_QUOTE, event);
        break;
    default:
        kev_TODO();
    }
}

KF(OUML) {
    switch (tl) {
    case TL_NEO:
        kev_level2(KEY_X, event);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
    case TL_DE_APPLE:
        kev_w_shift(KEY_SEMICOLON, event);
        break;
    default:
        kev_TODO();
    }
}

KF(UUML) {
    switch (tl) {
    case TL_NEO:
        kev_level2(KEY_Z, event);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
    case TL_DE_APPLE:
        kev_w_shift(KEY_LEFT_BRACE, event);
        break;
    default:
        kev_TODO();
    }
}

KF(ESZETT) {
    switch (tl) {
    case TL_NEO:
        kev_level2(KEY_LEFT_BRACE, event);
        break;
    default:
        kev_TODO();
    }
}

// letters
// lower case

KF(a) {
    switch (tl) {
    case TL_NEO:
        kev_plain(KEY_D, event);
        break;
    default:
        kev_plain(KEY_A, event);
    }
}

KF(b) {
    switch (tl) {
    case TL_NEO:
        kev_plain(KEY_N, event);
        break;
    default:
        kev_plain(KEY_B, event);
    }
}

KF(c) {
    switch (tl) {
    case TL_NEO:
        kev_plain(KEY_R, event);
        break;
    default:
        kev_plain(KEY_C, event);
    }
}

KF(d) {
    switch (tl) {
    case TL_NEO:
        kev_plain(KEY_SEMICOLON, event);
        break;
    default:
        kev_plain(KEY_D, event);
    }
}

KF(e) {
    switch (tl) {
    case TL_NEO:
        kev_plain(KEY_F, event);
        break;
    default:
        kev_plain(KEY_E, event);
    }
}

KF(f) {
    switch (tl) {
    case TL_NEO:
        kev_plain(KEY_O, event);
        break;
    default:
        kev_plain(KEY_F, event);
    }
}

KF(g) {
    switch (tl) {
    case TL_NEO:
        kev_plain(KEY_I, event);
        break;
    default:
        kev_plain(KEY_G, event);
    }
}

KF(h) {
    switch (tl) {
    case TL_NEO:
        kev_plain(KEY_U, event);
        break;
    default:
        kev_plain(KEY_H, event);
    }
}

KF(i) {
    switch (tl) {
    case TL_NEO:
        kev_plain(KEY_S, event);
        break;
    default:
        kev_plain(KEY_I, event);
    }
}

KF(j) {
    switch (tl) {
    case TL_NEO:
        kev_plain(KEY_SLASH, event);
        break;
    default:
        kev_plain(KEY_J, event);
    }
}

KF(k) {
    switch (tl) {
    case TL_NEO:
        kev_plain(KEY_Y, event);
        break;
    default:
        kev_plain(KEY_K, event);
    }
}

KF(l) {
    switch (tl) {
    case TL_NEO:
        kev_plain(KEY_E, event);
        break;
    default:
        kev_plain(KEY_L, event);
    }
}

KF(m) {
    switch (tl) {
    case TL_NEO:
        kev_plain(KEY_M, event);
        break;
    default:
        kev_plain(KEY_M, event);
    }
}

KF(n) {
    switch (tl) {
    case TL_NEO:
        kev_plain(KEY_J, event);
        break;
    default:
        kev_plain(KEY_N, event);
    }
}

KF(o) {
    switch (tl) {
    case TL_NEO:
        kev_plain(KEY_G, event);
        break;
    default:
        kev_plain(KEY_O, event);
    }
}

KF(p) {
    switch (tl) {
    case TL_NEO:
        kev_plain(KEY_V, event);
        break;
    default:
        kev_plain(KEY_P, event);
    }
}

KF(q) {
    switch (tl) {
    case TL_NEO:
        kev_plain(KEY_P, event);
        break;
    default:
        kev_plain(KEY_Q, event);
    }
}

KF(r) {
    switch (tl) {
    case TL_NEO:
        kev_plain(KEY_K, event);
        break;
    default:
        kev_plain(KEY_R, event);
    }
}

KF(s) {
    switch (tl) {
    case TL_NEO:
        kev_plain(KEY_H, event);
        break;
    default:
        kev_plain(KEY_S, event);
    }
}

KF(t) {
    switch (tl) {
    case TL_NEO:
        kev_plain(KEY_L, event);
        break;
    default:
        kev_plain(KEY_T, event);
    }
}

KF(u) {
    switch (tl) {
    case TL_NEO:
        kev_plain(KEY_A, event);
        break;
    default:
        kev_plain(KEY_U, event);
    }
}

KF(v) {
    switch (tl) {
    case TL_NEO:
        kev_plain(KEY_W, event);
        break;
    default:
        kev_plain(KEY_V, event);
    }
}

KF(w) {
    switch (tl) {
    case TL_NEO:
        kev_plain(KEY_T, event);
        break;
    default:
        kev_plain(KEY_W, event);
    }
}

KF(x) {
    switch (tl) {
    case TL_NEO:
        kev_plain(KEY_Q, event);
        break;
    default:
        kev_plain(KEY_X, event);
    }
}

KF(y) {
    switch (tl) {
    case TL_NEO:
        kev_plain(KEY_QUOTE, event);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
    case TL_DE_APPLE:
        kev_plain(KEY_Z, event);
        break;
    default:
        kev_plain(KEY_Y, event);
    }
}

KF(z) {
    switch (tl) {
    case TL_NEO:
        kev_plain(KEY_B, event);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
    case TL_DE_APPLE:
        kev_plain(KEY_Y, event);
        break;
    default:
        kev_plain(KEY_Z, event);
    }
}

KF(auml) {
    switch (tl) {
    case TL_NEO:
        kev_plain(KEY_C, event);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
    case TL_DE_APPLE:
        kev_plain(KEY_QUOTE, event);
        break;
    default:
        kev_TODO();
    }
}

KF(ouml) {
    switch (tl) {
    case TL_NEO:
        kev_plain(KEY_X, event);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
    case TL_DE_APPLE:
        kev_plain(KEY_SEMICOLON, event);
        break;
    default:
        kev_TODO();
    }
}

KF(uuml) {
    switch (tl) {
    case TL_NEO:
        kev_plain(KEY_Z, event);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
    case TL_DE_APPLE:
        kev_plain(KEY_LEFT_BRACE, event);
        break;
    default:
        kev_TODO();
    }
}

KF(eszett) {
    switch (tl) {
    case TL_NEO:
        kev_plain(KEY_LEFT_BRACE, event);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
    case TL_DE_APPLE:
        kev_plain(KEY_MINUS, event);
        break;
    default:
        kev_TODO();
    }
}

// basic punctuation characters (in ASCII order)

KF(space) {
    kev_allow_modifiers(KEY_SPACE, event);
}

KF(exclamation_mark) {
    switch (tl) {
    case TL_NEO:
        kev_level3(KEY_Y, event);
        break;
    default:
        kev_w_shift(KEY_1, event);
    }
}

KF(straight_dbl_quote) {
    switch (tl) {
    case TL_NEO:
        kev_level3(KEY_COMMA, event);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
    case TL_DE_APPLE:
        kev_w_shift(KEY_2, event);
        break;
    default:
        kev_w_shift(KEY_QUOTE, event);
    }
}

KF(hash) {
    switch (tl) {
    case TL_NEO:
        kev_level3(KEY_Z, event);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
    case TL_DE_APPLE:
        kev_plain(KEY_BACKSLASH, event);
        break;
    default:
        kev_w_shift(KEY_3, event);
    }
}

KF(dollar) {
    switch (tl) {
    case TL_NEO:
        kev_level3(KEY_X, event);
        break;
    default:
        kev_w_shift(KEY_4, event);
    }
}

KF(percent) {
    switch (tl) {
    case TL_NEO:
        kev_level3(KEY_M, event);
        break;
    default:
        kev_w_shift(KEY_5, event);
    }
}

KF(ampersand) {
    switch (tl) {
    case TL_NEO:
        kev_level3(KEY_P, event);
        break;
    default:
        kev_w_shift(KEY_6, event);
    }
}

KF(apostrophe) {
    switch (tl) {
    case TL_NEO:
        kev_level3(KEY_PERIOD, event);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
    case TL_DE_APPLE:
        kev_w_shift(KEY_BACKSLASH, event);
        break;
    default:
        kev_plain(KEY_QUOTE, event);
    }
}

KF(parentheses_left) {
    switch (tl) {
    case TL_NEO:
        kev_level3(KEY_J, event);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
    case TL_DE_APPLE:
        kev_w_shift(KEY_8, event);
        break;
    default:
        kev_w_shift(KEY_9, event);
    }
}

KF(parentheses_right) {
    switch (tl) {
    case TL_NEO:
        kev_level3(KEY_K, event);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
    case TL_DE_APPLE:
        kev_w_shift(KEY_9, event);
        break;
    default:
        kev_w_shift(KEY_0, event);
    }
}

KF(asterisk) {
    switch (tl) {
    case TL_NEO:
        kev_level3(KEY_G, event);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
    case TL_DE_APPLE:
        kev_w_shift(KEY_RIGHT_BRACE, event);
        break;
    default:
        kev_w_shift(KEY_8, event);
    }
}

KF(plus) {
    switch (tl) {
    case TL_NEO:
        kev_level3(KEY_N, event);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
    case TL_DE_APPLE:
        kev_plain(KEY_RIGHT_BRACE, event);
        break;
    default:
        kev_w_shift(KEY_EQUAL, event);
    }
}

KF(comma) {
    switch (tl) {
    default:
        kev_plain(KEY_COMMA, event);
    }
}

KF(dash_neo_lvl1) {
    switch (tl) {
    case TL_NEO:
        kev_plain(KEY_MINUS, event);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
    case TL_DE_APPLE:
        kev_plain(KEY_SLASH, event);
        break;
    default:
        kev_plain(KEY_MINUS, event);
    }
}

KF(dash_neo_lvl3) {
    switch (tl) {
    case TL_NEO:
        kev_level3(KEY_L, event);
        break;
    default:
        kf_dash_neo_lvl1(tl, event);
    }
}

KF(period) {
    switch (tl) {
    default:
        kev_plain(KEY_PERIOD, event);
    }
}

KF(slash) {
    switch (tl) {
    case TL_NEO:
        kev_level3(KEY_S, event);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
    case TL_DE_APPLE:
        kev_w_shift(KEY_7, event);
        break;
    default:
        kev_plain(KEY_SLASH, event);
    }
}


KF(colon) {
    switch (tl) {
    case TL_NEO:
        kev_level3(KEY_SEMICOLON, event);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
    case TL_DE_APPLE:
        kev_w_shift(KEY_PERIOD, event);
        break;
    default:
        kev_w_shift(KEY_SEMICOLON, event);
    }
}

KF(semicolon) {
    switch (tl) {
    case TL_NEO:
        kev_level3(KEY_SLASH, event);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
    case TL_DE_APPLE:
        kev_w_shift(KEY_COMMA, event);
        break;
    default:
        kev_plain(KEY_SEMICOLON, event);
    }
}

KF(chevron_left) {
    switch (tl) {
    case TL_NEO:
        kev_level3(KEY_U, event);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
    case TL_DE_APPLE: // FIXME: not working properly on Macbook ...
        kev_plain(KEY_ISO_EXTRA, event);
        break;
    default:
        kev_w_shift(KEY_COMMA, event);
    }
}

KF(equals) {
    switch (tl) {
    case TL_NEO:
        kev_level3(KEY_O, event);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
    case TL_DE_APPLE:
        kev_w_shift(KEY_0, event);
        break;
    default:
        kev_plain(KEY_EQUAL, event);
    }
}

KF(chevron_right) {
    switch (tl) {
    case TL_NEO:
        kev_level3(KEY_I, event);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
    case TL_DE_APPLE: // FIXME: not working properly on Macbook ...
        kev_w_shift(KEY_ISO_EXTRA, event);
        break;
    default:
        kev_w_shift(KEY_PERIOD, event);
    }
}

KF(question_mark) {
    switch (tl) {
    case TL_NEO:
        kev_level3(KEY_H, event);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
    case TL_DE_APPLE:
        kev_w_shift(KEY_MINUS, event);
        break;
    default:
        kev_w_shift(KEY_SLASH, event);
    }
}

KF(at) {
    switch (tl) {
    case TL_NEO:
        kev_level3(KEY_QUOTE, event);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kev_w_altgr(KEY_Q, event);
        break;
    case TL_DE_APPLE:
        kev_w_alt(KEY_L, event);
        break;
    default:
        kev_w_shift(KEY_2, event);
    }
}


KF(bracket_left) {
    switch (tl) {
    case TL_NEO:
        kev_level3(KEY_E, event);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kev_w_altgr(KEY_8, event);
        break;
    case TL_DE_APPLE:
        kev_w_alt(KEY_5, event);
        break;
    default:
        kev_plain(KEY_LEFT_BRACE, event);
    }
}

KF(backslash) {
    switch (tl) {
    case TL_NEO:
        kev_level3(KEY_A, event);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kev_w_altgr(KEY_MINUS, event);
        break;
    case TL_DE_APPLE:
        kev_w_shift_alt(KEY_7, event);
        break;
    default:
        kev_plain(KEY_BACKSLASH, event);
    }
}

KF(bracket_right) {
    switch (tl) {
    case TL_NEO:
        kev_level3(KEY_R, event);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kev_w_altgr(KEY_9, event);
        break;
    case TL_DE_APPLE:
        kev_w_alt(KEY_6, event);
        break;
    default:
        kev_plain(KEY_RIGHT_BRACE, event);
    }
}

KF(caret) {
    switch (tl) {
    case TL_NEO:
        kev_level3(KEY_T, event);
        break;
    case TL_DE:
        kev_plain(KEY_TILDE, event);
        kev_plain(KEY_SPACE, event);
        break;
    case TL_DE_NODEAD:
        kev_plain(KEY_TILDE, event);
        break;
    case TL_DE_APPLE:
        kev_w_shift_alt(KEY_K, event);
        break;
    default:
        kev_w_shift(KEY_6, event);
    }
}

KF(underscore) {
    switch (tl) {
    case TL_NEO:
        kev_level3(KEY_W, event);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
    case TL_DE_APPLE:
        kev_w_shift(KEY_SLASH, event);
        break;
    default:
        kev_w_shift(KEY_MINUS, event);
    }
}

KF(backtick) {
    switch (tl) {
    case TL_NEO:
        kev_level3(KEY_B, event);
        break;
    case TL_DE:
    case TL_DE_APPLE: // FIXME: not working properly on Macbook ...
        kev_w_shift(KEY_EQUAL, event);
        kev_plain  (KEY_SPACE, event);
        break;
    case TL_DE_NODEAD:
        kev_w_shift(KEY_EQUAL, event);
        break;
    default:
        kev_w_shift(KEY_TILDE, event);
    }
}


KF(brace_left) {
    switch (tl) {
    case TL_NEO:
        kev_level3(KEY_D, event);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kev_w_altgr(KEY_7, event);
        break;
    case TL_DE_APPLE:
        kev_w_alt(KEY_8, event);
        break;
    default:
        kev_w_shift(KEY_LEFT_BRACE, event);
    }
}

KF(pipe) {
    switch (tl) {
    case TL_NEO:
        kev_level3(KEY_C, event);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kev_w_altgr(KEY_ISO_EXTRA, event);
        break;
    case TL_DE_APPLE:
        kev_w_alt(KEY_7, event);
        break;
    default:
        kev_w_shift(KEY_BACKSLASH, event);
    }
}

KF(brace_right) {
    switch (tl) {
    case TL_NEO:
        kev_level3(KEY_F, event);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kev_w_altgr(KEY_0, event);
        break;
    case TL_DE_APPLE:
        kev_w_alt(KEY_9, event);
        break;
    default:
        kev_w_shift(KEY_RIGHT_BRACE, event);
    }
}

KF(tilde) {
    switch (tl) {
    case TL_NEO:
        kev_level3(KEY_V, event);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kev_w_altgr(KEY_RIGHT_BRACE, event);
        break;
    case TL_DE_APPLE:
        kev_w_shift_alt(KEY_8, event);
        break;
    default:
        kev_w_shift(KEY_TILDE, event);
    }
}


// enhanced punctuation characters (in order of appearance on the Neo layout from left to right, from top to bottom)

KF(degree) {
    switch (tl) {
    case TL_NEO:
        kev_level2(KEY_1, event);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
    case TL_DE_APPLE:
        kev_w_shift(KEY_TILDE, event);
        break;
    default:
        kev_TODO();
    }
}

KF(sectionsign) {
    switch (tl) {
    case TL_NEO:
        kev_level2(KEY_2, event);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
    case TL_DE_APPLE:
        kev_w_shift(KEY_3, event);
        break;
    default:
        kev_TODO();
    }
}

KF(euro_currency) {
    switch (tl) {
    case TL_NEO:
        kev_level2(KEY_7, event);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kev_w_altgr(KEY_E, event);
        break;
    case TL_DE_APPLE:
        kev_w_alt(KEY_E, event);
        break;
    default:
        kev_TODO();
    }
}

KF(cent_currency) {
    switch (tl) {
    case TL_NEO:
        kev_level3(KEY_6, event);
        break;
    default:
        kev_TODO();
    }
}

KF(pound_currency) {
    switch (tl) {
    case TL_NEO:
        kev_level4(KEY_6, event);
        break;
    default:
        kev_TODO();
    }
}

KF(yen_currency) {
    switch (tl) {
    case TL_NEO:
        kev_level3(KEY_7, event);
        break;
    default:
        kev_TODO();
    }
}

KF(currency_sign) {
    switch (tl) {
    case TL_NEO:
        kev_level4(KEY_7, event);
        break;
    default:
        kev_TODO();
    }
}

// esoteric punctuation characters (in order of appearance on the Neo layout from left to right, from top to bottom)

KF(superscript1) {
    switch (tl) {
    case TL_NEO:
        kev_level3(KEY_1, event);
        break;
    default:
        kev_TODO();
    }
}

KF(superscript2) {
    switch (tl) {
    case TL_NEO:
        kev_level3(KEY_2, event);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kev_w_altgr(KEY_2, event);
        break;
    default:
        kev_TODO();
    }
}

KF(script_small_l) {
    switch (tl) {
    case TL_NEO:
        kev_level2(KEY_3, event);
        break;
    default:
        kev_TODO();
    }
}

KF(superscript3) {
    switch (tl) {
    case TL_NEO:
        kev_level3(KEY_3, event);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kev_w_altgr(KEY_3, event);
        break;
    default:
        kev_TODO();
    }
}

KF(numero_sign) {
    switch (tl) {
    case TL_NEO:
        kev_level4(KEY_3, event);
        break;
    default:
        kev_TODO();
    }
}

KF(guillemet_dbl_gt) {
    switch (tl) {
    case TL_NEO:
        kev_level2(KEY_4, event);
        break;
    default:
        kev_TODO();
    }
}

KF(guillemet_sgl_gt) {
    switch (tl) {
    case TL_NEO:
        kev_level3(KEY_4, event);
        break;
    default:
        kev_TODO();
    }
}

KF(guillemet_dbl_lt) {
    switch (tl) {
    case TL_NEO:
        kev_level2(KEY_5, event);
        break;
    default:
        kev_TODO();
    }
}

KF(guillemet_sgl_lt) {
    switch (tl) {
    case TL_NEO:
        kev_level3(KEY_5, event);
        break;
    default:
        kev_TODO();
    }
}

KF(low9quote_dbl) {
    switch (tl) {
    case TL_NEO:
        kev_level2(KEY_8, event);
        break;
    default:
        kev_TODO();
    }
}

KF(low9quote_sgl) {
    switch (tl) {
    case TL_NEO:
        kev_level3(KEY_8, event);
        break;
    default:
        kev_TODO();
    }
}

KF(6quote_dbl) {
    switch (tl) {
    case TL_NEO:
        kev_level2(KEY_9, event);
        break;
    default:
        kev_TODO();
    }
}

KF(6quote_sgl) {
    switch (tl) {
    case TL_NEO:
        kev_level3(KEY_9, event);
        break;
    default:
        kev_TODO();
    }
}

KF(9quote_dbl) {
    switch (tl) {
    case TL_NEO:
        kev_level2(KEY_0, event);
        break;
    default:
        kev_TODO();
    }
}

KF(9quote_sgl) {
    switch (tl) {
    case TL_NEO:
        kev_level3(KEY_0, event);
        break;
    default:
        kev_TODO();
    }
}

// Geviertstrich
KF(mdash) {
    switch (tl) {
    case TL_NEO:
        kev_level2(KEY_MINUS, event);
        break;
    default:
        kev_TODO();
    }
}

KF(ellipsis) {
    switch (tl) {
    case TL_NEO:
        kev_level3(KEY_Q, event);
        break;
    default:
        kev_TODO();
    }
}

KF(inverted_exclamation_mark) {
    switch (tl) {
    case TL_NEO:
        kev_level3(KEY_Y, event);
        break;
    default:
        kev_TODO();
    }
}

KF(long_s) {
    switch (tl) {
    case TL_NEO:
        kev_level3(KEY_LEFT_BRACE, event);
        break;
    default:
        kev_TODO();
    }
}

KF(minus) {
    switch (tl) {
    case TL_NEO:
        kev_level4(KEY_LEFT_BRACE, event);
        break;
    default:
        kev_TODO();
    }
}

KF(inverted_question_mark) {
    switch (tl) {
    case TL_NEO:
        kev_level3(KEY_H, event);
        break;
    default:
        kev_TODO();
    }
}

// Halbgeviertstrich
KF(ndash) {
    switch (tl) {
    case TL_NEO:
        kev_level2(KEY_COMMA, event);
        break;
    default:
        kev_TODO();
    }
}

KF(bullet) {
    switch (tl) {
    case TL_NEO:
        kev_level2(KEY_PERIOD, event);
        break;
    default:
        kev_TODO();
    }
}



// dead keys

KF(dead_grave) {
    switch (tl) {
    case TL_NEO:
        kev_plain(KEY_EQUAL, event);
        break;
    default:
        kev_TODO();
    }
}

KF(dead_cedilla) {
    switch (tl) {
    case TL_NEO:
        kev_level2(KEY_EQUAL, event);
        break;
    default:
        kev_TODO();
    }
}

KF(dead_ring) {
    switch (tl) {
    case TL_NEO:
        kev_level3(KEY_EQUAL, event);
        break;
    default:
        kev_TODO();
    }
}

KF(dead_umlaut) {
    switch (tl) {
    case TL_NEO:
        kev_level4(KEY_EQUAL, event);
        break;
    default:
        kev_TODO();
    }
}

KF(dead_circumfex) {
    switch (tl) {
    case TL_NEO:
        kev_plain(KEY_TILDE, event);
        break;
    default:
        kev_TODO();
    }
}

KF(dead_caron) {
    switch (tl) {
    case TL_NEO:
        kev_level2(KEY_TILDE, event);
        break;
    default:
        kev_TODO();
    }
}

KF(dead_dot) {
    switch (tl) {
    case TL_NEO:
        kev_level4(KEY_TILDE, event);
        break;
    default:
        kev_TODO();
    }
}

KF(dead_acute) {
    switch (tl) {
    case TL_NEO:
        kev_plain(KEY_RIGHT_BRACE, event);
        break;
    default:
        kev_TODO();
    }
}

KF(dead_perispomene) {
    switch (tl) {
    case TL_NEO:
        kev_level2(KEY_RIGHT_BRACE, event);
        break;
    default:
        kev_TODO();
    }
}

KF(dead_bar) {
    switch (tl) {
    case TL_NEO:
        kev_level3(KEY_RIGHT_BRACE, event);
        break;
    default:
        kev_TODO();
    }
}

KF(dead_double_acute) {
    switch (tl) {
    case TL_NEO:
        kev_level4(KEY_RIGHT_BRACE, event);
        break;
    default:
        kev_TODO();
    }
}


// control and navigation keys

KF(page_up) {
    switch (tl) {
    default:
        kev_allow_modifiers(KEY_PAGE_UP, event);
    }
}

KF(page_down) {
    switch (tl) {
    default:
        kev_allow_modifiers(KEY_PAGE_DOWN, event);
    }
}

KF(backspace) {
    switch (tl) {
    default:
        kev_allow_modifiers(KEY_BACKSPACE, event);
    }
}

KF(delete) {
    switch (tl) {
    default:
        kev_allow_modifiers(KEY_DELETE, event);
    }
}

KF(up) {
    switch (tl) {
    default:
        kev_allow_modifiers(KEY_UP, event);
    }
}

KF(down) {
    switch (tl) {
    default:
        kev_allow_modifiers(KEY_DOWN, event);
    }
}

KF(left) {
    switch (tl) {
    default:
        kev_allow_modifiers(KEY_LEFT, event);
    }
}

KF(right) {
    switch (tl) {
    default:
        kev_allow_modifiers(KEY_RIGHT, event);
    }
}

KF(home) {
    switch (tl) {
    default:
        kev_allow_modifiers(KEY_HOME, event);
    }
}

KF(end) {
    switch (tl) {
    default:
        kev_allow_modifiers(KEY_END, event);
    }
}

KF(escape) {
    switch (tl) {
    default:
        kev_allow_modifiers(KEY_ESC, event);
    }
}

KF(tab) {
    switch (tl) {
    default:
        kev_allow_modifiers(KEY_TAB, event);
    }
}

KF(insert) {
    switch (tl) {
    default:
        kev_allow_modifiers(KEY_INSERT, event);
    }
}

KF(return) {
    switch (tl) {
    default:
        kev_allow_modifiers(KEY_ENTER, event);
    }
}


// numpad

KF(numpad_1) {
    switch (tl) {
    default:
        kev_allow_modifiers(KEYPAD_1, event);
    }
}

KF(numpad_2) {
    switch (tl) {
    default:
        kev_allow_modifiers(KEYPAD_2, event);
    }
}

KF(numpad_3) {
    switch (tl) {
    default:
        kev_allow_modifiers(KEYPAD_3, event);
    }
}

KF(numpad_4) {
    switch (tl) {
    default:
        kev_allow_modifiers(KEYPAD_4, event);
    }
}

KF(numpad_5) {
    switch (tl) {
    default:
        kev_allow_modifiers(KEYPAD_5, event);
    }
}

KF(numpad_6) {
    switch (tl) {
    default:
        kev_allow_modifiers(KEYPAD_6, event);
    }
}

KF(numpad_7) {
    switch (tl) {
    default:
        kev_allow_modifiers(KEYPAD_7, event);
    }
}

KF(numpad_8) {
    switch (tl) {
    default:
        kev_allow_modifiers(KEYPAD_8, event);
    }
}

KF(numpad_9) {
    switch (tl) {
    default:
        kev_allow_modifiers(KEYPAD_9, event);
    }
}

KF(numpad_0) {
    switch (tl) {
    default:
        kev_allow_modifiers(KEYPAD_0, event);
    }
}

KF(numpad_divide) {
    switch (tl) {
    default:
        kev_allow_modifiers(KEYPAD_SLASH, event);
    }
}

KF(numpad_multiply) {
    switch (tl) {
    default:
        kev_allow_modifiers(KEYPAD_ASTERIX, event);
    }
}

KF(numpad_plus) {
    switch (tl) {
    default:
        kev_allow_modifiers(KEYPAD_PLUS, event);
    }
}

KF(numpad_minus) {
    switch (tl) {
    default:
        kev_allow_modifiers(KEYPAD_MINUS, event);
    }
}

// XXX also try with SDL_SCANCODE_DECIMALSEPARATOR
KF(numpad_comma) {
    switch (tl) {
    case TL_NEO:
    case TL_DE:
    case TL_DE_NODEAD:
    case TL_DE_APPLE:
        kev_allow_modifiers(KEYPAD_PERIOD, event);
        break;
    default:
        kev_plain(KEY_COMMA, event);
    }
}

// XXX also try with SDL_SCANCODE_DECIMALSEPARATOR
KF(numpad_period) {
    switch (tl) {
    case TL_NEO:
    case TL_DE:
    case TL_DE_NODEAD:
    case TL_DE_APPLE:
        kev_plain(KEY_PERIOD, event);
        break;
    default:
        kev_allow_modifiers(KEYPAD_PERIOD, event);
    }
}

// function keys

KF(F1) {
    switch (tl) {
    default:
        kev_allow_modifiers(KEY_F1, event);
    }
}

KF(F2) {
    switch (tl) {
    default:
        kev_allow_modifiers(KEY_F2, event);
    }
}

KF(F3) {
    switch (tl) {
    default:
        kev_allow_modifiers(KEY_F3, event);
    }
}

KF(F4) {
    switch (tl) {
    default:
        kev_allow_modifiers(KEY_F4, event);
    }
}

KF(F5) {
    switch (tl) {
    default:
        kev_allow_modifiers(KEY_F5, event);
    }
}

KF(F6) {
    switch (tl) {
    default:
        kev_allow_modifiers(KEY_F6, event);
    }
}

KF(F7) {
    switch (tl) {
    default:
        kev_allow_modifiers(KEY_F7, event);
    }
}

KF(F8) {
    switch (tl) {
    default:
        kev_allow_modifiers(KEY_F8, event);
    }
}

KF(F9) {
    switch (tl) {
    default:
        kev_allow_modifiers(KEY_F9, event);
    }
}

KF(F10) {
    switch (tl) {
    default:
        kev_allow_modifiers(KEY_F10, event);
    }
}

KF(F11) {
    switch (tl) {
    default:
        kev_allow_modifiers(KEY_F11, event);
    }
}

KF(F12) {
    switch (tl) {
    default:
        kev_allow_modifiers(KEY_F12, event);
    }
}


// more from function key row and similar

KF(printscreen) {
    kev_allow_modifiers(KEY_PRINTSCREEN, event);
}

KF(pause) {
    kev_allow_modifiers(KEY_PAUSE, event);
}

KF(app) {
    kev_allow_modifiers(KEY_APP, event);
}

// special keys

KF(redo) {
    kev_allow_modifiers(KEY_REDO, event);
}

KF(undo) {
    kev_allow_modifiers(KEY_UNDO, event);
}

KF(copy) {
    kev_allow_modifiers(KEY_COPY, event);
}

KF(paste) {
    kev_allow_modifiers(KEY_PASTE, event);
}

KF(cut) {
    kev_allow_modifiers(KEY_CUT, event);
}

KF(find) {
    kev_allow_modifiers(KEY_FIND, event);
}

KF(forward) {
// TODO: scancode values > 255
    //kev_allow_modifiers(KEY_FORWARD, event);
    kev_TODO();
}

KF(back) {
// TODO: scancode values > 255
    //kev_allow_modifiers(KEY_BACK, event);
    kev_TODO();
}



keyrecord_t keymap[ROW_COUNT][2][COL_COUNT] = {
    // ROW_NUM (0x00-0x0F)
    {
        //ROW_NUM left (0x00-0x07)
        {
            // ô
            {
                .type = KT_IGNORE_SHIFTLOCK,
                .kf = { kf_dead_circumfex, kf_dead_caron, kf_TODO, kf_dead_dot, },
            },
            // 1
            {
                .type = KT_IGNORE_SHIFTLOCK,
                .kf = { kf_1, kf_degree, kf_superscript1, kf_TODO, kf_F1, },
            },
            // 2
            {
                .type = KT_IGNORE_SHIFTLOCK,
                .kf = { kf_2, kf_sectionsign, kf_superscript2, kf_TODO, kf_F2, },
            },
            // 3
            {
                .type = KT_IGNORE_SHIFTLOCK,
                .kf = { kf_3, kf_script_small_l, kf_superscript3, kf_numero_sign, kf_F3, },
            },
            // 4
            {
                .type = KT_IGNORE_SHIFTLOCK,
                .kf = { kf_4, kf_guillemet_dbl_gt, kf_guillemet_sgl_gt, kf_nop, kf_F4, },
            },
            // 5
            {
                .type = KT_IGNORE_SHIFTLOCK,
                .kf = { kf_5, kf_guillemet_dbl_lt, kf_guillemet_sgl_lt, kf_TODO, kf_F5, },
            },
        }, // controller (left/right side)
        //ROW_NUM right (0x08-0x0F)
        {
            // Key for number 6 is located at the right hand side of the keyboard. This is uncommon wrt regular keyboards with divided key fields (Microsoft Natural Ergonomic Keyboard and alike), but common for all keyboarys that have been designed with ergonomics in mind (e.g. ErgoDox, TECK, TypeMatrix, Kinesis Contoured Keyboard).
            // 6
            {
                .type = KT_IGNORE_SHIFTLOCK,
                .kf = { kf_6, kf_dollar, kf_cent_currency, kf_pound_currency, kf_F6, },
            },
            // 7
            {
                .type = KT_IGNORE_SHIFTLOCK,
                .kf = { kf_7, kf_euro_currency, kf_yen_currency, kf_currency_sign, kf_F7, },
            },
            // 8
            {
                .type = KT_IGNORE_SHIFTLOCK,
                .kf = { kf_8, kf_low9quote_dbl, kf_low9quote_sgl, kf_tab, kf_F8, },
            },
            // 9
            {
                .type = KT_IGNORE_SHIFTLOCK,
                .kf = { kf_9, kf_6quote_dbl, kf_6quote_sgl, kf_numpad_divide, kf_F9, },
            },
            // 0
            {
                .type = KT_IGNORE_SHIFTLOCK,
                .kf = { kf_0, kf_9quote_dbl, kf_9quote_sgl, kf_numpad_multiply, kf_F10, },
            },
            // -
            {
                .type = KT_IGNORE_SHIFTLOCK,
                .kf = { kf_dash_neo_lvl1, kf_mdash, kf_nop, kf_numpad_minus, kf_F11, },
            },
            // ò
            {
                .type = KT_IGNORE_SHIFTLOCK,
                .kf = { kf_dead_grave, kf_dead_cedilla, kf_dead_ring, kf_dead_umlaut, kf_F12, },
            },
        }, // controller (left/right side)
    }, // row

    
    // ROW_TOP (0x10-0x1F)
    {
        //ROW_TOP left (0x10-0x17)
        {
            // in contrast to neo layout, the left level4 modifier key has been moved from right of the left level2 mod key to ontop of the level3 mod ked
            // level4 modifier
            {
                .type = KT_LEVELMOD,
                .kf = { kf_level4mod_left },
            },
            // X
            {
                .type = KT_REGULAR,
                .kf = { kf_x, kf_X, kf_ellipsis, kf_page_up, NULL, },
            },
            // V
            {
                .type = KT_REGULAR,
                .kf = { kf_v, kf_V, kf_underscore, kf_backspace, NULL, },
            },
            // L
            {
                .type = KT_REGULAR,
                .kf = { kf_l, kf_L, kf_bracket_left, kf_up, NULL, },
            },
            // C
            {
                .type = KT_REGULAR,
                .kf = { kf_c, kf_C, kf_bracket_right, kf_delete, NULL, },
            },
            // W
            {
                .type = KT_REGULAR,
                .kf = { kf_w, kf_W, kf_caret, kf_page_down, NULL, },
            },
        }, // controller (left/right side)
        //ROW_TOP right (0x18-0x1F)
        {
            // K
            {
                .type = KT_REGULAR,
                .kf = { kf_k, kf_K, kf_exclamation_mark, kf_inverted_exclamation_mark, kf_back, },
            },
            // H
            {
                .type = KT_REGULAR,
                .kf = { kf_h, kf_H, kf_chevron_left, kf_numpad_7, kf_TODO /*left dblclick*/, },
            },
            // G
            {
                .type = KT_REGULAR,
                .kf = { kf_g, kf_G, kf_chevron_right, kf_numpad_8, kf_TODO /*mid dblclick*/, },
            },
            // F
            {
                .type = KT_REGULAR,
                .kf = { kf_f, kf_F, kf_equals, kf_numpad_9, kf_TODO /*right dblclick*/, },
            },
            // Q
            {
                .type = KT_REGULAR,
                .kf = { kf_q, kf_Q, kf_ampersand, kf_numpad_plus, kf_forward, },
            },
            // ß
            {
                .type = KT_REGULAR,
                .kf = { kf_eszett, kf_ESZETT, kf_long_s, kf_minus, kf_pause, },
            },
            // ó
            {
                .type = KT_IGNORE_SHIFTLOCK,
                .kf = { kf_dead_acute, kf_dead_perispomene, kf_dead_bar, kf_dead_double_acute, kf_printscreen },
            },
        }, // controller (left/right side)
    }, // row

    
    // ROW_HOME (0x20-0x2F)
    {
        //ROW_HOME left (0x20-0x27)
        {
            // level3 modifier
            {
                .type = KT_LEVELMOD,
                .kf = { kf_level3mod_left },
            },
            // U
            {
                .type = KT_REGULAR,
                .kf = { kf_u, kf_U, kf_backslash, kf_home, },
            },
            // I
            {
                .type = KT_REGULAR,
                .kf = { kf_i, kf_I, kf_slash, kf_left, },
            },
            // A
            {
                .type = KT_REGULAR,
                .kf = { kf_a, kf_A, kf_brace_left, kf_down, },
            },
            // E
            {
                .type = KT_REGULAR,
                .kf = { kf_e, kf_E, kf_brace_right, kf_right, },
            },
            // O
            {
                .type = KT_REGULAR,
                .kf = { kf_o, kf_O, kf_asterisk, kf_end, },
            },
        }, // controller (left/right side)
        //ROW_HOME right (0x28-0x2F)
        {
            // S
            {
                .type = KT_REGULAR,
                .kf = { kf_s, kf_S, kf_question_mark, kf_inverted_question_mark, kf_TODO /*click 8*/, },
            },
            // N
            {
                .type = KT_REGULAR,
                .kf = { kf_n, kf_N, kf_parentheses_left, kf_numpad_4, kf_TODO /*left click*/, },
            },
            // R
            {
                .type = KT_REGULAR,
                .kf = { kf_r, kf_R, kf_parentheses_right, kf_numpad_5, kf_TODO /*mid click*/, },
            },
            // T
            {
                .type = KT_REGULAR,
                .kf = { kf_t, kf_T, kf_dash_neo_lvl3, kf_numpad_6, kf_TODO /*right click*/, },
            },
            // D
            {
                .type = KT_REGULAR,
                .kf = { kf_d, kf_D, kf_colon, kf_numpad_comma, kf_TODO /*click 9*/, },
            },
            // Y
            {
                .type = KT_REGULAR,
                .kf = { kf_y, kf_Y, kf_at, kf_numpad_period, kf_find, },
            },
            // level3 modifier
            {
                .type = KT_LEVELMOD,
                .kf = { kf_level3mod_right },
            },
        }, // controller (left/right side)
    }, // row

    
    // ROW_BTM (0x30-0x3F)
    {
        //ROW_BTM left (0x30-0x37)
        {
            // level2 modifier
            {
                .type = KT_LEVELMOD,
                .kf = { kf_level2mod_left },
            },
            // Ü
            {
                .type = KT_REGULAR,
                .kf = { kf_uuml, kf_UUML, kf_hash, kf_escape, },
            },
            // Ö
            {
                .type = KT_REGULAR,
                .kf = { kf_ouml, kf_OUML, kf_dollar, kf_tab, },
            },
            // Ä
            {
                .type = KT_REGULAR,
                .kf = { kf_auml, kf_AUML, kf_pipe, kf_insert, },
            },
            // P
            {
                .type = KT_REGULAR,
                .kf = { kf_p, kf_P, kf_tilde, kf_return, },
            },
            // Z
            {
                .type = KT_REGULAR,
                .kf = { kf_z, kf_Z, kf_backtick, kf_undo, },
            },
        }, // controller (left/right side)
        //ROW_BTM right (0x38-0x3F)
        {
            // B
            {
                .type = KT_REGULAR,
                .kf = { kf_b, kf_B, kf_plus, kf_colon, kf_undo, },
            },
            // M
            {
                .type = KT_REGULAR,
                .kf = { kf_m, kf_M, kf_percent, kf_numpad_1, kf_copy, },
            },
            // ,
            {
                .type = KT_IGNORE_SHIFTLOCK,
                .kf = { kf_comma, kf_ndash, kf_straight_dbl_quote, kf_numpad_2, kf_paste, },
            },
            // .
            {
                .type = KT_IGNORE_SHIFTLOCK,
                .kf = { kf_period, kf_bullet, kf_apostrophe, kf_numpad_3, kf_cut, },
            },
            // J
            {
                .type = KT_REGULAR,
                .kf = { kf_j, kf_J, kf_semicolon, kf_semicolon, kf_redo, },
            },
            // level2 modifier
            {
                .type = KT_LEVELMOD,
                .kf = { kf_level2mod_right },
            },
        }, // controller (left/right side)
    }, // row

    
    // ROW_SPACE (0x40-0x4F)
    {
        //ROW_SPACE left (0x40-0x47)
        {
            // left Ctrl
            {
                .type = KT_IGNORE_LEVEL,
                .kf = { kf_ctrl_left },
            },
            // left GUI
            {
                .type = KT_IGNORE_LEVEL,
                .kf = { kf_gui_left },
            },
            // switch target layout // TODO preliminary use of this key
            {
                .type = KT_IGNORE_ALLLOCK,
                .kf = { kf_next_target_layout, kf_prev_target_layout, kf_numlock, kf_scrolllock, kf_capslock },
            },
            // left Alt
            {
                .type = KT_IGNORE_LEVEL,
                .kf = { kf_alt_left },
            },
            // space
            {
                .type = KT_REGULAR,
                .kf = { kf_space, kf_space, kf_space, kf_space, kf_return },
            },
            // unused
            {
                .type = KT_DUMB,
                .kf = { NULL },
            },
        }, // controller (left/right side)
        //ROW_SPACE right (0x48-0x4F)
        {
            // space, numpad-zero
            {
                .type = KT_REGULAR,
                .kf = { kf_space, kf_space, kf_space, kf_numpad_0, },
            },
            // level4 modifier
            {
                .type = KT_LEVELMOD,
                .kf = { kf_level4mod_right },
            },
            // right Alt
            {
                .type = KT_IGNORE_LEVEL,
                .kf = { kf_alt_right },
            },
            // switch target layout // TODO preliminary use of this key
            {
                .type = KT_IGNORE_LEVEL,
                .kf = { kf_app },
            },
            // right GUI
            {
                .type = KT_IGNORE_LEVEL,
                .kf = { kf_gui_right },
            },
            // right Ctrl
            {
                .type = KT_IGNORE_LEVEL,
                .kf = { kf_ctrl_right },
            },
        }, // controller (left/right side)
    }, // row
};



const keyrecord_t *get_keyrecord(uint8_t controller, uint8_t row, uint8_t col) {
    return &keymap[row][controller][col];
}
