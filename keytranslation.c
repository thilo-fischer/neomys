/*
  Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
  Copyright (c) 2015 Thilo Fischer
  This program is licenced under GPLv3.
*/

#include "teensy_codelib/usb_keyboard/usb_keyboard.h"

#include "keytranslation.h"

#include "keyhandling.h"
#include "sendkeys.h"

// KEY FUNCTIONS

#define KF(name) static void kf_##name(target_layout_t tl, keystate_t event)

// special purpose

KF(nop) {}

KF(TODO) {
    // todo: log to uart, light up warning LED
}

// level modifiers

KF(kf_level4mod_left) {
}

// numbers

KF(1) {
    switch (tl) {
    default:
        kpress_plain(KEY_1);
    }
}

KF(2) {
    switch (tl) {
    default:
        kpress_plain(KEY_2);
    }
}

KF(3) {
    switch (tl) {
    default:
        kpress_plain(KEY_3);
    }
}

KF(4) {
    switch (tl) {
    default:
        kpress_plain(KEY_4);
    }
}

KF(5) {
    switch (tl) {
    default:
        kpress_plain(KEY_5);
    }
}

KF(6) {
    switch (tl) {
    default:
        kpress_plain(KEY_6);
    }
}

KF(7) {
    switch (tl) {
    default:
        kpress_plain(KEY_7);
    }
}

KF(8) {
    switch (tl) {
    default:
        kpress_plain(KEY_8);
    }
}

KF(9) {
    switch (tl) {
    default:
        kpress_plain(KEY_9);
    }
}

KF(0) {
    switch (tl) {
    default:
        kpress_plain(KEY_0);
    }
}

// letters
// upper case

KF(A) {
    switch (tl) {
    case TL_NEO:
        kpress_w_shift(KEY_D);
        break;
    default:
        kpress_w_shift(KEY_A);
    }
}

KF(B) {
    switch (tl) {
    case TL_NEO:
        kpress_w_shift(KEY_N);
        break;
    default:
        kpress_w_shift(KEY_B);
    }
}

KF(C) {
    switch (tl) {
    case TL_NEO:
        kpress_w_shift(KEY_R);
        break;
    default:
        kpress_w_shift(KEY_C);
    }
}

KF(D) {
    switch (tl) {
    case TL_NEO:
        kpress_w_shift(KEY_SEMICOLON);
        break;
    default:
        kpress_w_shift(KEY_D);
    }
}

KF(E) {
    switch (tl) {
    case TL_NEO:
        kpress_w_shift(KEY_F);
        break;
    default:
        kpress_w_shift(KEY_E);
    }
}

KF(F) {
    switch (tl) {
    case TL_NEO:
        kpress_w_shift(KEY_O);
        break;
    default:
        kpress_w_shift(KEY_F);
    }
}

KF(G) {
    switch (tl) {
    case TL_NEO:
        kpress_w_shift(KEY_I);
        break;
    default:
        kpress_w_shift(KEY_G);
    }
}

KF(H) {
    switch (tl) {
    case TL_NEO:
        kpress_w_shift(KEY_U);
        break;
    default:
        kpress_w_shift(KEY_H);
    }
}

KF(I) {
    switch (tl) {
    case TL_NEO:
        kpress_w_shift(KEY_S);
        break;
    default:
        kpress_w_shift(KEY_I);
    }
}

KF(J) {
    switch (tl) {
    case TL_NEO:
        kpress_w_shift(KEY_SLASH);
        break;
    default:
        kpress_w_shift(KEY_J);
    }
}

KF(K) {
    switch (tl) {
    case TL_NEO:
        kpress_w_shift(KEY_Y);
        break;
    default:
        kpress_w_shift(KEY_K);
    }
}

KF(L) {
    switch (tl) {
    case TL_NEO:
        kpress_w_shift(KEY_E);
        break;
    default:
        kpress_w_shift(KEY_L);
    }
}

KF(M) {
    switch (tl) {
    case TL_NEO:
        kpress_w_shift(KEY_M);
        break;
    default:
        kpress_w_shift(KEY_M);
    }
}

KF(N) {
    switch (tl) {
    case TL_NEO:
        kpress_w_shift(KEY_J);
        break;
    default:
        kpress_w_shift(KEY_N);
    }
}

