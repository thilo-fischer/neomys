/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

/** @file
 * Implements the okey adaptation to run on the 2nd version of 2015 of the neomys keyboard hardware.
 */

#include "adaptation.h"

#include "io_spi01.h"
#include "ucontroller_teensy-2.0.h"
#include "ucontroller.h"

#include "userlayout_neomys.h"

const uint8_t MAX_SUPPORTED_PANELS = 4;


io_spi01_cfg_t neomys_io_cfg = {
  .rst_pin = { IOPORT_B, 0 },
  // TODO .baudrate = { ... }
};


panel_t neomys_pnl_left = {
  .width = 8,
  .height = 7,
  .gives_numeric_id = true,
  .out_size = 2,
  .io_spec = {
    .init_io = io_spi01_init,
    .sync_io = io_spi01_sync,
    .config_data = (void*) &neomys_io_cfg,
  },
  .userlayout = ulo_neomys_left,
  .ksw_states = {{{ 0 }}},
  .ksw_states_previous_first = false,
  .numeric_id = 0,
  .out_data = { 0, 0 },
};

panel_t neomys_pnl_right = {
  .width = 8,
  .height = 7,
  .gives_numeric_id = true,
  .out_size = 2,
  .io_spec = {
    .init_io = io_spi01_init,
    .sync_io = io_spi01_sync,
    .config_data = (void*) &neomys_io_cfg,
  },
  .userlayout = ulo_neomys_right,
  .ksw_states = {{{ 0 }}},
  .ksw_states_previous_first = false,
  .numeric_id = 0,
  .out_data = { 0, 0 },
};

const panel_t panel_processing[] = { neomys_pnl_left, neomys_pnl_right };

void adp_await_next_cycle() {
    uc_sleep(10);
}

