/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

#include <avr/io.h>

#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>

#include "ucontroller.h"
#include "panel.h"
#include "adaptation.h"
#include "hostcommunication.h"

static void init();
//static inline void init_2();

#define init_2() dbg_msg("ii")


int main(void) {
  uc_init();
   uc_signaling_led(false);
   dbg_msg("i1");
   uc_signaling_led(true);
   uart_putchar("x");
    uart_putchar("x");
    uart_putchar("x");
  uc_signaling_led(false);
  init();
  init_2(); dbg_msg("I1");
    dbg_msg("i2");
  init();
  init_2(); dbg_msg("I2");
  int a = uc_sleep(5000);
    dbg_msg("i3");
    uart_putchar("x");
    uart_putchar("x");
    uart_putchar("x");
  init();
  init_2(); dbg_msg("I1");
    dbg_msg("i4");
  uc_signaling_led(true);
  while (true) {
    dbg_msg("mainloop>");
    //adp_await_next_cycle();
    _delay_ms(5000);
    dbg_msg("pnl_sync>");
    //pnl_sync_io_all();
    //pnl_process_keystate_changes_all();
    //hcm_progress_out_keyseq();
    dbg_msg("<mainloop");
  };
  return a;
}

static void init() {
  dbg_msg(__TIME__);
  //  pnl_init_io_all();
}

#if 0
static inline void init_2() {
  dbg_msg("ii");
  //  pnl_init_io_all();
}
#endif
