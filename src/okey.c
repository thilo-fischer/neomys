/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

#include "ucontroller.h"
#include "panel.h"
#include "adaptation.h"
#include "hostcommunication.h"

static void init();

int main(void) {
  init();
  while (true) {
    dbg_char('{');
    adp_await_next_cycle();
    dbg_msg("sync>");
    pnl_sync_io_all();
    dbg_msg("ksw>");
    pnl_process_keystate_changes_all();
    dbg_msg("kseq>");
    hcm_progress_out_keyseq();
    dbg_char('}');
  };
  return 0;
}

static void init() {
  uc_init();
  uc_signaling_led(true);
  dbg_msg(__TIME__);
  pnl_init_io_all();
  uc_signaling_led(false);
}
