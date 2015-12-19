/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

#include <string.h>

#include "panel.h"

#include "adaptation.h"

//#include "userlayout_neomys_2015-02.h" // FIXME for level_t


void pnl_init_io(panel_t *panel);
void pnl_sync_io(panel_t *panel);
void pnl_process_keystate_changes(panel_t *panel);


static inline void pnl_swap_ksw_state_buffers(panel_t *panel) {
  panel->ksw_states_previous_first = !panel->ksw_states_previous_first;
}


void pnl_init_io_all() {
  for (uint8_t i = 0; i < MAX_SUPPORTED_PANELS; ++i) {
    pnl_init_io(panel_processing[i]);
  }
}


void pnl_init_io(panel_t *panel) {
  panel->io_spec.init_io(panel->io_spec.config_data);
}


void pnl_sync_io_all() {
  for (uint8_t i = 0; i < MAX_SUPPORTED_PANELS; ++i) {
    if (panel_processing[i]->io_spec.before_sync != NULL) {
      panel_processing[i]->io_spec.before_sync(&panel_processing[i]);
    }
  }
  for (uint8_t i = 0; i < MAX_SUPPORTED_PANELS; ++i) {
    pnl_sync_io(panel_processing[i]);
  }
  for (uint8_t i = 0; i < MAX_SUPPORTED_PANELS; ++i) {
    if (panel_processing[i]->io_spec.after_sync != NULL) {
      panel_processing[i]->io_spec.after_sync(&panel_processing[i]);
    }
  }
}


void pnl_sync_io(panel_t *panel) {
  pnl_swap_ksw_state_buffers(panel);
  panel->io_spec.sync_io(panel);
}

void pnl_process_keystate_changes_all() {
  for (uint8_t i = 0; i < MAX_SUPPORTED_PANELS; ++i) {
    pnl_process_keystate_changes(panel_processing[i]);
  }
}

void pnl_process_keystate_changes(panel_t *panel) {
  const uint8_t *const current_ksw_state_buffer  = pnl_get_current_ksw_state_buffer (panel);
  const uint8_t *const previous_ksw_state_buffer = pnl_get_previous_ksw_state_buffer(panel);
  if (memcmp(current_ksw_state_buffer, previous_ksw_state_buffer, pnl_get_single_buffer_size(panel)) != 0) {
    for (uint8_t row = 0; row < panel->height; ++row) {
      for (uint8_t byte = 0; byte < pnl_get_bytes_per_row(panel); ++byte) {
        const uint8_t *current  = pnl_get_byte_from_row_const(current_ksw_state_buffer , row, byte, panel);
        const uint8_t *previous = pnl_get_byte_from_row_const(previous_ksw_state_buffer, row, byte, panel);
        uint8_t diff = *current ^ *previous;
        if (diff > 0) {
          for (uint8_t bit = 0; bit < 8; ++bit) {
            if (diff & (1<<bit)) {
              keystate_t keystate = *current & (1<<bit) ? KS_RELEASE : KS_PRESS;
              keyfunc_t keyfunc = pnl_get_keyfunc(row, 8 * byte + bit, panel);
              keyfunc(g_effective_levels, g_current_targetlayout, keystate);
            }
          }
        }
      }
    }
  }
}
