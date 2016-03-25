/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

/**
 * @file
 * neomys-specific indication implementation. 
 */

#include "adp_indication.h"

#include "adaptation.h"
#include "targetlayout.h"
#include "panel.h"


void adp_ind_init() {
}

void adp_ind_cycle() {
}

void adp_ind_signal(uint8_t signal) {
  panel_processing[0]->out_data[1] = signal;
}

void adp_ind_targetlayout() {
  switch (g_current_targetlayout) {
  case TGL_NEO:
    adp_ind_signal(ADP_IND_SIG_TGT_LO_NEO);
    break;
  case TGL_DE:
    adp_ind_signal(ADP_IND_SIG_TGT_LO_DE);
    break;
  case TGL_DE_NODEAD:
    adp_ind_signal(ADP_IND_SIG_TGT_LO_DE_ND);
    break;
  case TGL_DE_APPLE:
    adp_ind_signal(ADP_IND_SIG_TGT_LO_DE_APPLE);
    break;
  case TGL_US:
    adp_ind_signal(ADP_IND_SIG_TGT_LO_US);
    break;
  default:
    adp_ind_signal(ADP_IND_SIG_NONE);
  }
}
