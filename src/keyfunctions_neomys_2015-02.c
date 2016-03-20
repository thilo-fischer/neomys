/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

// FIXME rename file: different file extension to indicate it is included in another .c file

#include <stddef.h>

#include "userlayout_neomys_2015-02.h"

#include "debug.h"

dbg_define_msg(KF_ERR_SF_NULL, 0xD3,
               "KF.ERROR: symfunc is NULL");

/// helper functions to implement the common and ordinary key functions
/// @todo FIXME extract adaption unspecific generic parts of these helper functions and move to userlayout.h or userlayout_common.c
///@{
static inline void kf_generic_levelspecific(targetlayout_t targetlayout, keystate_t event, symfunc_t symfunc) {
    if (symfunc != NULL) {
        symfunc(targetlayout, event);
    } else {
        dbg_error(KF_ERR_SF_NULL, 0);
    }
}

static inline void kf_generic_levelvarspecific(level_t level, targetlayout_t targetlayout, keystate_t event, symfunc_t sf1, symfunc_t sf2, symfunc_t sf3, symfunc_t sf4, symfunc_t sf4m, symfunc_t sf5, symfunc_t sf6) {
    switch (level) {
    case LVL_DEFAULT:
        kf_generic_levelspecific(targetlayout, event, sf1);
        break;
    case LVL_SHIFT  :
        kf_generic_levelspecific(targetlayout, event, sf2);
        break;
    case LVL_3      :
        kf_generic_levelspecific(targetlayout, event, sf3);
        break;
    case LVL_4      :
        kf_generic_levelspecific(targetlayout, event, sf4);
        break;
    case LVL_4M     :
        kf_generic_levelspecific(targetlayout, event, sf4m);
        break;
    case LVL_5      :
        kf_generic_levelspecific(targetlayout, event, sf5);
        break;
    case LVL_6      :
        kf_generic_levelspecific(targetlayout, event, sf6);
        break;
    default:
        // TODO signal error state
        ;
    }   
}

static inline void kf_generic(level_variants_t level_variant, level_t effective_levels[], targetlayout_t targetlayout, keystate_t event, symfunc_t sf1, symfunc_t sf2, symfunc_t sf3, symfunc_t sf4, symfunc_t sf4m, symfunc_t sf5, symfunc_t sf6) {
    kf_generic_levelvarspecific(effective_levels[level_variant], targetlayout, event, sf1, sf2, sf3, sf4, sf4m, sf5, sf6);
}

///@}


/// implements the key function to be called for a regular key
/// where symbol functions shall be called for the first four levels
/// with the forth level identical for LVL_4 and LVL_4M
static inline void kf_1to4(level_variants_t level_variant, level_t effective_levels[], targetlayout_t targetlayout, keystate_t event, symfunc_t sf1, symfunc_t sf2, symfunc_t sf3, symfunc_t sf4) {
    kf_generic(level_variant, effective_levels, targetlayout, event, sf1, sf2, sf3, sf4, sf4, NULL, NULL);
}

/// implements the key function to be called for a regular key
/// where symbol functions shall be called for the first four levels
/// with the forth level being distinct for LVL_4 and LVL_4M
static inline void kf_1to4m(level_variants_t level_variant, level_t effective_levels[], targetlayout_t targetlayout, keystate_t event, symfunc_t sf1, symfunc_t sf2, symfunc_t sf3, symfunc_t sf4, symfunc_t sf4m) {
    kf_generic(level_variant, effective_levels, targetlayout, event, sf1, sf2, sf3, sf4, sf4m, NULL, NULL);
}


/// implements the key function to be called for a regular key
/// where symbol functions shall be called for the all six levels
/// with the forth level identical for LVL_4 and LVL_4M
static inline void kf_1to6(level_variants_t level_variant, level_t effective_levels[], targetlayout_t targetlayout, keystate_t event, symfunc_t sf1, symfunc_t sf2, symfunc_t sf3, symfunc_t sf4, symfunc_t sf5, symfunc_t sf6) {
    kf_generic(level_variant, effective_levels, targetlayout, event, sf1, sf2, sf3, sf4, sf4, sf5, sf6);
}