KF(O) {
    switch (tl) {
    case TL_NEO:
        kpress_w_shift(KEY_G);
        break;
    default:
        kpress_w_shift(KEY_O);
    }
}

KF(P) {
    switch (tl) {
    case TL_NEO:
        kpress_w_shift(KEY_V);
        break;
    default:
        kpress_w_shift(KEY_P);
    }
}

KF(Q) {
    switch (tl) {
    case TL_NEO:
        kpress_w_shift(KEY_P);
        break;
    default:
        kpress_w_shift(KEY_Q);
    }
}

KF(R) {
    switch (tl) {
    case TL_NEO:
        kpress_w_shift(KEY_K);
        break;
    default:
        kpress_w_shift(KEY_R);
    }
}

KF(S) {
    switch (tl) {
    case TL_NEO:
        kpress_w_shift(KEY_H);
        break;
    default:
        kpress_w_shift(KEY_S);
    }
}

KF(T) {
    switch (tl) {
    case TL_NEO:
        kpress_w_shift(KEY_L);
        break;
    default:
        kpress_w_shift(KEY_T);
    }
}

KF(U) {
    switch (tl) {
    case TL_NEO:
        kpress_w_shift(KEY_A);
        break;
    default:
        kpress_w_shift(KEY_U);
    }
}

KF(V) {
    switch (tl) {
    case TL_NEO:
        kpress_w_shift(KEY_W);
        break;
    default:
        kpress_w_shift(KEY_V);
    }
}

KF(W) {
    switch (tl) {
    case TL_NEO:
        kpress_w_shift(KEY_T);
        break;
    default:
        kpress_w_shift(KEY_W);
    }
}

KF(X) {
    switch (tl) {
    case TL_NEO:
        kpress_w_shift(KEY_Q);
        break;
    default:
        kpress_w_shift(KEY_X);
    }
}

KF(Y) {
    switch (tl) {
    case TL_NEO:
        kpress_w_shift(KEY_QUOTE);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kpress_w_shift(KEY_Z);
        break;
    default:
        kpress_w_shift(KEY_Y);
    }
}

KF(Z) {
    switch (tl) {
    case TL_NEO:
        kpress_w_shift(KEY_B);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kpress_w_shift(KEY_Y);
        break;
    default:
        kpress_w_shift(KEY_Z);
    }
}

KF(AUML) {
    switch (tl) {
    case TL_NEO:
        kpress_w_shift(KEY_C);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kpress_w_shift(KEY_QUOTE);
        break;
    default:
        kpress_TODO();
    }
}

KF(OUML) {
    switch (tl) {
    case TL_NEO:
        kpress_w_shift(KEY_X);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kpress_w_shift(KEY_SEMICOLON);
        break;
    default:
        kpress_TODO();
    }
}

KF(UUML) {
    switch (tl) {
    case TL_NEO:
        kpress_w_shift(KEY_Z);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kpress_w_shift(KEY_LEFT_BRACE);
        break;
    default:
        kpress_TODO();
    }
}

KF(ESZETT) {
    switch (tl) {
    case TL_NEO:
        kpress_w_shift(KEY_LEFT_BRACE);
        break;
    default:
        kpress_TODO();
    }
}

// letters
// lower case

KF(a) {
    switch (tl) {
    case TL_NEO:
        kpress_plain(KEY_D);
        break;
    default:
        kpress_plain(KEY_A);
    }
}

KF(b) {
    switch (tl) {
    case TL_NEO:
        kpress_plain(KEY_N);
        break;
    default:
        kpress_plain(KEY_B);
    }
}

KF(c) {
    switch (tl) {
    case TL_NEO:
        kpress_plain(KEY_R);
        break;
    default:
        kpress_plain(KEY_C);
    }
}

KF(d) {
    switch (tl) {
    case TL_NEO:
        kpress_plain(KEY_SEMICOLON);
        break;
    default:
        kpress_plain(KEY_D);
    }
}

KF(e) {
    switch (tl) {
    case TL_NEO:
        kpress_plain(KEY_F);
        break;
    default:
        kpress_plain(KEY_E);
    }
}

KF(f) {
    switch (tl) {
    case TL_NEO:
        kpress_plain(KEY_O);
        break;
    default:
        kpress_plain(KEY_F);
    }
}

KF(g) {
    switch (tl) {
    case TL_NEO:
        kpress_plain(KEY_I);
        break;
    default:
        kpress_plain(KEY_G);
    }
}

