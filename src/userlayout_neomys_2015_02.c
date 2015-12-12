/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

/**
 * @file Defines the user layout symbols of the okey adaptation to
 * run on the 2nd version of 2015 of the neomys keyboard hardware.
 */

#include "userlayout_neomys_2015_02.h"


typedef enum {
    LVL_DEFAULT, ///< the default level active when no level modifiers are active
    LVL_SHIFT,   ///< the level associated with the shift modifier
    LVL_3,       ///< Neo2 level 3
    LVL_4,       ///< Neo2 level 4
    LVL_4M,      ///< neomys special mouse level derived from Neo2 level 4
    LVL_5,       ///< Neo2 level 5
    LVL_6,       ///< Neo2 level 6
    LVL_COUNT    ///< number of known levels
} level_t;


typedef enum {
    LVR_MAIN,  ///< regular level, applies to all letter keys
    LVR_IL2L,  ///< level reached when ignoring level-2-lock, applies to number and punctuation character keys
    LVR_COUNT  ///< number of different effective levels
} level_variants_t;


level_t current_levels[LVR_COUNT] = { LVL_DEFAULT, LVL_DEFAULT };

/// helper functions to implement the common and ordinary key functions
///@{
static inline void kf_generic_levelspecific(targetlayout_t targetlayout, keystate_t event, symfunc_t symfunc) {
    if (symfunc != NULL) {
        symfunc(targetlayout, event);
    } else {
        // TODO signal error state
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


// macros for domain specific language
#define KF_REGULAR_1TO4(key, sym1, sym2, sym3, sym4) KF(name) { kf_1to4(LVR_MAIN, effective_levels, targetlayout, event, sf_##sym1, sf_##sym2, sf_##sym3, sf_##sym4); }
#define KF_REGULAR_1TO4M(key, sym1, sym2, sym3, sym4, sym4m) KF(name) { kf_1to4m(LVR_MAIN, effective_levels, targetlayout, event, sf_##sym1, sf_##sym2, sf_##sym3, sf_##sym4, sf_##sym4m); }
#define KF_REGULAR_1TO6(key, sym1, sym2, sym3, sym4) KF(name) { kf_1to4(LVR_MAIN, effective_levels, targetlayout, event, sf_##sym1, sf_##sym2, sf_##sym3, sf_##sym4, sf_##sym5, sf_##sym6); }
#define KF_REGULAR_1TO6_4M(key, sym1, sym2, sym3, sym4, sym4m) KF(name) { kf_1to4m(LVR_MAIN, effective_levels, targetlayout, event, sf_##sym1, sf_##sym2, sf_##sym3, sf_##sym4, sf_##sym4m, sf_##sym5, sf_##sym6); }

#define KF_IL2LOCK_1TO4(key, sym1, sym2, sym3, sym4) KF(name) { kf_1to4(LVR_IL2L, effective_levels, targetlayout, event, sf_##sym1, sf_##sym2, sf_##sym3, sf_##sym4); }
#define KF_IL2LOCK_1TO4M(key, sym1, sym2, sym3, sym4, sym4m) KF(name) { kf_1to4m(LVR_IL2L, effective_levels, targetlayout, event, sf_##sym1, sf_##sym2, sf_##sym3, sf_##sym4, sf_##sym4m); }
#define KF_IL2LOCK_1TO6(key, sym1, sym2, sym3, sym4) KF(name) { kf_1to4(LVR_IL2L, effective_levels, targetlayout, event, sf_##sym1, sf_##sym2, sf_##sym3, sf_##sym4, sf_##sym5, sf_##sym6); }
#define KF_IL2LOCK_1TO6_4M(key, sym1, sym2, sym3, sym4, sym4m) KF(name) { kf_1to4m(LVR_IL2L, effective_levels, targetlayout, event, sf_##sym1, sf_##sym2, sf_##sym3, sf_##sym4, sf_##sym4m, sf_##sym5, sf_##sym6); }


KF_IL2LOCK_1TO4M(1, 1, degree, superscript1, TODO, F1);

KF_REGULAR_1TO4(X, x, X, ellipsis, page_up);


const userlayout_t ulo_neomys_left = {
    { kf_1 , },
    { kf_X , },
};
const userlayout_t ulo_neomys_right = {};