/// implements the key function to be called for a regular key
/// where symbol functions shall be called for the all six levels
/// with the forth level being distinct for LVL_4 and LVL_4M
static inline void kf_1to6_4m(level_variants_t level_variant, level_t effective_levels[], targetlayout_t targetlayout, keystate_t event, symfunc_t sf1, symfunc_t sf2, symfunc_t sf3, symfunc_t sf4, symfunc_t sf4m, symfunc_t sf5, symfunc_t sf6) {
    kf_generic(level_variant, effective_levels, targetlayout, event, sf1, sf2, sf3, sf4, sf4m, sf5, sf6);
}

/// implements the key function to be called for a key where the
/// associated symbol does not change depending on level
/// (e.g. modifier keys CTRL, ALT, GUI)
static inline void kf_all_levels(targetlayout_t targetlayout, keystate_t event, symfunc_t sf) {
    sf(targetlayout, event);
}

/// implements the key function to be called for a key that acts as a
/// level modifier
/// @param[in/out] effective_levels array of the currently active effective levels, may be altered by this function to effectuate the effect of the level modifier key event
/// @param[in] affected_level level the modifier is associated with
/// @param[in] modkey_id A keyboard usually has multiple keys for the same modifier (usually 2). The ID shall identify the specific modifier key being pressed, counting up starting at 0 from the leftmost key for this level's modifier to the rightmost key.
static inline void kf_level_modifier(level_t effective_levels[], level_t affected_level, uint8_t modkey_id, targetlayout_t targetlayout, keystate_t event, symfunc_t sf) {
#if 0 // TODO pressing two level modifiers at the same time shall lock the level
    if (effective_levels[LVR_MAIN] == affected_level) {
        if ()
    }
#endif
    effective_levels[LVR_MAIN] = affected_level;
    effective_levels[LVR_IL2L] = affected_level;
    effective_levels[LVR_IGNORE_ANY_LOCK] = affected_level;
    if (sf != NULL) {
        sf(targetlayout, event);
    }
}


// macros for domain specific language
#define KF_REGULAR_1TO4(name, sym1, sym2, sym3, sym4) KF(name) { kf_1to4(LVR_MAIN, effective_levels, targetlayout, event, sf_##sym1, sf_##sym2, sf_##sym3, sf_##sym4); }
#define KF_REGULAR_1TO4M(name, sym1, sym2, sym3, sym4, sym4m) KF(name) { kf_1to4m(LVR_MAIN, effective_levels, targetlayout, event, sf_##sym1, sf_##sym2, sf_##sym3, sf_##sym4, sf_##sym4m); }
#define KF_REGULAR_1TO6(name, sym1, sym2, sym3, sym4, sym5, sym6) KF(name) { kf_1to4(LVR_MAIN, effective_levels, targetlayout, event, sf_##sym1, sf_##sym2, sf_##sym3, sf_##sym4, sf_##sym5, sf_##sym6); }
#define KF_REGULAR_1TO6_4M(name, sym1, sym2, sym3, sym4, sym4m, sym5, sym6) KF(name) { kf_1to4m(LVR_MAIN, effective_levels, targetlayout, event, sf_##sym1, sf_##sym2, sf_##sym3, sf_##sym4, sf_##sym4m, sf_##sym5, sf_##sym6); }

