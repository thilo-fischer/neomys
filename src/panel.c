/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/


#include "panel.h"


void pnl_init_io(panel_t *panel);
void pnl_sync_io(panel_t *panel);
void pnl_process_keystate_changes(panel_t *panel);


static inline uint8_t *pnl_get_single_ksw_state_buffer(uint8_t buffer_idx, panel_t *panel) {
  const uint8_t single_buffer_size = panel->height * bitcount_to_bytecount(panel->width);
  return panel->ksw_states + single_buffer_size * buffer_idx;
}

static inline uint8_t *pnl_get_current_ksw_state_buffer(panel_t *panel) {
  return pnl_get_single_ksw_state_buffer(panel->ksw_states_previous_first ? 1 : 0, panel);
}

static inline uint8_t *pnl_get_previous_ksw_state_buffer(panel_t *panel) {
  return pnl_get_single_ksw_state_buffer(panel->ksw_states_previous_first ? 0 : 1, panel);
}

static inline uint8_t *pnl_get_ksw_state_byte_address(uint8_t *buffer, uint8_t row, uint8_t col, const panel_t *panel) {
  const uint8_t byte_at_row   = col / 8;
  const uint8_t bytes_per_row = bitcount_to_bytecount(panel->width);
  return buffer + row * bytes_per_row + byte_at_row;
}

static inline bool pnl_get_ksw_state_from_buffer(uint8_t *buffer, uint8_t row, uint8_t col, const panel_t *panel) {
  const uint8_t bitpos       = col % 8;
  uint8_t *const byteaddress = pnl_get_ksw_state_byte_address(buffer, row, col, panel);
  return get_bit(byteaddress, bitpos);
}

static inline bool pnl_get_ksw_state_current(uint8_t row, uint8_t col, panel_t *panel) {
  return pnl_get_ksw_state_from_buffer(pnl_get_current_ksw_state_buffer(panel), row, col, panel);
}

static inline bool pnl_get_ksw_state_previous(uint8_t row, uint8_t col, panel_t *panel) {
  return pnl_get_ksw_state_from_buffer(pnl_get_previous_ksw_state_buffer(panel), row, col, panel);
}

static inline void pnl_set_ksw_state_in_buffer(uint8_t *buffer, uint8_t row, uint8_t col, const panel_t *panel, bool state) {
  const uint8_t bitpos       = col % 8;
  uint8_t *const byteaddress = pnl_get_ksw_state_byte_address(buffer, row, col, panel);
  set_bit(byteaddress, bitpos, state);
}

static inline void pnl_set_ksw_state_current(uint8_t row, uint8_t col, panel_t *panel, bool state) {
  pnl_set_ksw_state_from_buffer(pnl_get_current_ksw_state_buffer(panel), row, col, panel, state);
}


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

