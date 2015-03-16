/*
  Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
  Copyright (c) 2015 Thilo Fischer
  This program is licenced under GPLv3.
*/

#include <stddef.h>

#include "teensy_codelib/usb_keyboard/usb_keyboard.h"

#include "keytranslation.h"

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
    ++target_layout;
    if (target_layout == TL_COUNT) {
        target_layout = TL_NEO;
    }
    inform(IL_INFO, SC_INFO_SWITCH_TARGET_LAYOUT);
    info_add(target_layout);
}

KF(prev_target_layout) {
    if (target_layout == TL_NEO) {
        target_layout = TL_COUNT;
    }
    --target_layout;
    inform(IL_INFO, SC_INFO_SWITCH_TARGET_LAYOUT);
    info_add(target_layout);
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

KF(level2mod_left) {
    set_modifier_bit(LM2_L, event);
    affect_levellock(LM2_L, LM2_R, LEVEL2, event);
    kev_modifier(KEY_LEFT_SHIFT, event);
}

KF(level2mod_right) {
    set_modifier_bit(LM2_R, event);
    affect_levellock(LM2_R, LM2_L, LEVEL2, event);
    kev_modifier(KEY_RIGHT_SHIFT, event);
}

KF(level3mod_left) {
    set_modifier_bit(LM3_L, event);
    affect_levellock(LM3_L, LM3_R, LEVEL3, event);
    if (tl == TL_NEO)
        kev_virtual_modifier(KEY_CAPS_LOCK, event);
}

KF(level3mod_right) {
    set_modifier_bit(LM3_R, event);
    affect_levellock(LM3_R, LM3_L, LEVEL3, event);
    if (tl == TL_NEO)
        kev_virtual_modifier(KEY_BACKSLASH, event);
}

KF(level4mod_left) {
    set_modifier_bit(LM4_L, event);
    // if LM4_L is getting pressed while LM4_R is already pressed, lock LEVEL4_MOUSE
    affect_levellock(LM4_L, LM4_R, LEVEL4_MOUSE, event);
    if (tl == TL_NEO)
        kev_modifier(KEY_RIGHT_ALT, event);
    // TODO kev_virtual_modifier(KEY_<<ISO extra key>>, event);
}

KF(level4mod_right) {
    set_modifier_bit(LM4_R, event);
    // if LM4_R is getting pressed while LM4_L is already pressed, lock LEVEL4
    affect_levellock(LM4_R, LM4_L, LEVEL4, event);
    if (tl == TL_NEO)
        kev_modifier(KEY_RIGHT_ALT, event);
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
        kev_w_shift(KEY_D, event);
        break;
    default:
        kev_w_shift(KEY_A, event);
    }
}

KF(B) {
    switch (tl) {
    case TL_NEO:
        kev_w_shift(KEY_N, event);
        break;
    default:
        kev_w_shift(KEY_B, event);
    }
}

KF(C) {
    switch (tl) {
    case TL_NEO:
        kev_w_shift(KEY_R, event);
        break;
    default:
        kev_w_shift(KEY_C, event);
    }
}

KF(D) {
    switch (tl) {
    case TL_NEO:
        kev_w_shift(KEY_SEMICOLON, event);
        break;
    default:
        kev_w_shift(KEY_D, event);
    }
}

KF(E) {
    switch (tl) {
    case TL_NEO:
        kev_w_shift(KEY_F, event);
        break;
    default:
        kev_w_shift(KEY_E, event);
    }
}

KF(F) {
    switch (tl) {
    case TL_NEO:
        kev_w_shift(KEY_O, event);
        break;
    default:
        kev_w_shift(KEY_F, event);
    }
}

KF(G) {
    switch (tl) {
    case TL_NEO:
        kev_w_shift(KEY_I, event);
        break;
    default:
        kev_w_shift(KEY_G, event);
    }
}

KF(H) {
    switch (tl) {
    case TL_NEO:
        kev_w_shift(KEY_U, event);
        break;
    default:
        kev_w_shift(KEY_H, event);
    }
}

KF(I) {
    switch (tl) {
    case TL_NEO:
        kev_w_shift(KEY_S, event);
        break;
    default:
        kev_w_shift(KEY_I, event);
    }
}

