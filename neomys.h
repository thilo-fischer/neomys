/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

#ifndef _NEOMYS_H_
#define _NEOMYS_H_

#include <avr/io.h>
#include <stdbool.h>

enum row_e {
    ROW_NUM,
    ROW_TOP,
    ROW_HOME,
    ROW_BTM,
    ROW_SPACE,
    ROW_COUNT
};

#define COL_COUNT 8

enum neo_levels_e {
    LEVEL1,
    LEVEL2,
    LEVEL3,
    LEVEL4,
    LEVEL4_MOUSE,
    LEVEL5,
    LEVEL6,
    LEVEL_COUNT
};


#define SIDE_LEFT  0
#define SIDE_RIGHT 1

enum controller_e {
    CTLR_MASTER,
    CTLR_SLAVE
};

#define CTLR_COUNT 2

// shall be defined by compiler switch (-DSIDE=SIDE_xyz)
//#define SIDE SIDE_LEFT
//#define SIDE SIDE_RIGHT

#if (SIDE == SIDE_LEFT)
#  define CONTROLLER CTLR_MASTER
#else
#  define CONTROLLER CTLR_SLAVE
#endif

enum warnings_e {
    W_TOO_MANY_KEYS,
    W_COMMUNICATION_FAILURE,
    W_PROGRAMMING_ERROR,
};

#endif // _NEOMYS_H_
