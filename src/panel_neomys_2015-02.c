/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

/**
 * @file Implements the panel configuration of the okey adaptation to
 * run on the 2nd version of 2015 of the neomys keyboard hardware.
 */

#include "panel.h"
#include "userlayout_neomys.h"

const uint8_t MAX_SUPPORTED_PANELS = 4;


extern io_spi01_cfg_t neomys_io_cfg;

uint8_t neomys_pnl_height = 7;
uint8_t neomys_pnl_width  = 8;
uint8_t neomys_pnl_out_size = 2;


uint8_t neomys_pnl_left_ksw_states_buffer [2][neomys_pnl_height][BYTES_PER_ROW(neomys_pnl_width)] = {{{0}}};
uint8_t neomys_pnl_left_out_buffer [neomys_pnl_out_size] = {0};
uint8_t neomys_pnl_right_ksw_states_buffer[2][neomys_pnl_height][BYTES_PER_ROW(neomys_pnl_width)] = {{{0}}};
uint8_t neomys_pnl_right_out_buffer[neomys_pnl_out_size] = {0};


panel_t neomys_pnl_left = {
  .width  = neomys_pnl_width,
  .height = neomys_pnl_height,
  .gives_numeric_id = true,
  .out_size = neomys_pnl_out_size,
  .io_spec = {
    .init_io = io_spi01_init,
    .sync_io = io_spi01_sync,
    .config_data = (void*) &neomys_io_cfg,
  },
  .userlayout = ulo_neomys_left,
  .ksw_states = neomys_pnl_left_ksw_states_buffer,
  .ksw_states_previous_first = false,
  .numeric_id = 0,
  .out_data = neomys_pnl_left_out_buffer,
};

panel_t neomys_pnl_right = {
  .width  = neomys_pnl_width,
  .height = neomys_pnl_height,
  .gives_numeric_id = true,
  .out_size = neomys_pnl_out_size,
  .io_spec = {
    .init_io = io_spi01_init,
    .sync_io = io_spi01_sync,
    .config_data = (void*) &neomys_io_cfg,
  },
  .userlayout = ulo_neomys_right,
  .ksw_states = neomys_pnl_right_ksw_states_buffer,
  .ksw_states_previous_first = false,
  .numeric_id = 0,
  .out_data = neomys_pnl_right_out_buffer,
};

panel_t * const panel_processing[] = { &neomys_pnl_left, &neomys_pnl_right };

