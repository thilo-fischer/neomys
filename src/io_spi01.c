/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.

   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

#include <avr/io.h>

#include "io_spi01.h"

#include "util.h"
#include "panel.h"

void io_spi01_rst(io_spi01_cfg_t *config, bool state);


#define DDR_SPI DDRB
#define DD_SCK  1
#define DD_MOSI 2
#define DD_MISO 3

void io_spi01_init(const void *cfg) {

  // run this function only once
  static bool initialized = false;
  if (initialized) {
    return;
  }
  initialized = true;

  io_spi01_cfg_t *config = (io_spi01_cfg_t*) cfg;

  set_bit(&DDRB, 0, true); // FIXME use gpio_pin_init instead -- why does it not work ?!
  io_spi01_rst(config, true); // FIXME use gpio_pin_init instead -- why does it not work ?!
  gpio_pin_init(config->rst_pin, GPIO_OUT_HIGH);

  /* Set MOSI and SCK output */
  DDR_SPI |= (1<<DD_MOSI)|(1<<DD_SCK);
  /* Set MISO input */
  DDR_SPI &= ~(1<<DD_MISO);
  /* Enable SPI, LSB first, Master, set clock rate fck/128 */
  SPCR = (1<<SPE)|(1<<DORD)|(1<<MSTR)|(1<<SPR1)|(1<<SPR0);
}

void io_spi01_before_sync(const void *cfg) {
  io_spi01_cfg_t *config = (io_spi01_cfg_t*) cfg;
  io_spi01_rst(config, false);
}

void io_spi01_after_sync(const void *cfg) {
  io_spi01_cfg_t *config = (io_spi01_cfg_t*) cfg;
  io_spi01_rst(config, true);
}

void io_spi01_sync(panel_t *panel) {
#if 0 // currently not in use
  io_spi01_cfg_t *config = (io_spi01_cfg_t*) panel->io_spec.config_data;
#endif

  //io_spi_SS(true);

  const uint16_t bytes_total = pnl_get_single_buffer_size(panel) + (panel->gives_numeric_id ? 1 : 0);
  uint16_t bytes_left = bytes_total;

  uint8_t *current_ksw_state_buffer = pnl_get_current_ksw_state_buffer(panel);

  for (uint8_t row = 0; row < panel->height; ++row) {
    for (uint8_t byte = 0; byte < pnl_get_bytes_per_row(panel); ++byte) {
      uint8_t mosi_byte = 0;
      uint8_t miso_byte = 0;
      if (bytes_left <= panel->out_size) {
 	mosi_byte = panel->out_data[panel->out_size - bytes_left];
      }

      // start transmission by writing a byte to be sent (MOSI) to the appropriate register
      uc_spi_transmit_byte(mosi_byte, &miso_byte);
      *pnl_get_byte_from_row(current_ksw_state_buffer, row, byte, panel) = ~miso_byte;
      
      --bytes_left;
    }
  }

  if (panel->gives_numeric_id) {
    uint8_t mosi_byte = 0;
    if (panel->out_size > 0) {
      mosi_byte = panel->out_data[panel->out_size - 1];
    }
    uc_spi_transmit_byte(mosi_byte, &panel->numeric_id);
  }
  
  //io_spi_SS(false);  
}

void io_spi01_rst(io_spi01_cfg_t *config, bool state) {
  set_bit(&PORTB, 0, state); // FIXME use gpio_outpin_set instead -- why does it not work ?!
  gpio_outpin_set(config->rst_pin, state);
}
