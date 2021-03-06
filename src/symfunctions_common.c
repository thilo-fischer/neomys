/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

/**
 * @file
 * Commenly used symbol functions. 
 */

#include "../teensy_codelib/usb_keyboard/usb_keyboard.h"
#include "usb_keyboard.h"

#include "keyhandling.h"
#include "sendkeys.h"
#include "userlayout.h" // SF macro
#include "targetlayout.h"

#include "debug.h"


// FIXME neomys-specific

enum neo_levels_e {
    // As we use level values as array indices, LEVEL1 must have value 0x00. (Using value 0x01 for LEVEL1 would make reading binary data during debugging somewhat more intuitive, but makes using values for array indexing more error prone.)
    LEVEL1 = 0x00,
    LEVEL2,
    LEVEL3,
    LEVEL4,
    LEVEL4_MOUSE,
    LEVEL5,
    LEVEL6,
    LEVEL_COUNT
};

enum neo_level_modifiers_e {
    LM2_L = 0x01,
    LM2_R = 0x02,
    LM3_L = 0x04,
    LM3_R = 0x08,
    LM4_L = 0x10,
    LM4_R = 0x20,
};

dbg_define_msg(SF_DBG_STATUS, 0xB0,
               "tgtlo:%02hhX", // XXX deprecated => lvlmods:%02hhX lcklvl:%02hhX",
               sizeof(targetlayout_t) // XXX deprecated =>, sizeof(level_modifiers), sizeof(locked_level)
               );

void symfunctions_status_dbg() {
  dbg_debug(SF_DBG_STATUS, g_current_targetlayout); // XXX deprecated => , level_modifiers, locked_level);
}


SF(nop) {}

dbg_define_msg(SF_NOT_YET_IMPLEMENTED, 0x1C, "no SF yet");

SF(TODO) {
  dbg_warn(SF_NOT_YET_IMPLEMENTED, 0);
}

dbg_define_msg(TARGET_LAYOUT, 0xC0,
               "target layout: %02hhX", sizeof(targetlayout_t));

void adp_ind_targetlayout(); // FIXME include appropriate header file

SF(next_target_layout) {
    if (event == KS_PRESS) {
        ++g_current_targetlayout;
        if (g_current_targetlayout == TGL_COUNT) {
            g_current_targetlayout = TGL_NEO;
        }
        dbg_info(TARGET_LAYOUT, g_current_targetlayout);
        adp_ind_targetlayout();
    }
}

SF(prev_target_layout) {
    if (event == KS_PRESS) {
        if (g_current_targetlayout == TGL_NEO) {
            g_current_targetlayout = TGL_COUNT;
        }
        --g_current_targetlayout;
        dbg_info(TARGET_LAYOUT, g_current_targetlayout);
        adp_ind_targetlayout();
    }
}

// statechange drivers for regular keyboards

SF(numlock) {
    switch (targetlayout) {
    default:
        kev_allow_modifiers(KEY_NUM_LOCK, event);
    }    
}

SF(scrolllock) {
    switch (targetlayout) {
    default:
        kev_allow_modifiers(KEY_SCROLL_LOCK, event);
    }    
}

SF(capslock) {
    switch (targetlayout) {
    default:
        kev_allow_modifiers(KEY_CAPS_LOCK, event);
    }    
}

SF(shift_left) {
  // Inform the host about the shift modifier event -- any host will understand the shift modifier and users will want to be able to use e.g. shift+mouseclick shift+return.
  kev_modifier(KEY_LEFT_SHIFT, event);
}

SF(shift_right) {
  // Inform the host about the shift modifier event -- any host will understand the shift modifier and users will want to be able to use e.g. shift+mouseclick shift+return.
  kev_modifier(KEY_RIGHT_SHIFT, event);
}

// FIXME neomys-specific => move to symfunctions_neomys*.c

static bool send_virtual_mod(targetlayout_t targetlayout) {
  return targetlayout == TGL_NEO;
}

SF(level3mod_left) {
  if (send_virtual_mod(targetlayout))
    kev_virtual_modifier(KEY_CAPS_LOCK, event);
}

SF(level3mod_right) {
  if (send_virtual_mod(targetlayout))
    kev_virtual_modifier(KEY_BACKSLASH, event);
}

SF(level4mod_left) {
  if (send_virtual_mod(targetlayout))
    // FIXME Inform even a Neo host about the modifier event only if we have not a LEVEL4_MOUSE-lock. (Neo host does not know about LEVEL4_MOUSE and would take wrong actions.)
    kev_virtual_modifier(KEY_ISO_EXTRA, event);
}

SF(level4mod_right) {
  // Do not inform any host about this modifier event, also Neo host does not know about LEVEL4_MOUSE.
}

// modifiers

SF(ctrl_left) {
    switch (targetlayout) {
    default:
        kev_modifier(KEY_LEFT_CTRL, event);
    }
}

SF(ctrl_right) {
    switch (targetlayout) {
    default:
        kev_modifier(KEY_RIGHT_CTRL, event);
    }
}

SF(alt_left) {
    switch (targetlayout) {
    default:
        kev_modifier(KEY_LEFT_ALT, event);
    }
}

