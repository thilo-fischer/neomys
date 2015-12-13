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


// forward declarations
struct userlayout_struct;
typedef struct userlayout_struct userlayout_t;


// Computes the number of bytes necessary to store all key switch states of one row.
// (One key switch states corresponds to one bit.)
#define BYTES_PER_ROW(width) ((width + 7) / 8)



/// Initialize the io devices according to cfg.
typedef void (*panel_init_io_func_t)(const void *cfg);
/// Read key switch states of height rows of keys with width keys per row from the hardware into the ksw_states array,
/// read the numeric ID value from the hardware into numeric_id
/// and write out_size bytes of data contained in out_data to the hardware
/// using the io configuration as given by cfg.
typedef void (*panel_sync_io_func_t)(uint8_t ksw_states[][], uint8_t width, uint8_t height, uint8_t *numeric_id, bool gives_numeric_id, const uint8_t out_data[], uint8_t out_size, const void *cfg);
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



typedef struct {
  /// @name Configuration values
  ///@{
  
  /// The number of (logical) key switch columns of the panel. Default: 8
  const uint8_t width;
  /// The number of (logical) key switch rows of the panel. Default: 7
  const uint8_t height;
  /// Whether a numeric ID of the panel will be provided after the last row. Default: true
  const bool gives_numeric_id;

  /// The number of bytes to send to the panel (to drive indicators of the panel's hardware). Default: 2
  const uint8_t out_size;
  
  /// specifies the mechanisms to use to read out the key switch states from the hardware
  /// and to drive indicators (LEDs and such) of the panel's hardware
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
  uint8_t ksw_states[2][height][BYTES_PER_ROW(width)];
  /// If true, find the *k*ey *sw*itch states of the previous cycle at ksw_states[0] and
  /// those of the current cycle at ksw_states[1]; if false, it's the other way around.
  /// By toggling this value each cycle, copying form current to previous buffer is not
  /// necessary.
  bool ksw_states_previous_first;

  uint8_t numeric_id;

  uint8_t out_data[out_size];
  
  ///@}


} panel_t;



void pnl_init_io_all();

void pnl_sync_io_all();

void pnl_process_keystate_changes_all();


#endif // _PANEL_H_

