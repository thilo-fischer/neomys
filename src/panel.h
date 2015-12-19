/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.

   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

/*
  An okey keyboard consists of several (usually two or three for a regular keyboard) panels. The default panel may contain up to 56 (7*8) key switches.

  One of the keyboard's panels contains the micro controller to connect the keyboard to the host via USB, to collect the state information of the key switches from all panel, process those states, translate them to key codes and transmit the key codes to the host and to drive indicators (LEDs and such) for modes and states. This panel is called the master panel, all other panels are called slave panels.

  In the default setup, all panels are connected in a line with a cable with 6 wires with the master panel on the starting point of the line. All slave panels may contain a micro controller, but the required logic can also be implemented with just a few digital integrated circuits not requiring any processor or software on the slave panels.

  The okey hard- and software is designed to be very flexible. Panels with different sizes than the default size and other approaches to connect the slave panels to the master panel are supported as well.

  Most of this software is intended to run on the controller of the host panel, but if a slave panel has a separate micro controller onboard, parts of this software can be used as well to run on the slave panel's controller.
*/

#ifndef _PANEL_H_
#define _PANEL_H_

#include "util.h"
// FIXME #include "userlayout.h"
#include "userlayout_neomys_2015-02.h"

// forward declarations
struct panel_struct;
typedef struct panel_struct panel_t;


/// Initialize the io devices according to cfg.
typedef void (*panel_init_io_func_t)(const void *cfg);
/// Read key switch states of height rows of keys with width keys per row from the hardware into the current ksw_states array,
/// read the numeric ID value from the hardware into numeric_id
/// and write out_size bytes of data contained in out_data to the hardware
/// using the io configuration as given by io_spec.config_data.
typedef void (*panel_sync_io_func_t)(panel_t *panel);
/// Run before syncing all panels.
typedef void (*panel_before_sync_io_func_t)(const void *cfg);
/// Run after syncing all panels.
typedef void (*panel_after_sync_io_func_t)(const void *cfg);



typedef struct {

  /// This function must implement all measures necessary to initialize the io devices to communicate to the panel.
  panel_init_io_func_t init_io;
  /// This function must implement the measures necessary to read out the key switch states and possibly ID from and to write the output data to the panel's hardware.
  panel_sync_io_func_t sync_io;

  panel_before_sync_io_func_t before_sync;
  panel_after_sync_io_func_t after_sync;
  
  /// io implementation specific configuration data specifying configurable details of the io mechanisms.
  void *config_data;
  
} panel_io_spec_t;



struct panel_struct {
  /// @name Configuration values
  ///@{
  
  /// The number of (logical) key switch rows of the panel. Default: 7
  const uint8_t height;
  /// The number of (logical) key switch columns of the
  /// panel. Default: 8
  const uint8_t width;
  /// Whether a numeric ID of the panel will be provided after the
  /// last row. Default: true
  const bool gives_numeric_id;

  /// The number of bytes to send to the panel (to drive indicators of
  /// the panel's hardware). Default: 2
  const uint8_t out_size;
  
  /// specifies the mechanisms to use to read out the key switch
  /// states from the hardware and to drive indicators (LEDs and such)
  /// of the panel's hardware
  const panel_io_spec_t io_spec;

  ///@}

  /// @name Settings
  ///@{

  /// User layout
  const userlayout_t *userlayout;
  
  ///@}

  
  /// @name Data buffers
  ///@{

  /// Buffers all *k*ey *sw*itch states of the panel for the previous and the current cycle.
  uint8_t *ksw_states;
  /// If true, find the *k*ey *sw*itch states of the previous cycle at ksw_states[0] and
  /// those of the current cycle at ksw_states[1]; if false, it's the other way around.
  /// By toggling this value each cycle, copying form current to previous buffer is not
  /// necessary.
  bool ksw_states_previous_first;

  uint8_t numeric_id;

  uint8_t *out_data;
  
  ///@}


};



void pnl_init_io_all();

void pnl_sync_io_all();

void pnl_process_keystate_changes_all();


static inline const uint8_t pnl_get_bytes_per_row(const panel_t *panel) {
  return bitcount_to_bytecount(panel->width);
}

static inline const uint16_t pnl_get_single_buffer_size(const panel_t *panel) {
  return ((uint16_t) panel->height) * pnl_get_bytes_per_row(panel);
}

static inline uint8_t *pnl_get_single_ksw_state_buffer(uint8_t buffer_idx, panel_t *panel) {
  return panel->ksw_states + pnl_get_single_buffer_size(panel) * buffer_idx;
}

static inline uint8_t *pnl_get_current_ksw_state_buffer(panel_t *panel) {
  return pnl_get_single_ksw_state_buffer(panel->ksw_states_previous_first ? 1 : 0, panel);
}

static inline uint8_t *pnl_get_previous_ksw_state_buffer(panel_t *panel) {
  return pnl_get_single_ksw_state_buffer(panel->ksw_states_previous_first ? 0 : 1, panel);
}

static inline uint8_t *pnl_get_byte_from_row(uint8_t *buffer, uint8_t row, uint8_t byte, const panel_t *panel) {
  return buffer + row * pnl_get_bytes_per_row(panel) + byte;
}

static inline const uint8_t *pnl_get_byte_from_row_const(const uint8_t *buffer, uint8_t row, uint8_t byte, const panel_t *panel) {
  return buffer + row * pnl_get_bytes_per_row(panel) + byte;
}

static inline uint8_t *pnl_get_ksw_state_byte_address(uint8_t *buffer, uint8_t row, uint8_t col, const panel_t *panel) {
  const uint8_t byte_at_row   = col / 8;
  return pnl_get_byte_from_row(buffer, row, byte_at_row, panel);
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
  pnl_set_ksw_state_in_buffer(pnl_get_current_ksw_state_buffer(panel), row, col, panel, state);
}

static inline keyfunc_t pnl_get_keyfunc(uint8_t row, uint8_t col, const panel_t *panel) {
  return (*panel->userlayout)[row * panel->width + col];
}



#endif // _PANEL_H_

