/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.

   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

/**
 * @file
 * Drive and query the GPIO pins of the teensy boards.
 */

#include <avr/io.h>

// FIXME why are these symbols not known from iom32u4.h ?!?
#define DDRB  _SFR_IO8(0x04)
#define PORTB _SFR_IO8(0x05)
#define PINB  _SFR_IO8(0x03)

#include "io.h"

// TODO Port to Teensy-LC. Then, use 64-bit FIFO (see SPIx_C3) or DMA.

void io_init() {
  io_generic_init();

  // Configure SS pin (PB0) as GPIO output pin
  DDRB |= 1<<0;
  io_spi_SS(false);
  
#if 0 // Teensy-LC should be something like this ...
  // Baud Rate Prescaler
  SPI1_BR = 0x78; // slow
  // SPI1_BR = 0x00; // fast

  // General settings ("Control Registers")
  SPI1_C2 = 0x00 ; // | 0x24 /*DMA*/ | 0x10 /*drive SS pin*/;
  SPI1_C1 = 0x40 /*enable SPI*/ | 0x10 /*Master*/ | 0x01 /*start with LSB*/ ; // | 0x02 /*drive SS pin*/ | 0x08 /*active-low CLK*/;
#else // Teensy 2.0
  
  /* Set MOSI and SCK output, all others input */
  DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK);
  /* Enable SPI, LSB first, Master, set clock rate fck/128 */
  SPCR = (1<<SPE)|(1<<DORD)|(1<<MSTR)|(1<<SPR1)|(1<<SPR0);

#endif
}

void io_spi_SS(bool state) {
  // SS is active low, so activating (true) results in clearing the bit
  if (state) {
    PORTB &= ~(1<<0);
  } else {
    PORTB |=   1<<0;
  }
}
  

/// write data received to in, output out_size bytes of data from out
void io_sync(kmatrix_t in, const uint8_t out, uint8_t out_size) {
  static uint8_t out_buffer[sizeof(kmatrix_t)] = {0};
  memcpy(out_buffer + sizeof(out_buffer) - out_size, out, out_size);

  io_spi_SS(true);

  for (row_t iter = ROW_NUM; ) {
    
 #if 0 // Teensy-LC should be something like this ...
    //while (SPI1_S & 0x80 == 0);
    SPI1_DL = out_buffer[iter];
    while (SPI1_S & 0x80 == 0);
    in[iter] = SPI1_DL;
#else // Teensy 2.0

    /* Start transmission */
    SPDR = out_buffer[iter];
    /* Wait for transmission complete */
    while(!(SPSR & (1<<SPIF)));
    in[iter] = SPDR;
    
#endif
    
  }
  
  io_spi_SS(false);

}

void io_read_switches(kmatrix_raw_t destination) {
  
  
}