#define KF_IL2LOCK_1TO4(name, sym1, sym2, sym3, sym4) KF(name) { kf_1to4(LVR_IL2L, effective_levels, targetlayout, event, sf_##sym1, sf_##sym2, sf_##sym3, sf_##sym4); }
#define KF_IL2LOCK_1TO4M(name, sym1, sym2, sym3, sym4, sym4m) KF(name) { kf_1to4m(LVR_IL2L, effective_levels, targetlayout, event, sf_##sym1, sf_##sym2, sf_##sym3, sf_##sym4, sf_##sym4m); }
#define KF_IL2LOCK_1TO6(name, sym1, sym2, sym3, sym4, sym5, sym6) KF(name) { kf_1to4(LVR_IL2L, effective_levels, targetlayout, event, sf_##sym1, sf_##sym2, sf_##sym3, sf_##sym4, sf_##sym5, sf_##sym6); }
#define KF_IL2LOCK_1TO6_4M(name, sym1, sym2, sym3, sym4, sym4m, sym5, sym6) KF(name) { kf_1to4m(LVR_IL2L, effective_levels, targetlayout, event, sf_##sym1, sf_##sym2, sf_##sym3, sf_##sym4, sf_##sym4m, sf_##sym5, sf_##sym6); }

#define KF_IGNORE_ANY_LOCK(name, sym1, sym2, sym3, sym4, sym4m, sym5, sym6) KF(name) { kf_generic(LVR_IGNORE_ANY_LOCK, effective_levels, targetlayout, event, sf_##sym1, sf_##sym2, sf_##sym3, sf_##sym4, sf_##sym4m, sf_##sym5, sf_##sym6); }

#define KF_ALL_LEVELS(name, sym) KF(name) { kf_all_levels(targetlayout, event, sf_##sym); }

#define KF_LEVEL_MODIFIER(name, lvl, id, sym) KF(name) { kf_level_modifier(effective_levels, LVL_##lvl, id, targetlayout, event, sf_##sym); }


// definitions of key functions

// ROW_NUM left (0x00-0x07)
KF_IL2LOCK_1TO4(dead_circumfex, dead_circumfex, dead_caron, TODO, dead_dot)
KF_IL2LOCK_1TO4M(1, 1, degree, superscript1, TODO, F1)
KF_IL2LOCK_1TO4M(2, 2, sectionsign, superscript2, TODO, F2)
KF_IL2LOCK_1TO4M(3, 3, script_small_l, superscript3, numero_sign, F3)
KF_IL2LOCK_1TO4M(4, 4, guillemet_dbl_gt, guillemet_sgl_gt, nop, F4)
KF_IL2LOCK_1TO4M(5, 5, guillemet_dbl_lt, guillemet_sgl_lt, TODO, F5)

// ROW_NUM right (0x08-0x0F)
KF_IL2LOCK_1TO4M(6, 6, dollar, cent_currency, pound_currency, F6)
KF_IL2LOCK_1TO4M(7, 7, euro_currency, yen_currency, currency_sign, F7)
KF_IL2LOCK_1TO4M(8, 8, low9quote_dbl, low9quote_sgl, tab, F8)
KF_IL2LOCK_1TO4M(9, 9, 6quote_dbl, 6quote_sgl, numpad_divide, F9)
KF_IL2LOCK_1TO4M(0, 0, 9quote_dbl, 9quote_sgl, numpad_multiply, F10)
KF_IL2LOCK_1TO4M(dash_neo_lvl1, dash_neo_lvl1, mdash, nop, numpad_minus, F11)
KF_IL2LOCK_1TO4M(dead_grave, dead_grave, dead_cedilla, dead_ring, dead_umlaut, F12)

// ROW_TOP left (0x10-0x17)
KF_LEVEL_MODIFIER(level4mod_left, 4, 0, level4mod_left)
KF_REGULAR_1TO4(X, x, X, ellipsis, page_up)
KF_REGULAR_1TO4(V, v, V, underscore, backspace)
KF_REGULAR_1TO4(L, l, L, bracket_left, up)
KF_REGULAR_1TO4(C, c, C, bracket_right, delete)
KF_REGULAR_1TO4(W, w, W, caret, page_down)

