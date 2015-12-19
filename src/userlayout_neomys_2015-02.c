/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

/**
 * @file Defines the user layout symbols of the okey adaptation to
 * run on the 2nd version of 2015 of the neomys keyboard hardware.
 */

#include "userlayout_neomys_2015-02.h"


typedef enum {
    LVR_MAIN,  ///< regular level, applies to all letter keys
    LVR_IL2L,  ///< level reached when ignoring level-2-lock, applies to number and punctuation character keys
    LVR_IGNORE_ANY_LOCK,
    LVR_COUNT  ///< number of different effective levels
} level_variants_t;


level_t g_effective_levels[LVR_COUNT] = { LVL_DEFAULT, LVL_DEFAULT, LVL_DEFAULT };

#include "keyfunctions_common.c"
#include "keyfunctions_neomys_2015-02.c"

// definitions of user layouts

// Array elemets not given an initialization value will be initialzed
// to 0. Thus,
// my_userlayout[index_of_element_without_explicit_initialization_value]
// == NULL. (0 == NULL is guaranteed by the C standard.)

const userlayout_t ulo_neomys_left = {
    { kf_dead_circumfex, kf_1, kf_2, kf_3, kf_4, kf_5 },
    { kf_level4mod_left, kf_X, kf_V, kf_L, kf_C, kf_w },
    { kf_level3mod_left, kf_U, kf_I, kf_A, kf_E, kf_o },
    { kf_level2mod_left, kf_uuml, kf_ouml, kf_auml, kf_P, kf_z },
    { kf_ctrl_left, kf_gui_left, target_layout, kf_alt_left, kf_space_left, kf_enter },
 };
const userlayout_t ulo_neomys_right = {
    { kf_6, kf_7, kf_8, kf_9, kf_0, kf_dash_neo_lvl1, kf_dead_grave },
    { kf_K, kf_H, kf_G, kf_F, kf_Q, kf_eszett, kf_dead_acute },
    { kf_S, kf_N, kf_R, kf_T, kf_D, kf_Y, kf_level3mod_right },
    { kf_B, kf_M, kf_comma, kf_period, kf_J, kf_level2mod_right },
    { kf_space_right, kf_level4mod_right, kf_alt_right, kf_app, kf_gui_right, kf_ctrl_right, },
};

