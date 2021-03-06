/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

/** @file
 * API to be used to signal states and events to the okey keyboard user.
 * @todo FIXME rename uc_indication
 * @todo FIXME align/merge with adp_indication
 */

#ifndef _INDICATION_H_
#define _INDICATION_H_

#include <stdint.h>
#include <stdbool.h>

/**
 * To be called at firmware initialization. May be used to configure pins etc.
 */
void ind_init();

/**
 * To be called cyclically from the firmware's mainloop. May be used
 * to toggle signals off after certain timeout periods.p
 */
void ind_cycle();

/**
 * To be called from anywhere in the firmware code when a certain
 * state or event shall be signaled to the okey keyboard user.
 *
 * @param[in] signal An implementation specific value that specifies
 * what and how to signal to the okey keyboard user.
 */
void ind_signal(uint8_t signal);

enum ind_signals {
  IND_SIG_NONE,
  IND_SIG_OKEY_INIT,
  IND_SIG_DBG_MSG_BUF,
  IND_SIGS_COUNT
};

#endif // _INDICATION_H_
