/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.

   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

#ifndef CTLRCOMM_H_
#define CTLRCOMM_H_

#include "neomys.h"

void tx_keystates();
int rx_keystates();

#endif /* CTLRCOMM_H_ */
