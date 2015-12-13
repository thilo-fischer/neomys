/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

/** @file
 * Implements the ucontroller.h API for the ATMEGA32U4 microcontroller (and probably other microcontrollers of the same family).
 */

#include <avr/io.h>

#include "ucontroller_ATMEGA32U4.h"

// FIXME why are these symbols not known from iom32u4.h ?!?
#define DDRB  _SFR_IO8(0x04)
#define PORTB _SFR_IO8(0x05)
#define PINB  _SFR_IO8(0x03)

#define DDRC  _SFR_IO8(0x07)
#define PORTC _SFR_IO8(0x08)
#define PINC  _SFR_IO8(0x06)

#define DDRD  _SFR_IO8(0x0A)
#define PORTD _SFR_IO8(0x0B)
#define PIND  _SFR_IO8(0x09)

#define DDRF  _SFR_IO8(0x10)
#define PORTF _SFR_IO8(0x11)
#define PINF  _SFR_IO8(0x0F)


/// arrays allow mapping from ioport_t to the according registers
///@{
uint8_t *const DDR_REGISTERS [IOPORT_COUNT] = {DDRB , DDRC , DDRD , DDRE , DDRF };
uint8_t *const PORT_REGISTERS[IOPORT_COUNT] = {PORTB, PORTC, PORTD, PORTE, PORTF};
uint8_t *const PIN_REGISTERS [IOPORT_COUNT] = {PINB , PINC , PIND , PINE , PINF };
///@}


void uc_init() {
    
}

void uc_spi_transmit_byte(uint8_t mosi, uint8_t *miso) {
  // start transmission by writing output byte to the appropriate register
  SPDR = mosi;
  // busy wait for transmission complete
  while(!(SPSR & (1<<SPIF)));
  // write data received to destination
  *mosi = SPDR;
}


void uc_sleep(uint16_t milliseconds) {
    _delay_ms(milliseconds);
}



void gpio_pin_init(gpio_pin_t pin, gpio_state_t state) {
  switch (state) {
  case GPIO_OPEN_DRAIN:
  case GPIO_INPUT:
  case GPIO_INPUT_OPEN_DRAIN:
    set_bit(DDR_REGISTERS [pin.port], pin.bitpos, false);
    set_bit(PORT_REGISTERS[pin.port], pin.bitpos, false);
    break;
  case GPIO_INPUT_PULL_UP:
    set_bit(DDR_REGISTERS [pin.port], pin.bitpos, false);
    set_bit(PORT_REGISTERS[pin.port], pin.bitpos, true );
    break;
  case GPIO_OUT_LOW:
    set_bit(PORT_REGISTERS[pin.port], pin.bitpos, false);
    set_bit(DDR_REGISTERS [pin.port], pin.bitpos, true );
    break;
  case GPIO_OUT_HIGH:
    set_bit(PORT_REGISTERS[pin.port], pin.bitpos, true );
    set_bit(DDR_REGISTERS [pin.port], pin.bitpos, true );
    break;
  default:
    // TODO signal error
    return;
  }
}

gpio_state_t gpio_pin_get_state(gpio_pin_t) {
  bool ddr = get_bit(DDR_REGISTERS [pin.port], pin.bitpos);
  if (ddr) {
    // output pin
    bool port = get_bit(PORT_REGISTERS[pin.port], pin.bitpos);
    if (port) {
      return GPIO_OUT_HIGH;
    } else {
      return GPIO_OUT_LOW;
    }
  } else {
    // input pin
    bool pin = get_bit(PIN_REGISTERS [pin.port], pin.bitpos);
    if (pin) {
      return GPIO_IN_HIGH;
    } else {
      return GPIO_IN_LOW;
    }
  }
}

void gpio_outpin_set(gpio_pin_t pin, bool state) {
  set_bit(PORT_REGISTERS[pin.port], pin.bitpos, state);
}

bool gpio_inpin_get(gpio_pin_t) {
  return get_bit(PIN_REGISTERS [pin.port], pin.bitpos);
}


// change pin from high output directly to opendrain is not possible on ATMEGA32U4, requires to go through low output or pullup input state
// => function not implemented for this controller!
void gpio_outpin_high_to_opendrain(gpio_pin_t);

void gpio_outpin_low_to_opendrain(gpio_pin_t) {
  set_bit(DDR_REGISTERS [pin.port], pin.bitpos, false);
}

// change pin from opendrain directly to high output is not possible on ATMEGA32U4, requires to go through low output or pullup input state
// => function not implemented for this controller!
void gpio_outpin_opendrain_to_high(gpio_pin_t);

void gpio_outpin_opendrain_to_low(gpio_pin_t) {
  set_bit(DDR_REGISTERS [pin.port], pin.bitpos, true );
}


void gpio_inpin_opendrain_to_pullup(gpio_pin_t) {
  set_bit(PORT_REGISTERS[pin.port], pin.bitpos, true );
}

void gpio_inpin_pullup_to_opendrain(gpio_pin_t) {
  set_bit(PORT_REGISTERS[pin.port], pin.bitpos, false);
}