KF(h) {
    switch (tl) {
    case TL_NEO:
        kpress_plain(KEY_U);
        break;
    default:
        kpress_plain(KEY_H);
    }
}

KF(i) {
    switch (tl) {
    case TL_NEO:
        kpress_plain(KEY_S);
        break;
    default:
        kpress_plain(KEY_I);
    }
}

KF(j) {
    switch (tl) {
    case TL_NEO:
        kpress_plain(KEY_SLASH);
        break;
    default:
        kpress_plain(KEY_J);
    }
}

KF(k) {
    switch (tl) {
    case TL_NEO:
        kpress_plain(KEY_Y);
        break;
    default:
        kpress_plain(KEY_K);
    }
}

KF(l) {
    switch (tl) {
    case TL_NEO:
        kpress_plain(KEY_E);
        break;
    default:
        kpress_plain(KEY_L);
    }
}

KF(m) {
    switch (tl) {
    case TL_NEO:
        kpress_plain(KEY_M);
        break;
    default:
        kpress_plain(KEY_M);
    }
}

KF(n) {
    switch (tl) {
    case TL_NEO:
        kpress_plain(KEY_J);
        break;
    default:
        kpress_plain(KEY_N);
    }
}

KF(o) {
    switch (tl) {
    case TL_NEO:
        kpress_plain(KEY_G);
        break;
    default:
        kpress_plain(KEY_O);
    }
}

KF(p) {
    switch (tl) {
    case TL_NEO:
        kpress_plain(KEY_V);
        break;
    default:
        kpress_plain(KEY_P);
    }
}

KF(q) {
    switch (tl) {
    case TL_NEO:
        kpress_plain(KEY_P);
        break;
    default:
        kpress_plain(KEY_Q);
    }
}

KF(r) {
    switch (tl) {
    case TL_NEO:
        kpress_plain(KEY_K);
        break;
    default:
        kpress_plain(KEY_R);
    }
}

KF(s) {
    switch (tl) {
    case TL_NEO:
        kpress_plain(KEY_H);
        break;
    default:
        kpress_plain(KEY_S);
    }
}

KF(t) {
    switch (tl) {
    case TL_NEO:
        kpress_plain(KEY_L);
        break;
    default:
        kpress_plain(KEY_T);
    }
}

KF(u) {
    switch (tl) {
    case TL_NEO:
        kpress_plain(KEY_A);
        break;
    default:
        kpress_plain(KEY_U);
    }
}

KF(v) {
    switch (tl) {
    case TL_NEO:
        kpress_plain(KEY_W);
        break;
    default:
        kpress_plain(KEY_V);
    }
}

KF(w) {
    switch (tl) {
    case TL_NEO:
        kpress_plain(KEY_T);
        break;
    default:
        kpress_plain(KEY_W);
    }
}

KF(x) {
    switch (tl) {
    case TL_NEO:
        kpress_plain(KEY_Q);
        break;
    default:
        kpress_plain(KEY_X);
    }
}

KF(y) {
    switch (tl) {
    case TL_NEO:
        kpress_plain(KEY_QUOTE);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kpress_plain(KEY_Z);
        break;
    default:
        kpress_plain(KEY_Y);
    }
}

KF(z) {
    switch (tl) {
    case TL_NEO:
        kpress_plain(KEY_B);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kpress_plain(KEY_Y);
        break;
    default:
        kpress_plain(KEY_Z);
    }
}

KF(auml) {
    switch (tl) {
    case TL_NEO:
        kpress_plain(KEY_C);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kpress_plain(KEY_QUOTE);
        break;
    default:
        kpress_TODO();
    }
}

KF(ouml) {
    switch (tl) {
    case TL_NEO:
        kpress_plain(KEY_X);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kpress_plain(KEY_SEMICOLON);
        break;
    default:
        kpress_TODO();
    }
}

KF(uuml) {
    switch (tl) {
    case TL_NEO:
        kpress_plain(KEY_Z);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kpress_plain(KEY_LEFT_BRACE);
        break;
    default:
        kpress_TODO();
    }
}

KF(eszett) {
    switch (tl) {
    case TL_NEO:
        kpress_plain(KEY_LEFT_BRACE);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kpress_plain(KEY_MINUS);
        break;
    default:
        kpress_TODO();
    }
}

// basic punctuation characters (in ASCII order)

