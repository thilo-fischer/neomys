/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.

   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

#include <avr/io.h>

#include "io_spi01.h"

void io_spi01_rst(io_spi01_cfg_t *config, bool state);


#define DDR_SPI DDRB
#define DD_SCK  1
#define DD_MOSI 2
#define DD_MISO 3

void io_spi01_init(void *cfg) {

  // run this function only once
  static bool initialized = false;
  if (initialized) {
    return;
  }
  initialized = true;

  
  io_spi01_cfg_t *config = (io_spi01_cfg_t*) cfg;

#if 0
  gpio_pin_init(config.rst_pin, GPIO_OUT_HIGH);
#elif 0
  io_spi01_SS(config, false);
#else 
  io_spi01_rst(config, true);
#endif

  /* Set MOSI and SCK output */
  DDR_SPI |= (1<<DD_MOSI)|(1<<DD_SCK);
  /* Set MISO input */
  DDR_SPI &= ~(1<<DD_MISO);
  /* Enable SPI, LSB first, Master, set clock rate fck/128 */
  SPCR = (1<<SPE)|(1<<DORD)|(1<<MSTR)|(1<<SPR1)|(1<<SPR0);
}

void io_spi01_before_sync(void *cfg) {
  io_spi01_cfg_t *config = (io_spi01_cfg_t*) cfg;
  io_spi01_rst(config, false);
}

void io_spi01_after_sync(void *cfg) {
  io_spi01_cfg_t *config = (io_spi01_cfg_t*) cfg;
  io_spi01_rst(config, true);
}

void io_spi01_sync(uint8_t ksw_states[][], uint8_t width, uint8_t height, uint8_t *numeric_id, bool gives_numeric_id, const out_data[], uint8_t out_size, const void *cfg) {
  io_spi01_cfg_t *config = (io_spi01_cfg_t*) cfg;

  //io_spi_SS(true);

  const uint16_t bytes_total = height * BYTES_PER_ROW(width) + (gives_numeric_id ? 1 : 0);
  uint16_t bytes_left = bytes_total;

  for (uint8_t row = 0; row < height; ++row) {
    for (uint8_t col = 0; col < BYTES_PER_ROW(width); ++col) {

      // start transmission by writing a byte to be sent (MOSI) to the appropriate register
      if (bytes_left > out_size) {
	uc_spi_transmit_byte(0, &ksw_states[row][col]);
      } else {
 	uc_spi_transmit_byte(out_data[out_size - bytes_left], &ksw_states[row][col]);
      }

      
    }
  }

  if (gives_numeric_id) {
    if (out_size > 0) {
      uc_spi_transmit_byte(out_data[out_size - 1], numeric_id);
    } else {
      uc_spi_transmit_byte(0, numeric_id);
    }
  }
  
  //io_spi_SS(false);  
}

#if 0
void io_spi01_SS(io_spi01_cfg_t *config, bool state) {
  // SS is active low, so activating (true) results in clearing the bit
  gpio_outpin_set(config.rst_pin, !state);
}
#else
void io_spi01_rst(io_spi01_cfg_t *config, bool state) {
  gpio_outpin_set(config.rst_pin, state);
}
#endif