SF(alt_right) {
    switch (targetlayout) {
    case TGL_NEO:
    case TGL_DE:
    case TGL_DE_NODEAD:
        kev_modifier(KEY_ALT, event);
        break;
    default:
        // KEY_RIGHT_ALT is AltGr key on some target layouts and may affect the level => use KEY_ALT instead of KEY_RIGHT_ALT to avoid further confusion ...
        // kev_modifier(KEY_RIGHT_ALT, event);
        kev_modifier(KEY_ALT, event);
    }
}

SF(gui_left) {
    switch (targetlayout) {
    default:
        kev_modifier(KEY_LEFT_GUI, event);
    }
}

SF(gui_right) {
    switch (targetlayout) {
    default:
        kev_modifier(KEY_RIGHT_GUI, event);
    }
}


// numbers

SF(1) {
    switch (targetlayout) {
    default:
        kev_plain(KEY_1, event);
    }
}

SF(2) {
    switch (targetlayout) {
    default:
        kev_plain(KEY_2, event);
    }
}

SF(3) {
    switch (targetlayout) {
    default:
        kev_plain(KEY_3, event);
    }
}

SF(4) {
    switch (targetlayout) {
    default:
        kev_plain(KEY_4, event);
    }
}

SF(5) {
    switch (targetlayout) {
    default:
        kev_plain(KEY_5, event);
    }
}

SF(6) {
    switch (targetlayout) {
    default:
        kev_plain(KEY_6, event);
    }
}

SF(7) {
    switch (targetlayout) {
    default:
        kev_plain(KEY_7, event);
    }
}

SF(8) {
    switch (targetlayout) {
    default:
        kev_plain(KEY_8, event);
    }
}

SF(9) {
    switch (targetlayout) {
    default:
        kev_plain(KEY_9, event);
    }
}

SF(0) {
    switch (targetlayout) {
    default:
        kev_plain(KEY_0, event);
    }
}

// letters
// upper case

SF(A) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level2(KEY_D, event);
        break;
    default:
        kev_w_shift(KEY_A, event);
    }
}

SF(B) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level2(KEY_N, event);
        break;
    default:
        kev_w_shift(KEY_B, event);
    }
}

SF(C) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level2(KEY_R, event);
        break;
    default:
        kev_w_shift(KEY_C, event);
    }
}

SF(D) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level2(KEY_SEMICOLON, event);
        break;
    default:
        kev_w_shift(KEY_D, event);
    }
}

SF(E) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level2(KEY_F, event);
        break;
    default:
        kev_w_shift(KEY_E, event);
    }
}

SF(F) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level2(KEY_O, event);
        break;
    default:
        kev_w_shift(KEY_F, event);
    }
}

SF(G) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level2(KEY_I, event);
        break;
    default:
        kev_w_shift(KEY_G, event);
    }
}

SF(H) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level2(KEY_U, event);
        break;
    default:
        kev_w_shift(KEY_H, event);
    }
}

SF(I) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level2(KEY_S, event);
        break;
    default:
        kev_w_shift(KEY_I, event);
    }
}

SF(J) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level2(KEY_SLASH, event);
        break;
    default:
        kev_w_shift(KEY_J, event);
    }
}

SF(K) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level2(KEY_Y, event);
        break;
    default:
        kev_w_shift(KEY_K, event);
    }
}

SF(L) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level2(KEY_E, event);
        break;
    default:
        kev_w_shift(KEY_L, event);
    }
}

SF(M) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level2(KEY_M, event);
        break;
    default:
        kev_w_shift(KEY_M, event);
    }
}

SF(N) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level2(KEY_J, event);
        break;
    default:
        kev_w_shift(KEY_N, event);
    }
}

SF(O) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level2(KEY_G, event);
        break;
    default:
        kev_w_shift(KEY_O, event);
    }
}

SF(P) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level2(KEY_V, event);
        break;
    default:
        kev_w_shift(KEY_P, event);
    }
}

SF(Q) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level2(KEY_P, event);
        break;
    default:
        kev_w_shift(KEY_Q, event);
    }
}

SF(R) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level2(KEY_K, event);
        break;
    default:
        kev_w_shift(KEY_R, event);
    }
}

SF(S) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level2(KEY_H, event);
        break;
    default:
        kev_w_shift(KEY_S, event);
    }
}

SF(T) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level2(KEY_L, event);
        break;
    default:
        kev_w_shift(KEY_T, event);
    }
}

SF(U) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level2(KEY_A, event);
        break;
    default:
        kev_w_shift(KEY_U, event);
    }
}

SF(V) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level2(KEY_W, event);
        break;
    default:
        kev_w_shift(KEY_V, event);
    }
}

SF(W) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level2(KEY_T, event);
        break;
    default:
        kev_w_shift(KEY_W, event);
    }
}

SF(X) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level2(KEY_Q, event);
        break;
    default:
        kev_w_shift(KEY_X, event);
    }
}

SF(Y) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level2(KEY_QUOTE, event);
        break;
    case TGL_DE:
    case TGL_DE_NODEAD:
    case TGL_DE_APPLE:
        kev_w_shift(KEY_Z, event);
        break;
    default:
        kev_w_shift(KEY_Y, event);
    }
}

