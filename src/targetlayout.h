/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

#ifndef _TARGET_LAYOUT_H_
#define _TARGET_LAYOUT_H_

enum targetlayout_enum {
   TGL_NEO       = 0x00,  ///< Neo2 (http://www.neo-layout.org/)
   TGL_DE        = 0x01,  ///< DIN 2137:2012-06 T1 (with dead keys)
   TGL_DE_NODEAD = 0x02,
   TGL_DE_APPLE  = 0x03,
   TGL_US        = 0x04,  ///< ANSI-INCITS 154-1988
   //TGL_US_APPLE,
   TGL_COUNT
};

typedef enum targetlayout_enum targetlayout_t;

extern targetlayout_t g_current_targetlayout;

#endif // _TARGET_LAYOUT_H_
