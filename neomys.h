/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

#ifndef _NEOMYS_H_
#define _NEOMYS_H_

#include <stdbool.h>
#include <stdint.h>

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

#define CTLR_MASTER 0
#define CTLR_SLAVE  1
#define CTLR_COUNT  2

#ifndef CONTROLLER
#  error CONTROLLER macro must be defined via compiler command line argument. Define as 0 to build software for master controller, as 1 to build for slave controllor. (-DCONTROLLER=0 or -DCONTROLLER=1 wit gcc.)
#endif

#endif // _NEOMYS_H_
