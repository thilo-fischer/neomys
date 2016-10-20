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
/// @todo FIXME extract adaption unspecific (i.e. neomys-independent) generic parts of these helper functions and move to userlayout.h or userlayout_common.c
///@{
static inline void kf_generic_levelspecific(targetlayout_t targetlayout, keystate_t event, symfunc_t symfunc) {
    if (symfunc != NULL) {
        symfunc(targetlayout, event);
    } else {
        dbg_error(KF_ERR_SF_NULL, 0);
    }
}

#define MAX_ACTIVE_KEYS 8
keyfunc_t current_active_keys[MAX_ACTIVE_KEYS] = { NULL };

dbg_define_msg(KF_DBG_ACTIVATION, 0xC0,
               "kf:%s:%p",
               sizeof(char *),
               sizeof(keyfunc_t)
               );

void activate_key(keyfunc_t keyfunc) {
  dbg_debug(KF_DBG_ACTIVATION, "A", keyfunc);
  
  keyfunc(g_effective_levels, g_current_targetlayout, KS_PRESS);

  keyfunc_t *iter = current_active_keys;
  while (*iter != NULL && *iter != keyfunc && iter < current_active_keys + MAX_ACTIVE_KEYS) {
    ++iter;
  }
  if (iter == current_active_keys + MAX_ACTIVE_KEYS) {
    // TODO error message: too many keys pressed
    return;
  }
  *iter = keyfunc;
}

void deactivate_key(keyfunc_t keyfunc) {
  dbg_debug(KF_DBG_ACTIVATION, "D", keyfunc);
  
  keyfunc_t *iter = current_active_keys;
  while (*iter != keyfunc && iter < current_active_keys + MAX_ACTIVE_KEYS) {
    ++iter;
  }
  if (iter == current_active_keys + MAX_ACTIVE_KEYS) {
    // TODO error message
    return;
  }
  *iter = NULL;

  keyfunc(g_effective_levels, g_current_targetlayout, KS_RELEASE);
}

dbg_define_msg(KF_DBG_NOTIFY_ALL, 0xC6,
               "notif:%d",
               sizeof(keystate_t)
               );

void notify_all_active_keys(keystate_t keystate) {
  dbg_debug(KF_DBG_NOTIFY_ALL, keystate);
  for (keyfunc_t *iter = current_active_keys; iter < current_active_keys + MAX_ACTIVE_KEYS; ++iter) {
    if (*iter != NULL) {
      (*iter)(g_effective_levels, g_current_targetlayout, keystate);      
    }
  }
}


static inline void kf_generic_levelvarspecific(level_t level, targetlayout_t targetlayout, keystate_t event, symfunc_t sf1, symfunc_t sf2, symfunc_t sf3, symfunc_t sf4, symfunc_t sf4m, symfunc_t sf5, symfunc_t sf6) {
  // If LVL_4M is active, ignore any other levels.
  if (level & LVL_4M) {
    kf_generic_levelspecific(targetlayout, event, sf4m);
    return;
  }
  // If none of the previous levels was is active, and LVL_4 is active, ignore any other levels.
  if (level & LVL_4) {
    kf_generic_levelspecific(targetlayout, event, sf4);
    return;
  }
  // If none of the previous levels was is active, and LVL_3 is active, ignore any other levels.
  if (level & LVL_3) {
    kf_generic_levelspecific(targetlayout, event, sf3);
    return;
  }
  // If none of the previous levels was is active, and LVL_2 is active, ignore any other levels.
  if (level & LVL_SHIFT) {
    kf_generic_levelspecific(targetlayout, event, sf2);
    return;
  }
  // If none of the previous levels was is active, and LVL_5 is active, ignore any other levels.
  if (level & LVL_5) {
    kf_generic_levelspecific(targetlayout, event, sf5);
    return;
  }
  // If none of the previous levels was is active, and LVL_6 is active, ignore any other levels.
  if (level & LVL_6) {
    kf_generic_levelspecific(targetlayout, event, sf6);
    return;
  }
  //assert(level == 0);
  kf_generic_levelspecific(targetlayout, event, sf1);
}