SF(Z) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level2(KEY_B, event);
        break;
    case TGL_DE:
    case TGL_DE_NODEAD:
    case TGL_DE_APPLE:
        kev_w_shift(KEY_Y, event);
        break;
    default:
        kev_w_shift(KEY_Z, event);
    }
}

SF(AUML) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level2(KEY_C, event);
        break;
    case TGL_DE:
    case TGL_DE_NODEAD:
    case TGL_DE_APPLE:
        kev_w_shift(KEY_QUOTE, event);
        break;
    default:
        kev_TODO();
    }
}

SF(OUML) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level2(KEY_X, event);
        break;
    case TGL_DE:
    case TGL_DE_NODEAD:
    case TGL_DE_APPLE:
        kev_w_shift(KEY_SEMICOLON, event);
        break;
    default:
        kev_TODO();
    }
}

SF(UUML) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level2(KEY_Z, event);
        break;
    case TGL_DE:
    case TGL_DE_NODEAD:
    case TGL_DE_APPLE:
        kev_w_shift(KEY_LEFT_BRACE, event);
        break;
    default:
        kev_TODO();
    }
}

SF(ESZETT) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level2(KEY_LEFT_BRACE, event);
        break;
    default:
        kev_TODO();
    }
}

// letters
// lower case

SF(a) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_plain(KEY_D, event);
        break;
    default:
        kev_plain(KEY_A, event);
    }
}

SF(b) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_plain(KEY_N, event);
        break;
    default:
        kev_plain(KEY_B, event);
    }
}

SF(c) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_plain(KEY_R, event);
        break;
    default:
        kev_plain(KEY_C, event);
    }
}

SF(d) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_plain(KEY_SEMICOLON, event);
        break;
    default:
        kev_plain(KEY_D, event);
    }
}

SF(e) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_plain(KEY_F, event);
        break;
    default:
        kev_plain(KEY_E, event);
    }
}

SF(f) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_plain(KEY_O, event);
        break;
    default:
        kev_plain(KEY_F, event);
    }
}

SF(g) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_plain(KEY_I, event);
        break;
    default:
        kev_plain(KEY_G, event);
    }
}

SF(h) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_plain(KEY_U, event);
        break;
    default:
        kev_plain(KEY_H, event);
    }
}

SF(i) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_plain(KEY_S, event);
        break;
    default:
        kev_plain(KEY_I, event);
    }
}

SF(j) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_plain(KEY_SLASH, event);
        break;
    default:
        kev_plain(KEY_J, event);
    }
}

SF(k) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_plain(KEY_Y, event);
        break;
    default:
        kev_plain(KEY_K, event);
    }
}

SF(l) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_plain(KEY_E, event);
        break;
    default:
        kev_plain(KEY_L, event);
    }
}

SF(m) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_plain(KEY_M, event);
        break;
    default:
        kev_plain(KEY_M, event);
    }
}

SF(n) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_plain(KEY_J, event);
        break;
    default:
        kev_plain(KEY_N, event);
    }
}

SF(o) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_plain(KEY_G, event);
        break;
    default:
        kev_plain(KEY_O, event);
    }
}

SF(p) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_plain(KEY_V, event);
        break;
    default:
        kev_plain(KEY_P, event);
    }
}

SF(q) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_plain(KEY_P, event);
        break;
    default:
        kev_plain(KEY_Q, event);
    }
}

SF(r) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_plain(KEY_K, event);
        break;
    default:
        kev_plain(KEY_R, event);
    }
}

SF(s) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_plain(KEY_H, event);
        break;
    default:
        kev_plain(KEY_S, event);
    }
}

SF(t) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_plain(KEY_L, event);
        break;
    default:
        kev_plain(KEY_T, event);
    }
}

SF(u) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_plain(KEY_A, event);
        break;
    default:
        kev_plain(KEY_U, event);
    }
}

SF(v) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_plain(KEY_W, event);
        break;
    default:
        kev_plain(KEY_V, event);
    }
}

SF(w) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_plain(KEY_T, event);
        break;
    default:
        kev_plain(KEY_W, event);
    }
}

SF(x) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_plain(KEY_Q, event);
        break;
    default:
        kev_plain(KEY_X, event);
    }
}

SF(y) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_plain(KEY_QUOTE, event);
        break;
    case TGL_DE:
    case TGL_DE_NODEAD:
    case TGL_DE_APPLE:
        kev_plain(KEY_Z, event);
        break;
    default:
        kev_plain(KEY_Y, event);
    }
}

SF(z) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_plain(KEY_B, event);
        break;
    case TGL_DE:
    case TGL_DE_NODEAD:
    case TGL_DE_APPLE:
        kev_plain(KEY_Y, event);
        break;
    default:
        kev_plain(KEY_Z, event);
    }
}

SF(auml) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_plain(KEY_C, event);
        break;
    case TGL_DE:
    case TGL_DE_NODEAD:
    case TGL_DE_APPLE:
        kev_plain(KEY_QUOTE, event);
        break;
    default:
        kev_TODO();
    }
}

SF(ouml) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_plain(KEY_X, event);
        break;
    case TGL_DE:
    case TGL_DE_NODEAD:
    case TGL_DE_APPLE:
        kev_plain(KEY_SEMICOLON, event);
        break;
    default:
        kev_TODO();
    }
}