KF(J) {
    switch (tl) {
    case TL_NEO:
        kev_w_shift(KEY_SLASH, event);
        break;
    default:
        kev_w_shift(KEY_J, event);
    }
}

KF(K) {
    switch (tl) {
    case TL_NEO:
        kev_w_shift(KEY_Y, event);
        break;
    default:
        kev_w_shift(KEY_K, event);
    }
}

KF(L) {
    switch (tl) {
    case TL_NEO:
        kev_w_shift(KEY_E, event);
        break;
    default:
        kev_w_shift(KEY_L, event);
    }
}

KF(M) {
    switch (tl) {
    case TL_NEO:
        kev_w_shift(KEY_M, event);
        break;
    default:
        kev_w_shift(KEY_M, event);
    }
}

KF(N) {
    switch (tl) {
    case TL_NEO:
        kev_w_shift(KEY_J, event);
        break;
    default:
        kev_w_shift(KEY_N, event);
    }
}

KF(O) {
    switch (tl) {
    case TL_NEO:
        kev_w_shift(KEY_G, event);
        break;
    default:
        kev_w_shift(KEY_O, event);
    }
}

KF(P) {
    switch (tl) {
    case TL_NEO:
        kev_w_shift(KEY_V, event);
        break;
    default:
        kev_w_shift(KEY_P, event);
    }
}

KF(Q) {
    switch (tl) {
    case TL_NEO:
        kev_w_shift(KEY_P, event);
        break;
    default:
        kev_w_shift(KEY_Q, event);
    }
}

KF(R) {
    switch (tl) {
    case TL_NEO:
        kev_w_shift(KEY_K, event);
        break;
    default:
        kev_w_shift(KEY_R, event);
    }
}

KF(S) {
    switch (tl) {
    case TL_NEO:
        kev_w_shift(KEY_H, event);
        break;
    default:
        kev_w_shift(KEY_S, event);
    }
}

KF(T) {
    switch (tl) {
    case TL_NEO:
        kev_w_shift(KEY_L, event);
        break;
    default:
        kev_w_shift(KEY_T, event);
    }
}

KF(U) {
    switch (tl) {
    case TL_NEO:
        kev_w_shift(KEY_A, event);
        break;
    default:
        kev_w_shift(KEY_U, event);
    }
}

KF(V) {
    switch (tl) {
    case TL_NEO:
        kev_w_shift(KEY_W, event);
        break;
    default:
        kev_w_shift(KEY_V, event);
    }
}

KF(W) {
    switch (tl) {
    case TL_NEO:
        kev_w_shift(KEY_T, event);
        break;
    default:
        kev_w_shift(KEY_W, event);
    }
}

KF(X) {
    switch (tl) {
    case TL_NEO:
        kev_w_shift(KEY_Q, event);
        break;
    default:
        kev_w_shift(KEY_X, event);
    }
}

KF(Y) {
    switch (tl) {
    case TL_NEO:
        kev_w_shift(KEY_QUOTE, event);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kev_w_shift(KEY_Z, event);
        break;
    default:
        kev_w_shift(KEY_Y, event);
    }
}

KF(Z) {
    switch (tl) {
    case TL_NEO:
        kev_w_shift(KEY_B, event);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kev_w_shift(KEY_Y, event);
        break;
    default:
        kev_w_shift(KEY_Z, event);
    }
}

KF(AUML) {
    switch (tl) {
    case TL_NEO:
        kev_w_shift(KEY_C, event);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kev_w_shift(KEY_QUOTE, event);
        break;
    default:
        kev_TODO();
    }
}

KF(OUML) {
    switch (tl) {
    case TL_NEO:
        kev_w_shift(KEY_X, event);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kev_w_shift(KEY_SEMICOLON, event);
        break;
    default:
        kev_TODO();
    }
}

KF(UUML) {
    switch (tl) {
    case TL_NEO:
        kev_w_shift(KEY_Z, event);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kev_w_shift(KEY_LEFT_BRACE, event);
        break;
    default:
        kev_TODO();
    }
}

