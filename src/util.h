/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.

   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

#ifndef _UTIL_H_
#define _UTIL_H_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/// Computes the number of bytes necessary to store all key switch
/// states of one row.  (One key switch states corresponds to one bit.)
/// @todo FIXME deprecated, use bitcount_to_bytecount instead
#define BYTES_PER_ROW(width) (bitcount_to_bytecount(width)

/// @return the number of bytes necessary to store the given number of
/// bits: you will need one byte to store 1 to 8 bits, two bytes to
/// store 9 to 16 bits and so on.
static inline uint8_t bitcount_to_bytecount(uint8_t bitcount) {
  return (bitcount + 7) / 8;
}


/// set a single bit in a byte to a given value (not changing any of the other bits)
static inline void set_bit(uint8_t *byteaddress, uint8_t bitpos, bool state) {
  if (state) {
    *byteaddress |=  (1 << bitpos);
  } else {
    *byteaddress &= ~(1 << bitpos);
  }
}

/// get the value of a single bit in a byte
static inline bool get_bit(uint8_t *byteaddress, uint8_t bitpos) {
  return (*byteaddress & (1 << bitpos));
}



#endif // _UTIL_H_
