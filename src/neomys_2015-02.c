

#include "panel.h"
#include "io_spi01.h"
#include "ucontroller_teensy-2.0.h"
#include "neomys_layout.h"


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
  .userlayout = neomys_layout_left,
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
  .userlayout = neomys_layout_right,
  .ksw_states = {{{ 0 }}},
  .ksw_states_previous_first = false,
  .numeric_id = 0,
  .out_data = { 0, 0 },
};

const panel_t panel_processing = { neomys_pnl_left, neomys_pnl_right };
