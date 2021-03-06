/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

/** @file
 * API for the aspects to implement to create a specific adaptation of an okey keyboard. All code apart from the adaptation code shold be generic and usable for various okey keyboard implementations. The aspects specific to a certain okey keyboard implementation will be defined in the adaption code.
 */

#ifndef _ADAPTATION_H_
#define _ADAPTATION_H_

#include <stdint.h>
#include <stdbool.h>

// forward declaration
struct panel_struct;
typedef struct panel_struct panel_t;

/// holds the specifications of the supported panels and defines the order in which the specified panels will be processed
extern panel_t * const panel_processing[];

/// Number of valid entries in the panel_processing array.  This is
/// also the maximal number of panels that can be driven by this
/// controller (1 master panel and (MAX_SUPPORTED_PANELS-1) slave
/// panels)
extern const uint8_t PANEL_COUNT;

enum level_enum;
typedef enum level_enum level_t;

void adp_await_next_cycle();

#endif // _ADAPTATION_H_