KF(space) {
    kpress_allow_modifiers(KEY_SPACE);
}

KF(exclamation_mark) {
    switch (tl) {
    case TL_NEO:
        kpress_level3(KEY_H);
        break;
    default:
        kpress_w_shift(KEY_1);
    }
}

KF(straight_dbl_quote) {
    switch (tl) {
    case TL_NEO:
        kpress_level3(KEY_COMMA);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kpress_w_shift(KEY_2);
        break;
    default:
        kpress_w_shift(KEY_QUOTE);
    }
}

KF(hash) {
    switch (tl) {
    case TL_NEO:
        kpress_level3(KEY_Z);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kpress_plain(KEY_BACKSLASH);
        break;
    default:
        kpress_w_shift(KEY_3);
    }
}

KF(dollar) {
    switch (tl) {
    case TL_NEO:
        kpress_level3(KEY_X);
        break;
    default:
        kpress_w_shift(KEY_4);
    }
}

KF(percent) {
    switch (tl) {
    case TL_NEO:
        kpress_level3(KEY_M);
        break;
    default:
        kpress_w_shift(KEY_5);
    }
}

KF(ampersand) {
    switch (tl) {
    case TL_NEO:
        kpress_level3(KEY_P);
        break;
    default:
        kpress_w_shift(KEY_6);
    }
}

KF(apostrophe) {
    switch (tl) {
    case TL_NEO:
        kpress_level3(KEY_PERIOD);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kpress_w_shift(KEY_HASH);
        break;
    default:
        kpress_plain(KEY_QUOTE);
    }
}

KF(parentheses_left) {
    switch (tl) {
    case TL_NEO:
        kpress_level3(KEY_J);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kpress_w_shift(KEY_8);
        break;
    default:
        kpress_w_shift(KEY_9);
    }
}

KF(parentheses_right) {
    switch (tl) {
    case TL_NEO:
        kpress_level3(KEY_K);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kpress_w_shift(KEY_9);
        break;
    default:
        kpress_w_shift(KEY_0);
    }
}

KF(asterisk) {
    switch (tl) {
    case TL_NEO:
        kpress_level3(KEY_G);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kpress_w_shift(KEY_RIGHT_BRACE);
        break;
    default:
        kpress_w_shift(KEY_8);
    }
}

KF(plus) {
    switch (tl) {
    case TL_NEO:
        kpress_level3(KEY_N);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kpress_plain(KEY_RIGHT_BRACE);
        break;
    default:
        kpress_w_shift(KEY_EQUALS);
    }
}

KF(comma) {
    switch (tl) {
    default:
        kpress_plain(KEY_COMMA);
    }
}

KF(dash) {
    switch (tl) {
    case TL_NEO:
        kpress_level3(KEY_L);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kpress_plain(KEY_SLASH);
        break;
    default:
        kpress_plain(KEY_MINUS);
    }
}

KF(period) {
    switch (tl) {
    default:
        kpress_plain(KEY_PERIOD);
    }
}

KF(slash) {
    switch (tl) {
    case TL_NEO:
        kpress_level3(KEY_S);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kpress_w_shift(KEY_7);
        break;
    default:
        kpress_plain(KEY_SLASH);
    }
}


KF(colon) {
    switch (tl) {
    case TL_NEO:
        kpress_level3(KEY_SEMICOLON);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kpress_w_shift(KEY_PERIOD);
        break;
    default:
        kpress_w_shift(KEY_SEMICOLON);
    }
}

KF(semicolon) {
    switch (tl) {
    case TL_NEO:
        kpress_level3(KEY_SLASH);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kpress_w_shift(KEY_COMMA);
        break;
    default:
        kpress_plain(KEY_SEMICOLON);
    }
}

KF(chevron_left) {
    switch (tl) {
    case TL_NEO:
        kpress_level3(KEY_U);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kpress_TODO();
        break;
    default:
        kpress_w_shift(KEY_COMMA);
    }
}

KF(equals) {
    switch (tl) {
    case TL_NEO:
        kpress_level3(KEY_O);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kpress_w_shift(KEY_0);
        break;
    default:
        kpress_plain(KEY_EQUALS);
    }
}

KF(chevron_right) {
    switch (tl) {
    case TL_NEO:
        kpress_level3(KEY_I);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kpress_TODO();
        break;
    default:
        kpress_w_shift(KEY_PERIOD);
    }
}

