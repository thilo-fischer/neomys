/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

#include "ucontroller.h"
#include "panel.h"
#include "adaptation.h"
#include "hostcomm.h"

int main(void) {
  init();
  while (true) {
    adp_await_next_cycle();
    pnl_sync_io_all();
    pnl_process_keystate_changes();
    hcm_progress_out_keyseq();
  };
  return 0;
}

void init() {
  uc_init();
  pnl_init_io_all();
}