SF(uuml) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_plain(KEY_Z, event);
        break;
    case TGL_DE:
    case TGL_DE_NODEAD:
    case TGL_DE_APPLE:
        kev_plain(KEY_LEFT_BRACE, event);
        break;
    default:
        kev_TODO();
    }
}

SF(eszett) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_plain(KEY_LEFT_BRACE, event);
        break;
    case TGL_DE:
    case TGL_DE_NODEAD:
    case TGL_DE_APPLE:
        kev_plain(KEY_MINUS, event);
        break;
    default:
        kev_TODO();
    }
}

// basic punctuation characters (in ASCII order)

SF(space) {
    kev_allow_modifiers(KEY_SPACE, event);
}

SF(exclamation_mark) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level3(KEY_Y, event);
        break;
    default:
        kev_w_shift(KEY_1, event);
    }
}

SF(straight_dbl_quote) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level3(KEY_COMMA, event);
        break;
    case TGL_DE:
    case TGL_DE_NODEAD:
    case TGL_DE_APPLE:
        kev_w_shift(KEY_2, event);
        break;
    default:
        kev_w_shift(KEY_QUOTE, event);
    }
}

SF(hash) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level3(KEY_Z, event);
        break;
    case TGL_DE:
    case TGL_DE_NODEAD:
    case TGL_DE_APPLE:
        kev_plain(KEY_BACKSLASH, event);
        break;
    default:
        kev_w_shift(KEY_3, event);
    }
}

SF(dollar) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level3(KEY_X, event);
        break;
    default:
        kev_w_shift(KEY_4, event);
    }
}

SF(percent) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level3(KEY_M, event);
        break;
    default:
        kev_w_shift(KEY_5, event);
    }
}

SF(ampersand) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level3(KEY_P, event);
        break;
    default:
        kev_w_shift(KEY_6, event);
    }
}

SF(apostrophe) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level3(KEY_PERIOD, event);
        break;
    case TGL_DE:
    case TGL_DE_NODEAD:
    case TGL_DE_APPLE:
        kev_w_shift(KEY_BACKSLASH, event);
        break;
    default:
        kev_plain(KEY_QUOTE, event);
    }
}

SF(parentheses_left) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level3(KEY_J, event);
        break;
    case TGL_DE:
    case TGL_DE_NODEAD:
    case TGL_DE_APPLE:
        kev_w_shift(KEY_8, event);
        break;
    default:
        kev_w_shift(KEY_9, event);
    }
}

SF(parentheses_right) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level3(KEY_K, event);
        break;
    case TGL_DE:
    case TGL_DE_NODEAD:
    case TGL_DE_APPLE:
        kev_w_shift(KEY_9, event);
        break;
    default:
        kev_w_shift(KEY_0, event);
    }
}

SF(asterisk) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level3(KEY_G, event);
        break;
    case TGL_DE:
    case TGL_DE_NODEAD:
    case TGL_DE_APPLE:
        kev_w_shift(KEY_RIGHT_BRACE, event);
        break;
    default:
        kev_w_shift(KEY_8, event);
    }
}

SF(plus) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level3(KEY_N, event);
        break;
    case TGL_DE:
    case TGL_DE_NODEAD:
    case TGL_DE_APPLE:
        kev_plain(KEY_RIGHT_BRACE, event);
        break;
    default:
        kev_w_shift(KEY_EQUAL, event);
    }
}

SF(comma) {
    switch (targetlayout) {
    default:
        kev_plain(KEY_COMMA, event);
    }
}

SF(dash_neo_lvl1) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_plain(KEY_MINUS, event);
        break;
    case TGL_DE:
    case TGL_DE_NODEAD:
    case TGL_DE_APPLE:
        kev_plain(KEY_SLASH, event);
        break;
    default:
        kev_plain(KEY_MINUS, event);
    }
}

SF(dash_neo_lvl3) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level3(KEY_L, event);
        break;
    default:
        sf_dash_neo_lvl1(targetlayout, event);
    }
}

SF(period) {
    switch (targetlayout) {
    default:
        kev_plain(KEY_PERIOD, event);
    }
}

SF(slash) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level3(KEY_S, event);
        break;
    case TGL_DE:
    case TGL_DE_NODEAD:
    case TGL_DE_APPLE:
        kev_w_shift(KEY_7, event);
        break;
    default:
        kev_plain(KEY_SLASH, event);
    }
}


SF(colon) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level3(KEY_SEMICOLON, event);
        break;
    case TGL_DE:
    case TGL_DE_NODEAD:
    case TGL_DE_APPLE:
        kev_w_shift(KEY_PERIOD, event);
        break;
    default:
        kev_w_shift(KEY_SEMICOLON, event);
    }
}

SF(semicolon) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level3(KEY_SLASH, event);
        break;
    case TGL_DE:
    case TGL_DE_NODEAD:
    case TGL_DE_APPLE:
        kev_w_shift(KEY_COMMA, event);
        break;
    default:
        kev_plain(KEY_SEMICOLON, event);
    }
}