KF(ESZETT) {
    switch (tl) {
    case TL_NEO:
        kev_w_shift(KEY_LEFT_BRACE, event);
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
        kev_level3(KEY_H, event);
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

KF(dash) {
    switch (tl) {
    case TL_NEO:
        kev_level3(KEY_L, event);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kev_plain(KEY_SLASH, event);
        break;
    default:
        kev_plain(KEY_MINUS, event);
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
        kev_TODO();
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
        kev_TODO();
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
        kev_TODO();
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
    default:
        kev_TODO();
    }
}

KF(cent_currency) {
    kev_TODO();
}

KF(pound_currency) {
    kev_TODO();
}

KF(yen_currency) {
    kev_TODO();
}

KF(currency_sign) {
    kev_TODO();
}

KF(mdash) {
    kev_TODO();
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
    kev_TODO();
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
    kev_TODO();
}

KF(guillemet_dbl_gt) {
    kev_TODO();
}

KF(guillemet_sgl_gt) {
    kev_TODO();
}

KF(guillemet_dbl_lt) {
    kev_TODO();
}

KF(guillemet_sgl_lt) {
    kev_TODO();
}

KF(low9quote_dbl) {
    kev_TODO();
}

KF(low9quote_sgl) {
    kev_TODO();
}

KF(6quote_dbl) {
    kev_TODO();
}

KF(6quote_sgl) {
    kev_TODO();
}

KF(9quote_dbl) {
    kev_TODO();
}

KF(9quote_sgl) {
    kev_TODO();
}

KF(ellipsis) {
    kev_TODO();
}

KF(inverted_exclamation_mark) {
    kev_TODO();
}

KF(long_s) {
    kev_TODO();
}

KF(minus) {
    kev_TODO();
}

KF(inverted_question_mark) {
    kev_TODO();
}

KF(ndash) {
    kev_TODO();
}

KF(bullet) {
    kev_TODO();
}



// dead keys

KF(dead_grave) {
    kev_TODO();
}

KF(dead_cedilla) {
    kev_TODO();
}

KF(dead_ring) {
    kev_TODO();
}

KF(dead_umlaut) {
    kev_TODO();
}

KF(dead_circumfex) {
    kev_TODO();
}

KF(dead_caron) {
    kev_TODO();
}

KF(dead_dot) {
    kev_TODO();
}

KF(dead_acute) {
    kev_TODO();
}

KF(dead_perispomene) {
    kev_TODO();
}

KF(dead_bar) {
    kev_TODO();
}

KF(dead_double_acute) {
    kev_TODO();
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

KF(numpad_slash) {
    switch (tl) {
    default:
        kev_allow_modifiers(KEYPAD_SLASH, event);
    }
}

KF(numpad_asterisk) {
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

KF(numpad_comma) {
    switch (tl) {
    case TL_NEO:
    case TL_DE:
    case TL_DE_NODEAD:
        kev_w_shift(KEYPAD_PERIOD, event);
        break;
    default:
        kev_allow_modifiers(KEY_COMMA, event);
    }
}

KF(numpad_period) {
    switch (tl) {
    case TL_NEO:
    case TL_DE:
    case TL_DE_NODEAD:
        kev_w_shift(KEY_PERIOD, event);
        break;
    default:
        kev_allow_modifiers(KEYPAD_PERIOD, event);
    }
}

// function keys

KF(F1) {
    kev_TODO();
}

KF(F2) {
    kev_TODO();
}

KF(F3) {
    kev_TODO();
}

KF(F4) {
    kev_TODO();
}

KF(F5) {
    kev_TODO();
}

KF(F6) {
    kev_TODO();
}

KF(F7) {
    kev_TODO();
}

KF(F8) {
    kev_TODO();
}

KF(F9) {
    kev_TODO();
}

KF(F10) {
    kev_TODO();
}

KF(F11) {
    kev_TODO();
}

KF(F12) {
    kev_TODO();
}



// special keys

KF(undo) {
    kev_TODO();
}

KF(copy) {
    kev_TODO();
}

KF(paste) {
    kev_TODO();
}

KF(cut) {
    kev_TODO();
}

KF(forward) {
    kev_TODO();
}

KF(back) {
    kev_TODO();
}



keyrecord_t keymap[ROW_COUNT][2][COL_COUNT] = {
    // ROW_NUM (0x00-0x0F)
    {
        //ROW_NUM left (0x00-0x07)
        {
            // in contrast to neo layout, the key for the circumfex accent has been moved from the top left to the top right corner of the keyboard
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
            // 6
            {
                .type = KT_IGNORE_SHIFTLOCK,
                .kf = { kf_6, kf_dollar, kf_cent_currency, kf_pound_currency, kf_F6, },
            },
        }, // controller (left/right side)
        //ROW_NUM right (0x08-0x0F)
        {
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
                .kf = { kf_9, kf_6quote_dbl, kf_6quote_sgl, kf_numpad_slash, kf_F9, },
            },
            // 0
            {
                .type = KT_IGNORE_SHIFTLOCK,
                .kf = { kf_0, kf_9quote_dbl, kf_9quote_sgl, kf_numpad_asterisk, kf_F10, },
            },
            // -
            {
                .type = KT_IGNORE_SHIFTLOCK,
                .kf = { kf_dash, kf_mdash, kf_nop, kf_numpad_minus, kf_F11, },
            },
            // ò
            {
                .type = KT_IGNORE_SHIFTLOCK,
                .kf = { kf_dead_grave, kf_dead_cedilla, kf_dead_ring, kf_dead_umlaut, kf_F12, },
            },
            // ô
            {
                .type = KT_IGNORE_SHIFTLOCK,
                .kf = { kf_dead_circumfex, kf_dead_caron, kf_TODO, kf_dead_dot, kf_nop, },
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
                .type = KT_PLAIN,
                .kf = { kf_x, kf_X, kf_ellipsis, kf_page_up, NULL, },
            },
            // V
            {
                .type = KT_PLAIN,
                .kf = { kf_v, kf_V, kf_underscore, kf_backspace, NULL, },
            },
            // L
            {
                .type = KT_PLAIN,
                .kf = { kf_l, kf_L, kf_bracket_left, kf_up, NULL, },
            },
            // C
            {
                .type = KT_PLAIN,
                .kf = { kf_c, kf_C, kf_bracket_right, kf_delete, NULL, },
            },
            // W
            {
                .type = KT_PLAIN,
                .kf = { kf_w, kf_W, kf_caret, kf_page_down, NULL, },
            },
        }, // controller (left/right side)
        //ROW_TOP right (0x18-0x1F)
        {
            // K
            {
                .type = KT_PLAIN,
                .kf = { kf_k, kf_K, kf_exclamation_mark, kf_inverted_exclamation_mark, kf_back, },
            },
            // H
            {
                .type = KT_PLAIN,
                .kf = { kf_h, kf_H, kf_chevron_left, kf_numpad_7, kf_TODO /*left dblclick*/, },
            },
            // G
            {
                .type = KT_PLAIN,
                .kf = { kf_g, kf_G, kf_chevron_right, kf_numpad_8, kf_TODO /*mid dblclick*/, },
            },
            // F
            {
                .type = KT_PLAIN,
                .kf = { kf_f, kf_F, kf_equals, kf_numpad_9, kf_TODO /*right dblclick*/, },
            },
            // Q
            {
                .type = KT_PLAIN,
                .kf = { kf_q, kf_Q, kf_ampersand, kf_numpad_plus, kf_forward, },
            },
            // ß
            {
                .type = KT_PLAIN,
                .kf = { kf_eszett, kf_ESZETT, kf_long_s, kf_minus, kf_TODO, },
            },
            // ó
            {
                .type = KT_IGNORE_SHIFTLOCK,
                .kf = { kf_dead_acute, kf_dead_perispomene, kf_dead_bar, kf_dead_double_acute, kf_TODO, },
            },
        }, // controller (left/right side)
    }, // row

    
    // ROW_HOME
    {
        //ROW_HOME left
        {
            // level3 modifier
            {
                .type = KT_LEVELMOD,
                .kf = { kf_level3mod_left },
            },
            // U
            {
                .type = KT_PLAIN,
                .kf = { kf_u, kf_U, kf_backslash, kf_home, },
            },
            // I
            {
                .type = KT_PLAIN,
                .kf = { kf_i, kf_I, kf_slash, kf_left, },
            },
            // A
            {
                .type = KT_PLAIN,
                .kf = { kf_a, kf_A, kf_brace_left, kf_down, },
            },
            // E
            {
                .type = KT_PLAIN,
                .kf = { kf_e, kf_E, kf_brace_right, kf_right, },
            },
            // O
            {
                .type = KT_PLAIN,
                .kf = { kf_o, kf_O, kf_asterisk, kf_end, },
            },
        }, // controller (left/right side)
        //ROW_HOME right
        {
            // S
            {
                .type = KT_PLAIN,
                .kf = { kf_s, kf_S, kf_question_mark, kf_inverted_question_mark, kf_TODO, },
            },
            // N
            {
                .type = KT_PLAIN,
                .kf = { kf_n, kf_N, kf_parentheses_left, kf_numpad_4, kf_TODO /*left click*/, },
            },
            // R
            {
                .type = KT_PLAIN,
                .kf = { kf_r, kf_R, kf_parentheses_right, kf_numpad_5, kf_TODO /*mid click*/, },
            },
            // T
            {
                .type = KT_PLAIN,
                .kf = { kf_t, kf_T, kf_dash, kf_numpad_6, kf_TODO /*right click*/, },
            },
            // D
            {
                .type = KT_PLAIN,
                .kf = { kf_d, kf_D, kf_colon, kf_numpad_comma, kf_TODO, },
            },
            // Y
            {
                .type = KT_PLAIN,
                .kf = { kf_y, kf_Y, kf_at, kf_numpad_period, kf_TODO, },
            },
            // level3 modifier
            {
                .type = KT_LEVELMOD,
                .kf = { kf_level3mod_right },
            },
        }, // controller (left/right side)
    }, // row

    
    // ROW_BTM
    {
        //ROW_BTM left
        {
            // level2 modifier
            {
                .type = KT_LEVELMOD,
                .kf = { kf_level2mod_left },
            },
            // Ü
            {
                .type = KT_PLAIN,
                .kf = { kf_uuml, kf_UUML, kf_hash, kf_escape, },
            },
            // Ö
            {
                .type = KT_PLAIN,
                .kf = { kf_ouml, kf_OUML, kf_dollar, kf_tab, },
            },
            // Ä
            {
                .type = KT_PLAIN,
                .kf = { kf_auml, kf_AUML, kf_pipe, kf_insert, },
            },
            // P
            {
                .type = KT_PLAIN,
                .kf = { kf_p, kf_P, kf_tilde, kf_return, },
            },
            // Z
            {
                .type = KT_PLAIN,
                .kf = { kf_z, kf_Z, kf_backtick, kf_undo, },
            },
        }, // controller (left/right side)
        //ROW_BTM right
        {
            // B
            {
                .type = KT_PLAIN,
                .kf = { kf_b, kf_B, kf_plus, kf_colon, kf_TODO, },
            },
            // M
            {
                .type = KT_PLAIN,
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
                .type = KT_PLAIN,
                .kf = { kf_j, kf_J, kf_semicolon, kf_semicolon, kf_TODO, },
            },
            // level2 modifier
            {
                .type = KT_LEVELMOD,
                .kf = { kf_level2mod_right },
            },
        }, // controller (left/right side)
    }, // row

    
    // ROW_SPACE
    {
        //ROW_SPACE left
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
                .type = KT_IGNORE_LEVEL,
                .kf = { kf_prev_target_layout },
            },
            // unused
            {
                .type = KT_DUMB,
                .kf = { NULL },
            },
            // space
            {
                .type = KT_IGNORE_LEVEL,
                .kf = { kf_space },
            },
            // left Alt
            {
                .type = KT_IGNORE_LEVEL,
                .kf = { kf_alt_left },
            },
        }, // controller (left/right side)
        //ROW_SPACE right
        {
            // right Alt
            {
                .type = KT_IGNORE_LEVEL,
                .kf = { kf_alt_right },
            },
            // level4 modifier
            {
                .type = KT_LEVELMOD,
                .kf = { kf_level4mod_right },
            },
            // space, numpad-zero
            {
                .type = KT_PLAIN,
                .kf = { kf_space, kf_space, kf_space, kf_numpad_0, kf_nop, },
            },
            // switch target layout // TODO preliminary use of this key
            {
                .type = KT_IGNORE_LEVEL,
                .kf = { kf_next_target_layout },
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