KF(question_mark) {
    switch (tl) {
    case TL_NEO:
        kpress_level3(KEY_H);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kpress_w_shift(KEY_MINUS);
        break;
    default:
        kpress_w_shift(KEY_SLASH);
    }
}

KF(at) {
    switch (tl) {
    case TL_NEO:
        kpress_level3(KEY_QUOTE);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kpress_w_altgr(KEY_Q);
        break;
    default:
        kpress_w_shift(KEY_2);
    }
}


KF(bracket_left) {
    switch (tl) {
    case TL_NEO:
        kpress_level3(KEY_E);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kpress_w_altgr(KEY_8);
        break;
    default:
        kpress_plain(KEY_LEFT_BRACE);
    }
}

KF(backslash) {
    switch (tl) {
    case TL_NEO:
        kpress_level3(KEY_A);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kpress_w_altgr(KEY_MINUS);
        break;
    default:
        kpress_plain(KEY_BACKSLASH);
    }
}

KF(bracket_right) {
    switch (tl) {
    case TL_NEO:
        kpress_level3(KEY_R);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kpress_w_altgr(KEY_9);
        break;
    default:
        kpress_plain(KEY_RIGHT_BRACE);
    }
}

KF(caret) {
    switch (tl) {
    case TL_NEO:
        kpress_level3(KEY_T);
        break;
    case TL_DE:
        kpress_plain(KEY_GRAVE);
        kpress_plain(KEY_SPACE);
        break;
    case TL_DE_NODEAD:
        kpress_plain(KEY_GRAVE);
        break;
    default:
        kpress_w_shift(KEY_6);
    }
}

KF(underscore) {
    switch (tl) {
    case TL_NEO:
        kpress_level3(KEY_W);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kpress_w_shift(KEY_SLASH);
        break;
    default:
        kpress_w_shift(KEY_MINUS);
    }
}

KF(backtick) {
    switch (tl) {
    case TL_NEO:
        kpress_level3(KEY_B);
        break;
    case TL_DE:
        kpress_w_shift(KEY_EQUALS);
        kpress_plain  (KEY_SPACE);
        break;
    case TL_DE_NODEAD:
        kpress_w_shift(KEY_EQUALS);
        break;
    default:
        kpress_w_shift(KEY_GRAVE);
    }
}


KF(brace_left) {
    switch (tl) {
    case TL_NEO:
        kpress_level3(KEY_D);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kpress_w_altgr(KEY_7);
        break;
    default:
        kpress_w_shift(KEY_LEFT_BRACE);
    }
}

KF(pipe) {
    switch (tl) {
    case TL_NEO:
        kpress_level3(KEY_C);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kpress_TODO();
        break;
    default:
        kpress_w_shift(KEY_BACKSLASH);
    }
}

KF(brace_right) {
    switch (tl) {
    case TL_NEO:
        kpress_level3(KEY_F);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kpress_w_altgr(KEY_0);
        break;
    default:
        kpress_w_shift(KEY_RIGHT_BRACE);
    }
}

KF(tilde) {
    switch (tl) {
    case TL_NEO:
        kpress_level3(KEY_V);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kpress_w_altgr(KEY_RIGHT_BRACE);
        break;
    default:
        kpress_w_shift(KEY_GRAVE);
    }
}


// enhanced punctuation characters (in order of appearance on the Neo layout from left to right, from top to bottom)

KF(degree) {
    switch (tl) {
    case TL_NEO:
        kpress_level2(KEY_1);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kpress_w_shift(KEY_GRAVE);
        break;
    default:
        kpress_TODO();
    }
}

KF(sectionsign) {
    switch (tl) {
    case TL_NEO:
        kpress_level2(KEY_2);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kpress_w_shift(KEY_3);
        break;
    default:
        kpress_TODO();
    }
}

KF(euro_currency) {
    switch (tl) {
    case TL_NEO:
        kpress_level2(KEY_7);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kpress_w_altgr(KEY_E);
        break;
    default:
        kpress_TODO();
    }
}

// esoteric punctuation characters (in order of appearance on the Neo layout from left to right, from top to bottom)

KF(superscript_1) {
    switch (tl) {
    case TL_NEO:
        kpress_level3(KEY_1);
        break;
    default:
        kpress_TODO();
    }
}