SF(chevron_left) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level3(KEY_U, event);
        break;
    case TGL_DE:
    case TGL_DE_NODEAD:
    case TGL_DE_APPLE:
        // Apple: OsX will open a dialog to identify the keyboard when connected to the Mac the first time and ask to press the key in between the shift and the Y key -- the ISO_EXTRA key. Switch the neomys to APPLE host layout and press the keys to produce a '<' character (Mod3+H). Otherwise, the '<' and '>' characters won't work correctly. => FIXME: document this accordingly in "end user documentation"
        kev_plain(KEY_ISO_EXTRA, event);
        break;
    default:
        kev_w_shift(KEY_COMMA, event);
    }
}

SF(equals) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level3(KEY_O, event);
        break;
    case TGL_DE:
    case TGL_DE_NODEAD:
    case TGL_DE_APPLE:
        kev_w_shift(KEY_0, event);
        break;
    default:
        kev_plain(KEY_EQUAL, event);
    }
}

SF(chevron_right) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level3(KEY_I, event);
        break;
    case TGL_DE:
    case TGL_DE_NODEAD:
    case TGL_DE_APPLE:
        kev_w_shift(KEY_ISO_EXTRA, event);
        break;
    default:
        kev_w_shift(KEY_PERIOD, event);
    }
}

SF(question_mark) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level3(KEY_H, event);
        break;
    case TGL_DE:
    case TGL_DE_NODEAD:
    case TGL_DE_APPLE:
        kev_w_shift(KEY_MINUS, event);
        break;
    default:
        kev_w_shift(KEY_SLASH, event);
    }
}

SF(at) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level3(KEY_QUOTE, event);
        break;
    case TGL_DE:
    case TGL_DE_NODEAD:
        kev_w_altgr(KEY_Q, event);
        break;
    case TGL_DE_APPLE:
        kev_w_alt(KEY_L, event);
        break;
    default:
        kev_w_shift(KEY_2, event);
    }
}


SF(bracket_left) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level3(KEY_E, event);
        break;
    case TGL_DE:
    case TGL_DE_NODEAD:
        kev_w_altgr(KEY_8, event);
        break;
    case TGL_DE_APPLE:
        kev_w_alt(KEY_5, event);
        break;
    default:
        kev_plain(KEY_LEFT_BRACE, event);
    }
}

SF(backslash) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level3(KEY_A, event);
        break;
    case TGL_DE:
    case TGL_DE_NODEAD:
        kev_w_altgr(KEY_MINUS, event);
        break;
    case TGL_DE_APPLE:
        kev_w_shift_alt(KEY_7, event);
        break;
    default:
        kev_plain(KEY_BACKSLASH, event);
    }
}

SF(bracket_right) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level3(KEY_R, event);
        break;
    case TGL_DE:
    case TGL_DE_NODEAD:
        kev_w_altgr(KEY_9, event);
        break;
    case TGL_DE_APPLE:
        kev_w_alt(KEY_6, event);
        break;
    default:
        kev_plain(KEY_RIGHT_BRACE, event);
    }
}

SF(caret) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level3(KEY_T, event);
        break;
    case TGL_DE:
        kev_plain(KEY_TILDE, event);
        kev_plain(KEY_SPACE, event);
        break;
    case TGL_DE_NODEAD:
        kev_plain(KEY_TILDE, event);
        break;
    case TGL_DE_APPLE:
        // kev_w_shift_alt(KEY_K, event); => produces the accent sign ontop of nothing
        // To get ASCII char 0x5E, we need to combine the caret dead key with space:
        kev_w_shift_alt(KEY_6, event);
        kev_plain(KEY_SPACE, event);        
        break;
    default:
        kev_w_shift(KEY_6, event);
    }
}

SF(underscore) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level3(KEY_W, event);
        break;
    case TGL_DE:
    case TGL_DE_NODEAD:
    case TGL_DE_APPLE:
        kev_w_shift(KEY_SLASH, event);
        break;
    default:
        kev_w_shift(KEY_MINUS, event);
    }
}

SF(backtick) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level3(KEY_B, event);
        break;
    case TGL_DE:
    case TGL_DE_APPLE: // This was not working properly on my Macbook once -- but since the chevrons have been fixed, backtick is also fixed. XXX reproduce backtick issue and verify it is fixed as the chevron problem when keyboard is properly detected.
        kev_w_shift(KEY_EQUAL, event);
        kev_plain  (KEY_SPACE, event);
        break;
    case TGL_DE_NODEAD:
        kev_w_shift(KEY_EQUAL, event);
        break;
    default:
        kev_w_shift(KEY_TILDE, event);
    }
}


SF(brace_left) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level3(KEY_D, event);
        break;
    case TGL_DE:
    case TGL_DE_NODEAD:
        kev_w_altgr(KEY_7, event);
        break;
    case TGL_DE_APPLE:
        kev_w_alt(KEY_8, event);
        break;
    default:
        kev_w_shift(KEY_LEFT_BRACE, event);
    }
}

SF(pipe) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level3(KEY_C, event);
        break;
    case TGL_DE:
    case TGL_DE_NODEAD:
        kev_w_altgr(KEY_ISO_EXTRA, event);
        break;
    case TGL_DE_APPLE:
        kev_w_alt(KEY_7, event);
        break;
    default:
        kev_w_shift(KEY_BACKSLASH, event);
    }
}

