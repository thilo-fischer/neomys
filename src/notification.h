/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

/** @file
 * API to be used to signal states and events to the okey keyboard user.
 */

/**
 * To be called at firmware initialization. May be used to configure pins etc.
 */
void ntf_init();

/**
 * To be called cyclically from the firmware's mainloop. May be used
 * to toggle signals off after certain timeout periods.p
 */
void ntf_cycle();

/**
 * To be called from anywhere in the firmware code when a certain
 * state or event shall be signaled to the okey keyboard user.
 *
 * @param[in] signal An implementation specific value that specifies
 * what and how to signal to the okey keyboard user.
 */
void ntf_signal(uint8_t signal);
