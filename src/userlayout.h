/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

/**
 * @file
 *
 * Defines the symbols used to specify the key presses (or
 * sequences of key presses) to be sent to the host as reaction to the
 * key switch state changes on the okey keyboard hardware.
 *
 * Key presses on the okey keyboard can be translated to key presses
 * (or sequences of key presses) that will make the host the keyboard
 * is connected to (e.g. a PC) act as if it uses the user layout even
 * if it is configured for a different keyboard layout, e.g. use a
 * Dvorak layout on a PC configured for a US-international keyboard
 * layout or a Neo2 layout on a Mac configured for a Apple DE layout.
 *
 * The software running on the okey keyboard's master panel's
 * controller will take care of these translations, the host does not
 * need any special modifications or software.
 *
 * This file defines the symbols to be used to specify the necessary
 * translation routines in the approprialte userlayout_Foobar.c files.
 *
 * A user layout is a two-dimensional array of function pointers where
 * each key switch of the according panel corresponds to one array
 * element.  The functions pointed to implement the routines to achive
 * the desired effects of the according key press for various target
 * layouts. (The target layout is the layout that is configured at the
 * host the okey keyboard is connected to.)  Depending on the
 * currently set target layout, the function will enqueue an
 * appropriate sequence of key codes to be sent to the host that will
 * result in simulating a key press according to the configured user
 * layout.
 *
 * There are good reasons for using dedicated functions and a
 * two-dimensional array of function pointers instead of using data
 * structs to describe the key sequences to be generated upon okey
 * keyboard key presses with a specific user layout:
 *
 * 1) Using functions is much more flexible. Keys can be freely
 *    configured to do very special stuff, e.g. change the user or
 *    target layout or act as modifier key for an additional level.
 *
 * 2) Most micro processors are harvard architectures where the
 *    program code executed resides in ROM memory while the data
 *    operated on is in RAM. While ROM memory is typically much more
 *    than needed for okey keyboard code, RAM memory may get short if
 *    you put large data structures like key translation tables for
 *    several dozens of keys and a few user and target layouts in
 *    RAM. (First prototype software of the neomys keyboard did it
 *    this way and went out of RAM on the Teensy 2.0 controller.) One
 *    could put the translation tables in the ROM and access them from
 *    there with special (micro processor specific) instructions, but
 *    this requiires additional effort in both implementation and
 *    runtime performance. It's not that much of effort, and our
 *    software is far away from being performance critical on any
 *    common micro controller, so it is not a major disadvantage. But
 *    it is a disadvantage and another reason to prefer function
 *    pointers over data structures in the user layout arrays.
 * 
 * 3) Compiled functions just running the right routines will
 *    typically achive higher runtime performace than evaluating data
 *    structures to get a generic function to run the right
 *    routines. Compiled functions may also result in a smaller memory
 *    footprint of the compiled code because control flow branches
 *    relevant only for certain keys can be left away or can be
 *    optimized away by the compiler for all keys that don't need that
 *    branches, while when using a data structure for each key, this
 *    structure needs to provide elements for all special cases that
 *    one or the other key might need.
 */

#ifndef _USERLAYOUT_H_
#define _USERLAYOUT_H_

#include "adaption.h"

typedef enum targetlayout_t;

/// The function pointer type to be used in the user layout arrays.
/// 
/// @param[in, out] effective_levels An array of the levels that
/// currently apply to certain classes of keys. With respect to level
/// locking, certain keys shall behave differently than
/// others. E.g. letter keys shall respond to level-2-lock
/// (shift-level locked, like achived on normal keyboards with the
/// caps-lock key), number keys and punctuation character keys should
/// (normally) not. If a numlock behaviour shall be modeled by the
/// okey keyboard firmware, this could be achived through another
/// level with the level lock affecting only the keys from the
/// notepad. (Note that it is recommended to not model numlock
/// behaviour from the okey firmware, but use the numlock feature of
/// the OS of the host instead.) Thus, beyond the "main" level which
/// is the level achived when taking into account level locking, is
/// valid for most of the keys and should be the first array element,
/// there can be an arbitrary number of additional levels that apply
/// to keys which shall evaluate currently pressed level modifiers and
/// level lockings differently. The number of additional levels, thier
/// order and their meaning are specific to the okey adaptions. It is
/// usual and common convention to have one main level and a second
/// level that is achived when ignoring level-2-lock. Thus, specifiers
/// for these effective levels are defined in okey code. Specifiers
/// for additional effective levels shall be part of the adaption
/// specific code.<br>
/// The parameter is not const such that modifier keys
/// can change the set levels (if this is coordinated and consistent
/// with the other key functions).
///
/// @param[in] targetlayout the current target layout. Will normally not be evaluated by the key function itself but 
typedef void (*keyfunc_t)(level_t effective_levels[], targetlayout_t targetlayout, keystate_t event);

/// The type for user layouts.
typedef keyfunc_t userlayout_t[][];

typedef void (*symfunc_t)(targetlayout_t targetlayout, keystate_t event);

/// Macros to provide a domain specific language to describe user
/// layouts and translations to target layouts.
///@{

/// Function header for `key functions', i.e. functions referenced
/// directly from the layout that call the `symbol functions'
/// according to the currently active level modifiers.
#define KF(name) static void kf_##name(level_t effective_levels[], targetlayout_t targetlayout, keystate_t event)


#define LEVEL_SWITCH switch (level)
#define LEVEL_CASE(level, symbol) case LVL_##level: sf_##symbol(targetlayout, event); break;
#define LEVEL_DEFAULT(symbol) default: sf_##symbol(targetlayout, event); break;
#define LEVEL_ELSE default: /* TODO signal error state */; break;

/// Function header for `symbol functions', i.e. functions called from
/// the `key functions' depending on the currently active level
/// modifiers.
#define SF(name) static void sf_##name(targetlayout_t targetlayout, keystate_t event)


///@}

typedef enum {
    KT_DUMB,             ///< key does not have any effect, key is *really* dead
    KT_REGULAR,          ///< vanilla key
    KT_IGNORE_SHIFTLOCK, ///< key will not be affected by level2 lock (e.g. number keys, period, comma, deadkeys)
    KT_IGNORE_ALLLOCK,   ///< key will not be affected by any level lock (e.g. target layout switch key and any other keys to change settings of the neomys firmware)
    KT_IGNORE_LEVEL,     ///< ignore level modifiers at all (e.g. Ctrl, Alt, Gui)
    KT_LEVELMOD,         ///< key is a modifier key which affects the current level
} keytype_t;

typedef struct {
    keytype_t type;
    keyfunc_t kf[LEVEL_COUNT];
} keyrecord_t;


const keyrecord_t *get_keyrecord(uint8_t controller, uint8_t row, uint8_t col);

extern target_layout_t target_layout;

#endif // _USERLAYOUT_H_