SF(brace_right) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level3(KEY_F, event);
        break;
    case TGL_DE:
    case TGL_DE_NODEAD:
        kev_w_altgr(KEY_0, event);
        break;
    case TGL_DE_APPLE:
        kev_w_alt(KEY_9, event);
        break;
    default:
        kev_w_shift(KEY_RIGHT_BRACE, event);
    }
}

SF(tilde) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level3(KEY_V, event);
        break;
    case TGL_DE:
    case TGL_DE_NODEAD:
        kev_w_altgr(KEY_RIGHT_BRACE, event);
        break;
    case TGL_DE_APPLE:
        // kev_w_shift_alt(KEY_8, event); => produces the accent sign ontop of nothing
        // To get ASCII char 0x7E, we need to combine the tilde dead key with space:
        kev_w_alt(KEY_N, event);
        kev_plain(KEY_SPACE, event);
        break;
    default:
        kev_w_shift(KEY_TILDE, event);
    }
}


// enhanced punctuation characters (in order of appearance on the Neo layout from left to right, from top to bottom)

SF(degree) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level2(KEY_1, event);
        break;
    case TGL_DE:
    case TGL_DE_NODEAD:
    case TGL_DE_APPLE:
        kev_w_shift(KEY_TILDE, event);
        break;
    default:
        kev_TODO();
    }
}

SF(sectionsign) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level2(KEY_2, event);
        break;
    case TGL_DE:
    case TGL_DE_NODEAD:
    case TGL_DE_APPLE:
        kev_w_shift(KEY_3, event);
        break;
    default:
        kev_TODO();
    }
}

SF(euro_currency) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level2(KEY_7, event);
        break;
    case TGL_DE:
    case TGL_DE_NODEAD:
        kev_w_altgr(KEY_E, event);
        break;
    case TGL_DE_APPLE:
        kev_w_alt(KEY_E, event);
        break;
    default:
        kev_TODO();
    }
}

SF(cent_currency) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level3(KEY_6, event);
        break;
    default:
        kev_TODO();
    }
}

SF(pound_currency) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level4(KEY_6, event);
        break;
    default:
        kev_TODO();
    }
}

SF(yen_currency) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level3(KEY_7, event);
        break;
    default:
        kev_TODO();
    }
}

SF(currency_sign) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level4(KEY_7, event);
        break;
    default:
        kev_TODO();
    }
}

// esoteric punctuation characters (in order of appearance on the Neo layout from left to right, from top to bottom)

SF(superscript1) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level3(KEY_1, event);
        break;
    default:
        kev_TODO();
    }
}

SF(superscript2) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level3(KEY_2, event);
        break;
    case TGL_DE:
    case TGL_DE_NODEAD:
        kev_w_altgr(KEY_2, event);
        break;
    default:
        kev_TODO();
    }
}

SF(script_small_l) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level2(KEY_3, event);
        break;
    default:
        kev_TODO();
    }
}

SF(superscript3) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level3(KEY_3, event);
        break;
    case TGL_DE:
    case TGL_DE_NODEAD:
        kev_w_altgr(KEY_3, event);
        break;
    default:
        kev_TODO();
    }
}

SF(numero_sign) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level4(KEY_3, event);
        break;
    default:
        kev_TODO();
    }
}

SF(guillemet_dbl_gt) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level2(KEY_4, event);
        break;
    default:
        kev_TODO();
    }
}

SF(guillemet_sgl_gt) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level3(KEY_4, event);
        break;
    default:
        kev_TODO();
    }
}

SF(guillemet_dbl_lt) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level2(KEY_5, event);
        break;
    default:
        kev_TODO();
    }
}

SF(guillemet_sgl_lt) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level3(KEY_5, event);
        break;
    default:
        kev_TODO();
    }
}

SF(low9quote_dbl) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level2(KEY_8, event);
        break;
    default:
        kev_TODO();
    }
}

SF(low9quote_sgl) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level3(KEY_8, event);
        break;
    default:
        kev_TODO();
    }
}

SF(6quote_dbl) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level2(KEY_9, event);
        break;
    default:
        kev_TODO();
    }
}

SF(6quote_sgl) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level3(KEY_9, event);
        break;
    default:
        kev_TODO();
    }
}

SF(9quote_dbl) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level2(KEY_0, event);
        break;
    default:
        kev_TODO();
    }
}

SF(9quote_sgl) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level3(KEY_0, event);
        break;
    default:
        kev_TODO();
    }
}

// Geviertstrich
SF(mdash) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level2(KEY_MINUS, event);
        break;
    default:
        kev_TODO();
    }
}

SF(ellipsis) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level3(KEY_Q, event);
        break;
    default:
        kev_TODO();
    }
}

SF(inverted_exclamation_mark) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level3(KEY_Y, event);
        break;
    default:
        kev_TODO();
    }
}

SF(long_s) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level3(KEY_LEFT_BRACE, event);
        break;
    default:
        kev_TODO();
    }
}

SF(minus) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level4(KEY_LEFT_BRACE, event);
        break;
    default:
        kev_TODO();
    }
}