static inline void kf_generic(level_variants_t level_variant, level_t effective_levels[], targetlayout_t targetlayout, keystate_t event, symfunc_t sf1, symfunc_t sf2, symfunc_t sf3, symfunc_t sf4, symfunc_t sf4m, symfunc_t sf5, symfunc_t sf6) {
  if (event == KS_MODCHANGE) {
    kf_generic_levelvarspecific(effective_levels[level_variant], targetlayout, KS_RELEASE, sf1, sf2, sf3, sf4, sf4m, sf5, sf6);
  } else {
    kf_generic_levelvarspecific(effective_levels[level_variant], targetlayout, event, sf1, sf2, sf3, sf4, sf4m, sf5, sf6);
  }
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
  if (event == KS_MODCHANGE) {
    return;
  }
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
    switch (event) {
    case KS_PRESS:
      // FIXME Quickfix to work around "key jamming" bug.
      //
      // Without this bugfix, a key release event of key whose symbol was
      // altered by a level modifier key would not be detected correctly if
      // the "modified" key and the modifier key get released in the wrong
      // order causing the key to "jam". (The same applies accordingly
      // to key presses.)
      //
      // Currently, a quick fix is implemented that releases all
      // modifier-sensitive keys whenever a modifier is being pressed or
      // released.
      //
      // A clean solution would release only those keys affected by the
      // level change from the modifier being pressed and trigger a delayed
      // activation of the symbol associated with the key in the new level
      // if the key is not being released within the delay.
      notify_all_active_keys(KS_MODCHANGE);
      // TODO_R introduce *one* method that propagates the level to *all* effective_level variants instead of setting the bit manually in each effective_level variant
      effective_levels[LVR_MAIN] |= affected_level;
      effective_levels[LVR_IL2L] |= affected_level;
      effective_levels[LVR_IGNORE_ANY_LOCK] |= affected_level;
      break;
    case KS_RELEASE:
      // FIXME Quickfix to work around "key jamming" bug. (see above)
      notify_all_active_keys(KS_MODCHANGE);
      // TODO_R introduce *one* method that propagates the level to *all* effective_level variants instead of setting the bit manually in each effective_level variant (see above)
      effective_levels[LVR_MAIN] &= ~affected_level;
      effective_levels[LVR_IL2L] &= ~affected_level;
      effective_levels[LVR_IGNORE_ANY_LOCK] &= ~affected_level;
      break;
    case KS_MODCHANGE:
      return; // ignore
    default:
      ; // XXX error message: programming error
    }
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

#define KF_ALL_LEVELS_SAME_NAME(name) KF_ALL_LEVELS(name, name)

#define KF_LEVEL_MODIFIER(name, lvl, id, sym) KF(name) { kf_level_modifier(effective_levels, LVL_##lvl, id, targetlayout, event, sf_##sym); }


// definitions of key functions

// number row left (0x00-0x07)
KF_IL2LOCK_1TO4(dead_circumfex, dead_circumfex, dead_caron, TODO, dead_dot)
KF_IL2LOCK_1TO4M(1, 1, degree, superscript1, TODO, F1)
KF_IL2LOCK_1TO4M(2, 2, sectionsign, superscript2, TODO, F2)
KF_IL2LOCK_1TO4M(3, 3, script_small_l, superscript3, numero_sign, F3)
KF_IL2LOCK_1TO4M(4, 4, guillemet_dbl_gt, guillemet_sgl_gt, nop, F4)
KF_IL2LOCK_1TO4M(5, 5, guillemet_dbl_lt, guillemet_sgl_lt, TODO, F5)

// number row right (0x08-0x0F)
KF_IL2LOCK_1TO4M(6, 6, dollar, cent_currency, pound_currency, F6)
KF_IL2LOCK_1TO4M(7, 7, euro_currency, yen_currency, currency_sign, F7)
KF_IL2LOCK_1TO4M(8, 8, low9quote_dbl, low9quote_sgl, tab, F8)
KF_IL2LOCK_1TO4M(9, 9, 6quote_dbl, 6quote_sgl, numpad_divide, F9)
KF_IL2LOCK_1TO4M(0, 0, 9quote_dbl, 9quote_sgl, numpad_multiply, F10)
KF_IL2LOCK_1TO4M(dash_neo_lvl1, dash_neo_lvl1, mdash, nop, numpad_minus, F11)
KF_IL2LOCK_1TO4M(dead_grave, dead_grave, dead_cedilla, dead_ring, dead_umlaut, F12)

// top row left (0x10-0x17)
KF_LEVEL_MODIFIER(level4mod_left, 4, 0, level4mod_left)
KF_REGULAR_1TO4(X, x, X, ellipsis, page_up)
KF_REGULAR_1TO4(V, v, V, underscore, backspace)
KF_REGULAR_1TO4(L, l, L, bracket_left, up)
KF_REGULAR_1TO4(C, c, C, bracket_right, delete)
KF_REGULAR_1TO4(W, w, W, caret, page_down)

// top row right (0x18-0x1F)
KF_REGULAR_1TO4M(K, k, K, exclamation_mark, inverted_exclamation_mark, back)
KF_REGULAR_1TO4M(H, h, H, chevron_left, numpad_7, TODO /*left dblclick*/)
KF_REGULAR_1TO4M(G, g, G, chevron_right, numpad_8, TODO /*mid dblclick*/)
KF_REGULAR_1TO4M(F, f, F, equals, numpad_9, TODO /*right dblclick*/)
KF_REGULAR_1TO4M(Q, q, Q, ampersand, numpad_plus, forward)
KF_REGULAR_1TO4M(eszett, eszett, ESZETT, long_s, minus, pause)
KF_IL2LOCK_1TO4M(dead_acute, dead_acute, dead_perispomene, dead_bar, dead_double_acute, printscreen)

// home row left (0x20-0x27)
KF_LEVEL_MODIFIER(level3mod_left, 3, 0, level3mod_left)
KF_REGULAR_1TO4(U, u, U, backslash, home)
KF_REGULAR_1TO4(I, i, I, slash, left)
KF_REGULAR_1TO4(A, a, A, brace_left, down)
KF_REGULAR_1TO4(E, e, E, brace_right, right)
KF_REGULAR_1TO4(O, o, O, asterisk, end)

// home row right (0x28-0x2F)
KF_REGULAR_1TO4M(S, s, S, question_mark, inverted_question_mark, TODO /*click 8*/)
KF_REGULAR_1TO4M(N, n, N, parentheses_left, numpad_4, TODO /*left click*/)
KF_REGULAR_1TO4M(R, r, R, parentheses_right, numpad_5, TODO /*mid click*/)
KF_REGULAR_1TO4M(T, t, T, dash_neo_lvl3, numpad_6, TODO /*right click*/)
KF_REGULAR_1TO4M(D, d, D, colon, numpad_comma, TODO /*click 9*/)
KF_REGULAR_1TO4M(Y, y, Y, at, numpad_period, find)
KF_LEVEL_MODIFIER(level3mod_right, 3, 1, level3mod_right)

// bottom row left (0x30-0x37)
KF_LEVEL_MODIFIER(level2mod_left, SHIFT, 0, shift_left)
KF_REGULAR_1TO4(uuml, uuml, UUML, hash, escape)
KF_REGULAR_1TO4(ouml, ouml, OUML, dollar, tab)
KF_REGULAR_1TO4(auml, auml, AUML, pipe, insert)
KF_REGULAR_1TO4(P, p, P, tilde, return)
KF_REGULAR_1TO4(Z, z, Z, backtick, undo)

// bottom row right (0x38-0x3F)
KF_REGULAR_1TO4M(B, b, B, plus, colon, undo)
KF_REGULAR_1TO4M(M, m, M, percent, numpad_1, copy)
KF_IL2LOCK_1TO4M(comma, comma, ndash, straight_dbl_quote, numpad_2, paste)
KF_IL2LOCK_1TO4M(period, period, bullet, apostrophe, numpad_3, cut)
KF_REGULAR_1TO4M(J, j, J, semicolon, semicolon, redo)
KF_LEVEL_MODIFIER(level2mod_right, SHIFT, 1, shift_right)

// space row left (0x40-0x47)
KF_ALL_LEVELS_SAME_NAME(ctrl_left)
KF_ALL_LEVELS_SAME_NAME(gui_left)
//KF_ALL_LEVELS(unused, nop)
KF_ALL_LEVELS_SAME_NAME(alt_left)
KF_ALL_LEVELS(space_left, space)
//KF_ALL_LEVELS(unused, nop)

// space row right (0x48-0x4F)
KF_REGULAR_1TO4(space_right, space, space, space, numpad_0)
KF_LEVEL_MODIFIER(level4mod_right, 4, 1, nop)
KF_ALL_LEVELS_SAME_NAME(alt_right)
KF_ALL_LEVELS_SAME_NAME(app)
KF_ALL_LEVELS_SAME_NAME(gui_right)
KF_ALL_LEVELS_SAME_NAME(ctrl_right)

// extra row 1 right (0x58-0x5F)
KF_ALL_LEVELS_SAME_NAME(sleep)
KF_ALL_LEVELS_SAME_NAME(copy)
KF_ALL_LEVELS_SAME_NAME(cut)
KF_ALL_LEVELS_SAME_NAME(paste)
KF_ALL_LEVELS_SAME_NAME(undo)
KF_ALL_LEVELS_SAME_NAME(redo)
KF_ALL_LEVELS_SAME_NAME(pause)
KF_ALL_LEVELS_SAME_NAME(printscreen)

// extra row 2 right (0x68-0x6F)
KF_ALL_LEVELS(target_layout_prev, prev_target_layout)
KF_ALL_LEVELS(target_layout_next, next_target_layout)
KF_ALL_LEVELS_SAME_NAME(numlock)
KF_ALL_LEVELS_SAME_NAME(capslock)
KF_ALL_LEVELS_SAME_NAME(scrolllock)
KF_ALL_LEVELS_SAME_NAME(mute)
KF_ALL_LEVELS_SAME_NAME(volumedown)
KF_ALL_LEVELS_SAME_NAME(volumeup)

