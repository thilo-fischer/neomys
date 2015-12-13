/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/


#include "panel.h"


void pnl_init_io(panel_t *panel);
void pnl_sync_io(panel_t *panel);
void pnl_process_keystate_changes(panel_t *panel);


void pnl_init_io_all() {
  for (uint8_t i = 0; i < MAX_SUPPORTED_PANELS; ++i) {
    pnl_init_io(&panel_processing[i]);
  }
}


void pnl_init_io(panel_t *panel) {
  panel->io_spec.init_io(panel->io_spec.config);
}


void pnl_sync_io_all() {
  for (uint8_t i = 0; i < MAX_SUPPORTED_PANELS; ++i) {
    if (panel_processing[i].io_spec.before_sync != NULL) {
      panel_processing[i].io_spec.before_sync(&panel_processing[i]);
    }
  }
  for (uint8_t i = 0; i < MAX_SUPPORTED_PANELS; ++i) {
    pnl_sync_io(&panel_processing[i]);
  }
  for (uint8_t i = 0; i < MAX_SUPPORTED_PANELS; ++i) {
    if (panel_processing[i].io_spec.after_sync != NULL) {
      panel_processing[i].io_spec.after_sync(&panel_processing[i]);
    }
  }
}


void pnl_sync_io(panel_t *panel) {
  panel->ksw_states_previous_first ^= true;
  uint8_t ksw_state_buffer_current[][] = panel->ksw_states[panel->ksw_states_previous_first ? 1 : 0];
  panel->io_spec.sync_io(ksw_state_buffer_current, panel->width, panel->height, panel->numeric_id, panel->gives_numeric_id, panel->out_data, panel->out_size, panel->io_spec.config);
}

void pnl_process_keystate_changes_all() {
  for (uint8_t i = 0; i < MAX_SUPPORTED_PANELS; ++i) {
    pnl_process_keystate_changes(&panel_processing[i]);
  }
}

void pnl_process_keystate_changes(panel_t *panel) {
  if (memcmp(panel->ksw_states[0], panel->ksw_states[1], BYTES_PER_ROW(panel->width) * panel->height) != 0) {
    for (uint8_t row = 0; row < panel->height; ++row) {
      for (uint8_t byte = 0; byte < BYTES_PER_ROW(panel->width); ++byte) {
        uint8_t diff = panel->ksw_states[0][row][col] ^ panel->ksw_states[1][row][col];
        if (diff > 0) {
          for (uint8_t bit = 0; bit < 8; ++bit) {
            if (diff & (1<<bit)) {
              keystate_t keystate = (panel->ksw_states[0][row][col] & (1<<bit)) ^ panel->ksw_states_previous_first;
              panel->userlayout[row][bit + bytes*panel->width](g_effective_levels, g_targetlayout, keystate);
            }
          }
        }
      }
    }
  }
}