SF(inverted_question_mark) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level3(KEY_H, event);
        break;
    default:
        kev_TODO();
    }
}

// Halbgeviertstrich
SF(ndash) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level2(KEY_COMMA, event);
        break;
    default:
        kev_TODO();
    }
}

SF(bullet) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level2(KEY_PERIOD, event);
        break;
    default:
        kev_TODO();
    }
}



// dead keys

SF(dead_grave) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_plain(KEY_EQUAL, event);
        break;
    default:
        kev_TODO();
    }
}

SF(dead_cedilla) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level2(KEY_EQUAL, event);
        break;
    default:
        kev_TODO();
    }
}

SF(dead_ring) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level3(KEY_EQUAL, event);
        break;
    default:
        kev_TODO();
    }
}

SF(dead_umlaut) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level4(KEY_EQUAL, event);
        break;
    default:
        kev_TODO();
    }
}

SF(dead_circumfex) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_plain(KEY_TILDE, event);
        break;
    default:
        kev_TODO();
    }
}

SF(dead_caron) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level2(KEY_TILDE, event);
        break;
    default:
        kev_TODO();
    }
}

SF(dead_dot) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level4(KEY_TILDE, event);
        break;
    default:
        kev_TODO();
    }
}

SF(dead_acute) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_plain(KEY_RIGHT_BRACE, event);
        break;
    default:
        kev_TODO();
    }
}

SF(dead_perispomene) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level2(KEY_RIGHT_BRACE, event);
        break;
    default:
        kev_TODO();
    }
}

SF(dead_bar) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level3(KEY_RIGHT_BRACE, event);
        break;
    default:
        kev_TODO();
    }
}

SF(dead_double_acute) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level4(KEY_RIGHT_BRACE, event);
        break;
    default:
        kev_TODO();
    }
}


// control and navigation keys

SF(page_up) {
    switch (targetlayout) {
    default:
        kev_allow_modifiers(KEY_PAGE_UP, event);
    }
}

SF(page_down) {
    switch (targetlayout) {
    default:
        kev_allow_modifiers(KEY_PAGE_DOWN, event);
    }
}

SF(backspace) {
    switch (targetlayout) {
    default:
        kev_allow_modifiers(KEY_BACKSPACE, event);
    }
}

SF(delete) {
    switch (targetlayout) {
    default:
        kev_allow_modifiers(KEY_DELETE, event);
    }
}

SF(up) {
    switch (targetlayout) {
    default:
        kev_allow_modifiers(KEY_UP, event);
    }
}

SF(down) {
    switch (targetlayout) {
    default:
        kev_allow_modifiers(KEY_DOWN, event);
    }
}

SF(left) {
    switch (targetlayout) {
    default:
        kev_allow_modifiers(KEY_LEFT, event);
    }
}

SF(right) {
    switch (targetlayout) {
    default:
        kev_allow_modifiers(KEY_RIGHT, event);
    }
}

SF(home) {
    switch (targetlayout) {
    default:
        kev_allow_modifiers(KEY_HOME, event);
    }
}

SF(end) {
    switch (targetlayout) {
    default:
        kev_allow_modifiers(KEY_END, event);
    }
}

SF(escape) {
    switch (targetlayout) {
    default:
        kev_allow_modifiers(KEY_ESC, event);
    }
}

SF(tab) {
    switch (targetlayout) {
    default:
        kev_allow_modifiers(KEY_TAB, event);
    }
}

SF(insert) {
    switch (targetlayout) {
    default:
        kev_allow_modifiers(KEY_INSERT, event);
    }
}

SF(return) {
    switch (targetlayout) {
    default:
        kev_allow_modifiers(KEY_ENTER, event);
    }
}

SF(enter) {
    switch (targetlayout) {
    default:
        kev_allow_modifiers(KEY_ENTER, event);
    }
}


// numpad

SF(numpad_1) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level4(KEY_M, event);
        break;
    default:
        kev_allow_modifiers(KEYPAD_1, event);
    }
}

SF(numpad_2) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level4(KEY_COMMA, event);
        break;
    default:
        kev_allow_modifiers(KEYPAD_2, event);
    }
}

SF(numpad_3) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level4(KEY_PERIOD, event);
        break;
    default:
        kev_allow_modifiers(KEYPAD_3, event);
    }
}

SF(numpad_4) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level4(KEY_J, event);
        break;
    default:
        kev_allow_modifiers(KEYPAD_4, event);
    }
}

SF(numpad_5) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level4(KEY_K, event);
        break;
    default:
        kev_allow_modifiers(KEYPAD_5, event);
    }
}

SF(numpad_6) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level4(KEY_L, event);
        break;
    default:
        kev_allow_modifiers(KEYPAD_6, event);
    }
}

SF(numpad_7) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level4(KEY_U, event);
        break;
    default:
        kev_allow_modifiers(KEYPAD_7, event);
    }
}

SF(numpad_8) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level4(KEY_I, event);
        break;
    default:
        kev_allow_modifiers(KEYPAD_8, event);
    }
}

SF(numpad_9) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level4(KEY_O, event);
        break;
    default:
        kev_allow_modifiers(KEYPAD_9, event);
    }
}

