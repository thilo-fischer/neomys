#include "ucontroller.h"


typedef enum {
  IOPORT_B,
  IOPORT_C,
  IOPORT_D,
  IOPORT_E,
  IOPORT_F,
  IOPORT_COUNT
} ioport_t;

uint8_t *const DDR_REGISTERS [IOPORT_COUNT] = {DDRB , DDRC , DDRD , DDRE , DDRF };
uint8_t *const PORT_REGISTERS[IOPORT_COUNT] = {PORTB, PORTC, PORTD, PORTE, PORTF};
uint8_t *const PIN_REGISTERS [IOPORT_COUNT] = {PINB , PINC , PIND , PINE , PINF };


#if 0 // deprecated
typedef struct {
  uint8_t bitpos;
  uint8_t *ddr;
  uint8_t *port;
  uint8_t *pin;
} gpio_pin_t;
#else
typedef struct {
  ioport_t port;
  uint8_t bitpos;
} gpio_pin_t;
#endif

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



void uc_spi_transmit_byte(uint8_t mosi, uint8_t *miso) {
  // start transmission by writing output byte to the appropriate register
  SPDR = mosi;
  // busy wait for transmission complete
  while(!(SPSR & (1<<SPIF)));
  // write data received to destination
  *mosi = SPDR;
}