// ROW_TOP right (0x18-0x1F)
KF_REGULAR_1TO4M(K, k, K, exclamation_mark, inverted_exclamation_mark, back)
KF_REGULAR_1TO4M(H, h, H, chevron_left, numpad_7, TODO /*left dblclick*/)
KF_REGULAR_1TO4M(G, g, G, chevron_right, numpad_8, TODO /*mid dblclick*/)
KF_REGULAR_1TO4M(F, f, F, equals, numpad_9, TODO /*right dblclick*/)
KF_REGULAR_1TO4M(Q, q, Q, ampersand, numpad_plus, forward)
KF_REGULAR_1TO4M(eszett, eszett, ESZETT, long_s, minus, pause)
KF_IL2LOCK_1TO4M(dead_acute, dead_acute, dead_perispomene, dead_bar, dead_double_acute, printscreen)

// ROW_HOME left (0x20-0x27)
KF_LEVEL_MODIFIER(level3mod_left, 3, 0, level3mod_left)
KF_REGULAR_1TO4(U, u, U, backslash, home)
KF_REGULAR_1TO4(I, i, I, slash, left)
KF_REGULAR_1TO4(A, a, A, brace_left, down)
KF_REGULAR_1TO4(E, e, E, brace_right, right)
KF_REGULAR_1TO4(O, o, O, asterisk, end)

// ROW_HOME right (0x28-0x2F)
KF_REGULAR_1TO4M(S, s, S, question_mark, inverted_question_mark, TODO /*click 8*/)
KF_REGULAR_1TO4M(N, n, N, parentheses_left, numpad_4, TODO /*left click*/)
KF_REGULAR_1TO4M(R, r, R, parentheses_right, numpad_5, TODO /*mid click*/)
KF_REGULAR_1TO4M(T, t, T, dash_neo_lvl3, numpad_6, TODO /*right click*/)
KF_REGULAR_1TO4M(D, d, D, colon, numpad_comma, TODO /*click 9*/)
KF_REGULAR_1TO4M(Y, y, Y, at, numpad_period, find)
KF_LEVEL_MODIFIER(level3mod_right, 3, 1, level3mod_right)

// ROW_BTM left (0x30-0x37)
KF_LEVEL_MODIFIER(level2mod_left, SHIFT, 0, shift_left)
KF_REGULAR_1TO4(uuml, uuml, UUML, hash, escape)
KF_REGULAR_1TO4(ouml, ouml, OUML, dollar, tab)
KF_REGULAR_1TO4(auml, auml, AUML, pipe, insert)
KF_REGULAR_1TO4(P, p, P, tilde, return)
KF_REGULAR_1TO4(Z, z, Z, backtick, undo)

// ROW_BTM right (0x38-0x3F)
KF_REGULAR_1TO4M(B, b, B, plus, colon, undo)
KF_REGULAR_1TO4M(M, m, M, percent, numpad_1, copy)
KF_IL2LOCK_1TO4M(comma, comma, ndash, straight_dbl_quote, numpad_2, paste)
KF_IL2LOCK_1TO4M(period, period, bullet, apostrophe, numpad_3, cut)
KF_REGULAR_1TO4M(J, j, J, semicolon, semicolon, redo)
KF_LEVEL_MODIFIER(level2mod_right, SHIFT, 1, shift_right)

// ROW_SPACE left (0x40-0x47)
KF_ALL_LEVELS(ctrl_left, ctrl_left)
KF_ALL_LEVELS(gui_left, gui_left)
KF_IGNORE_ANY_LOCK(target_layout, next_target_layout, prev_target_layout, numlock, scrolllock, capslock, nop, nop)
KF_ALL_LEVELS(alt_left, alt_left)
KF_ALL_LEVELS(space_left, space)
KF_ALL_LEVELS(enter, enter)

// ROW_SPACE right (0x48-0x4F)
KF_REGULAR_1TO4(space_right, space, space, space, numpad_0)
KF_LEVEL_MODIFIER(level4mod_right, 4, 1, nop)
KF_ALL_LEVELS(alt_right, alt_right)
KF_ALL_LEVELS(app, app)
KF_ALL_LEVELS(gui_right, gui_right)
KF_ALL_LEVELS(ctrl_right, ctrl_right)