SF(numpad_0) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level4(KEY_SPACE, event);
        break;
    default:
        kev_allow_modifiers(KEYPAD_0, event);
    }
}

SF(numpad_divide) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level4(KEY_9, event);
        break;
    default:
        kev_allow_modifiers(KEYPAD_SLASH, event);
    }
}

SF(numpad_multiply) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level4(KEY_0, event);
        break;
    default:
        kev_allow_modifiers(KEYPAD_ASTERIX, event);
    }
}

SF(numpad_plus) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level4(KEY_P, event);
        break;
    default:
        kev_allow_modifiers(KEYPAD_PLUS, event);
    }
}

SF(numpad_minus) {
    switch (targetlayout) {
    case TGL_NEO:
        kev_level4(KEY_LEFT_BRACE, event);
        break;
    default:
        kev_allow_modifiers(KEYPAD_MINUS, event);
    }
}

// XXX also try with SDL_SCANCODE_DECIMALSEPARATOR
// XXX not 100% in accordance with http://wiki.neo-layout.org/browser/A-REFERENZ-A/neo20.txt?format=raw
SF(numpad_comma) {
    switch (targetlayout) {
    case TGL_NEO:
    case TGL_DE:
    case TGL_DE_NODEAD:
    case TGL_DE_APPLE:
        kev_allow_modifiers(KEYPAD_PERIOD, event);
        break;
    default:
        kev_plain(KEY_COMMA, event);
    }
}

// XXX also try with SDL_SCANCODE_DECIMALSEPARATOR
// XXX not 100% in accordance with http://wiki.neo-layout.org/browser/A-REFERENZ-A/neo20.txt?format=raw
SF(numpad_period) {
    switch (targetlayout) {
    case TGL_NEO:
    case TGL_DE:
    case TGL_DE_NODEAD:
    case TGL_DE_APPLE:
        kev_plain(KEY_PERIOD, event);
        break;
    default:
        kev_allow_modifiers(KEYPAD_PERIOD, event);
    }
}

// function keys

SF(F1) {
    switch (targetlayout) {
    default:
        kev_allow_modifiers(KEY_F1, event);
    }
}

SF(F2) {
    switch (targetlayout) {
    default:
        kev_allow_modifiers(KEY_F2, event);
    }
}

SF(F3) {
    switch (targetlayout) {
    default:
        kev_allow_modifiers(KEY_F3, event);
    }
}

SF(F4) {
    switch (targetlayout) {
    default:
        kev_allow_modifiers(KEY_F4, event);
    }
}

SF(F5) {
    switch (targetlayout) {
    default:
        kev_allow_modifiers(KEY_F5, event);
    }
}

SF(F6) {
    switch (targetlayout) {
    default:
        kev_allow_modifiers(KEY_F6, event);
    }
}

SF(F7) {
    switch (targetlayout) {
    default:
        kev_allow_modifiers(KEY_F7, event);
    }
}

SF(F8) {
    switch (targetlayout) {
    default:
        kev_allow_modifiers(KEY_F8, event);
    }
}

SF(F9) {
    switch (targetlayout) {
    default:
        kev_allow_modifiers(KEY_F9, event);
    }
}

SF(F10) {
    switch (targetlayout) {
    default:
        kev_allow_modifiers(KEY_F10, event);
    }
}

SF(F11) {
    switch (targetlayout) {
    default:
        kev_allow_modifiers(KEY_F11, event);
    }
}

SF(F12) {
    switch (targetlayout) {
    default:
        kev_allow_modifiers(KEY_F12, event);
    }
}


// more from function key row and similar

SF(printscreen) {
    kev_allow_modifiers(KEY_PRINTSCREEN, event);
}

SF(pause) {
    kev_allow_modifiers(KEY_PAUSE, event);
}

SF(app) {
    kev_allow_modifiers(KEY_APP, event);
}

// special keys

SF(redo) {
    kev_allow_modifiers(KEY_REDO, event);
}

SF(undo) {
    kev_allow_modifiers(KEY_UNDO, event);
}

SF(copy) {
    kev_allow_modifiers(KEY_COPY, event);
}

SF(paste) {
    kev_allow_modifiers(KEY_PASTE, event);
}

SF(cut) {
    kev_allow_modifiers(KEY_CUT, event);
}

SF(find) {
    kev_allow_modifiers(KEY_FIND, event);
}

SF(forward) {
// TODO: scancode values > 255 (see usb_keyboard.h:press_key)
    //kev_allow_modifiers(KEY_FORWARD, event);
    kev_TODO();
}

SF(back) {
// TODO: scancode values > 255 (see usb_keyboard.h:press_key)
    //kev_allow_modifiers(KEY_BACK, event);
    kev_TODO();
}

SF(sleep) {
// TODO: scancode values > 255 (see usb_keyboard.h:press_key)
  //kev_allow_modifiers(KEY_SLEEP, event);
    kev_TODO();
}

SF(mute) {
    kev_allow_modifiers(KEY_MUTE, event);
}

SF(volumeup) {
    kev_allow_modifiers(KEY_VOLUMEUP, event);
}

SF(volumedown) {
    kev_allow_modifiers(KEY_VOLUMEDOWN, event);
}

