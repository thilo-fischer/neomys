/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

#include "indication.h"
#include "debug.h"
#include "ucontroller.h"
#include "panel.h"
#include "adaptation.h"
#include "hostcommunication.h"

static void init();

dbg_define_msg(BUILDTIME, 0x01, "build %s, %s", sizeof(__DATE__), sizeof(__TIME__));

int main(void) {
  init();
  while (true) {
    ind_cycle();
    dbg_cycle();
    adp_await_next_cycle();
    pnl_sync_io_all();
    pnl_process_keystate_changes_all();
    hcm_progress_out_keyseq();
  };
  return 0;
}

static void init() {
  ind_init();
  ind_signal(IND_SIG_OKEY_INIT);
  dbg_init();
  uc_init();
  dbg_info(BUILDTIME, __DATE__, __TIME__);
  pnl_init_io_all();
}
