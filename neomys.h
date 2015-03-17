/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

/**
  Central TODO list. Other TODO issues can be found scattered over the source code marked with "FIXME" for important issues, "TODO" for normal issues, "XXX" for minor issiues. (eclipse IDE TODO comment style.)

  @TODO TODO add hardware switches to change target layout
  @TODO XXX provide a way to send numlock/capslock/scrolllock key events (e.g. higher level of other extra hardware switches)
  @TODO XXX provide a way to send numpad_enter key event (e.g. return on LEVEL4_MOUSE+V, numpad_enter on LEVEL4+V)
  @TODO FIXME provide LED to indicate current level
  @TODO TODO display current target layout selection (extra hardware ?)


 */

#ifndef _NEOMYS_H_
#define _NEOMYS_H_

#ifndef CONTROLLER
#  error CONTROLLER macro must be defined via compiler command line argument. Define as 0 to build software for master controller, as 1 to build for slave controllor. (-DCONTROLLER=0 or -DCONTROLLER=1 wit gcc.)
#endif

#include <stdbool.h>
#include <stdint.h>

#define CTLR_MASTER 0
#define CTLR_SLAVE  1
#define CTLR_COUNT  2

#include "inform.h"

enum row_e {
    ROW_NUM,
    ROW_TOP,
    ROW_HOME,
    ROW_BTM,
    ROW_SPACE,
    ROW_COUNT
};

#define COL_COUNT 8

#endif // _NEOMYS_H_