KF(superscript_2) {
    switch (tl) {
    case TL_NEO:
        kpress_level3(KEY_2);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kpress_w_altgr(KEY_2);
        break;
    default:
        kpress_TODO();
    }
}

KF(superscript_3) {
    switch (tl) {
    case TL_NEO:
        kpress_level3(KEY_3);
        break;
    case TL_DE:
    case TL_DE_NODEAD:
        kpress_w_altgr(KEY_3);
        break;
    default:
        kpress_TODO();
    }
}



// control and navigation keys

KF(page_up) {
    switch (tl) {
    default:
        kpress_allow_modifiers(KEY_PAGE_UP);
    }
}

KF(page_down) {
    switch (tl) {
    default:
        kpress_allow_modifiers(KEY_PAGE_DOWN);
    }
}

KF(backspace) {
    switch (tl) {
    default:
        kpress_allow_modifiers(KEY_BACKSPACE);
    }
}

KF(delete) {
    switch (tl) {
    default:
        kpress_allow_modifiers(KEY_DELETE);
    }
}

KF(up) {
    switch (tl) {
    default:
        kpress_allow_modifiers(KEY_UP);
    }
}

KF(down) {
    switch (tl) {
    default:
        kpress_allow_modifiers(KEY_DOWN);
    }
}

KF(left) {
    switch (tl) {
    default:
        kpress_allow_modifiers(KEY_LEFT);
    }
}

KF(right) {
    switch (tl) {
    default:
        kpress_allow_modifiers(KEY_RIGHT);
    }
}

KF(home) {
    switch (tl) {
    default:
        kpress_allow_modifiers(KEY_HOME);
    }
}

KF(end) {
    switch (tl) {
    default:
        kpress_allow_modifiers(KEY_END);
    }
}

KF(escape) {
    switch (tl) {
    default:
        kpress_allow_modifiers(KEY_ESC);
    }
}

KF(tab) {
    switch (tl) {
    default:
        kpress_allow_modifiers(KEY_TAB);
    }
}

KF(insert) {
    switch (tl) {
    default:
        kpress_allow_modifiers(KEY_INSERT);
    }
}

KF(return) {
    switch (tl) {
    default:
        kpress_allow_modifiers(KEY_ENTER);
    }
}

KF(undo) {
    kpress_TODO();
}


// numpad

KF(numpad_1) {
    switch (tl) {
    default:
        kpress_allow_modifiers(KEYPAD_1);
    }
}

KF(numpad_2) {
    switch (tl) {
    default:
        kpress_allow_modifiers(KEYPAD_2);
    }
}

KF(numpad_3) {
    switch (tl) {
    default:
        kpress_allow_modifiers(KEYPAD_3);
    }
}

KF(numpad_4) {
    switch (tl) {
    default:
        kpress_allow_modifiers(KEYPAD_4);
    }
}

KF(numpad_5) {
    switch (tl) {
    default:
        kpress_allow_modifiers(KEYPAD_5);
    }
}

KF(numpad_6) {
    switch (tl) {
    default:
        kpress_allow_modifiers(KEYPAD_6);
    }
}

KF(numpad_7) {
    switch (tl) {
    default:
        kpress_allow_modifiers(KEYPAD_7);
    }
}

KF(numpad_8) {
    switch (tl) {
    default:
        kpress_allow_modifiers(KEYPAD_8);
    }
}

KF(numpad_9) {
    switch (tl) {
    default:
        kpress_allow_modifiers(KEYPAD_9);
    }
}

KF(numpad_0) {
    switch (tl) {
    default:
        kpress_allow_modifiers(KEYPAD_0);
    }
}

KF(numpad_slash) {
    switch (tl) {
    default:
        kpress_allow_modifiers(KEYPAD_SLASH);
    }
}

KF(numpad_asterisk) {
    switch (tl) {
    default:
        kpress_allow_modifiers(KEYPAD_ASTERIX);
    }
}

KF(numpad_plus) {
    switch (tl) {
    default:
        kpress_allow_modifiers(KEYPAD_PLUS);
    }
}

KF(numpad_minus) {
    switch (tl) {
    default:
        kpress_allow_modifiers(KEYPAD_MINUS);
    }
}

KF(numpad_period) {
    switch (tl) {
    default:
        kpress_allow_modifiers(KEYPAD_PERIOD);
    }
}

// special keys

KF(undo) {
    kpress_TODO();
}

