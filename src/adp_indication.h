/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

/** @file
 * API to be used to signal states and events to the okey keyboard user.
 * @todo FIXME merge/align with (uc_)indication
 * @todo FIXME rework indication concept/design
 */

#ifndef _ADP_INDICATION_H_
#define _ADP_INDICATION_H_

#include <stdint.h>
#include <stdbool.h>

/**
 * To be called at firmware initialization. May be used to configure pins etc.
 */
void adp_ind_init();

/**
 * To be called cyclically from the firmware's mainloop. May be used
 * to toggle signals off after certain timeout periods.
 */
void adp_ind_cycle();

/**
 * To be called from anywhere in the firmware code when a certain
 * state or event shall be signaled to the okey keyboard user.
 *
 * @param[in] signal An implementation specific value that specifies
 * what and how to signal to the okey keyboard user.
 */
void adp_ind_signal(uint8_t signal);

void adp_ind_targetlayout();

enum ind_signals {
  ADP_IND_SIG_NONE = 0x00,
  ADP_IND_SIG_TGT_LO_NEO = 0x01,
  ADP_IND_SIG_TGT_LO_DE = 0x02,
  ADP_IND_SIG_TGT_LO_DE_ND = 0x04,
  ADP_IND_SIG_TGT_LO_DE_APPLE = 0x08,
  ADP_IND_SIG_TGT_LO_US = 0x10
};

#endif // _ADP_INDICATION_H_