KF(copy) {
    kpress_TODO();
}

KF(paste) {
    kpress_TODO();
}

KF(cut) {
    kpress_TODO();
}

KF(forward) {
    kpress_TODO();
}

KF(back) {
    kpress_TODO();
}


// KEY MAP


typedef enum {
    KT_PLAIN,
    KT_LEVELMOD,
    KT_IGNORE_SHIFTLOCK,
    KT_IGNORE_LEVEL,
    KT_DUMB, // rename: PHANTOM
} keytype_t;


typedef struct {
    keytype_t type;
    keyfunc_t kf[LEVEL_COUNT];
} keyrecord_t;


keyrecord_t keymap[ROW_COUNT][2][COL_COUNT] = {
    // ROW_NUM
    {
        //ROW_NUM left
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
                .kf = { kf_3, NULL, kf_superscript3, kf_numero_sign, kf_F3, },
            },
            // 4
            {
                .type = KT_IGNORE_SHIFTLOCK,
                .kf = { kf_4, kf_guillemet_dbl_gt, kf_guillemet_sgl_gt, NULL, kf_F4, },
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
        //ROW_NUM right
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
                .kf = { kf_dash, kf_mdash, NULL, kf_numpad_dash, kf_F11, },
            },
            // ò
            {
                .type = KT_IGNORE_SHIFTLOCK,
                .kf = { kf_dead_grave, kf_dead_cedilla, kf_dead_ring, kf_dead_umlaut, kf_F12, },
            },
            // ô
            {
                .type = KT_IGNORE_SHIFTLOCK,
                .kf = { kf_dead_circumfex, kf_dead_caron, NULL, kf_dead_dot, NULL, },
            },
        }, // controller (left/right side)
    }, // row

    
    // ROW_TOP
    {
        //ROW_TOP left
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
        //ROW_TOP right
        {
            // K
            {
                .type = KT_PLAIN,
                .kf = { kf_k, kf_K, kf_exclamation_mark, kf_inverted_exclamation_mark, kf_TODO, },
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
                .kf = { kf_q, kf_Q, kf_ampersand, kf_numpad_plus, kf_TODO, },
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
                .type = KT_PLAIN,
                .kf = { kf_comma, kf_ndash, kf_straight_dbl_quote, kf_numpad_2, kf_paste, },
            },
            // .
            {
                .type = KT_PLAIN,
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
            // unused
            {
                .type = KT_DUMB,
                .kf = { NULL },
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
            // left Alt
            {
                .type = KT_IGNORE_LEVEL,
                .kf = { kf_alt_left },
            },
            // level4 modifier
            {
                .type = KT_LEVELMOD,
                .kf = { kf_level4mod_right },
            },
            // space, numpad-zero
            {
                .type = KT_PLAIN,
                .kf = { kf_space, kf_space, kf_space, kf_numpad_zero, kf_nop, },
            },
            // unused
            {
                .type = KT_DUMB,
                .kf = { NULL },
            },
            // left GUI
            {
                .type = KT_IGNORE_LEVEL,
                .kf = { kf_gui_left },
            },
            // left Ctrl
            {
                .type = KT_IGNORE_LEVEL,
                .kf = { kf_ctrl_left },
            },
        }, // controller (left/right side)
    }, // row
};



keyfunc_t get_keyfunc(uint8_t controller, uint8_t row, uint8_t col, /*xxx>*/enum neo_levels_e locked_level,  enum neo_levels_e active_level/*<xxx*/) {
    keyrecord_t *record = keymap[row][controller][col];
    keyfunc_t result = NULL;
    switch (record->type) {
    case KT_PLAIN:
        // FIXME
        result = record->kf[level];
        break;
    case KT_LEVELMOD:
        // keyfunc of level mod should not be touched -> TODO: warning(programming error)
        break;
    case KT_IGNORE_SHIFTLOCK:
        // FIXME
        if (level_locked == LEVEL2) {
            result = record->kf[level];
        } else {
            result = record->kf[level];
        }
        break;
    case KT_IGNORE_LEVEL:
        return record->kf[0];
        break;
    case KT_DUMB:
        return kf_nop;
        break;
    default:
        // todo
    }

    // if NULL and LEVEL4_MOUSE, fallback to LEVEL4
    if (result = NULL && LEVEL4_MOUSE) {
        result = record->kf[LEVEL4];
    }
}
