/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

#ifndef _UCONTROLLER_H_
#define _UCONTROLLER_H_

/// specifies a certain GPIO pin of the microcontroller
typedef struct gpio_pin_t;

typedef struct spi_baudrate_t;
typedef struct uart_baudrate_t;


typedef enum {
  GPIO_UNKNOWN = 0,      ///< signals an invalid or uninitialized value
  GPIO_OPEN_DRAIN,       ///< may be used to configure the pin, might be a result when querying the pin if the controller has a dedicated open drain state distinct from the input state
  GPIO_INPUT,            ///< may be used to configure the pin
  GPIO_INPUT_OPEN_DRAIN, ///< may be used to configure the pin
  GPIO_INPUT_PULL_UP,    ///< may be used to configure the pin
  GPIO_INPUT_PULL_DOWN,  ///< may be used to configure the pin
  GPIO_IN_LOW,           ///< may be a result when querying the pin
  GPIO_IN_HIGH,          ///< may be a result when querying the pin
  GPIO_OUT_LOW,          ///< may be used to configure the pin and a result when querying the pin
  GPIO_OUT_HIGH,         ///< may be used to configure the pin and a result when querying the pin
  GPIO_OTHER,            ///< may be a result when querying the pin (but shouldn't ...)
  GPIO_INVALID           ///< may be a result when querying the pin (but shouldn't ...)
} gpio_state_t;


/// initialize the controller: register at host computer as USB keyboard and controller specific initialization (e.g. set up timers, cpu prescaler, ...)
void uc_init();


/// helper function: set a single bit in an 8-bit register to a given value
static inline void set_bit(uint8_t *register, uint8_t bitpos, bool state) {
  if (state) {
    *register |=  (1 << bitpos);
  } else {
    *register &= ~(1 << bitpos);
  }
}

/// helper function: get the value of a single bit in a 8-bit register
static inline bool get_bit(uint8_t *register, uint8_t bitpos) {
  return (register & (1 << bitpos));
}


void gpio_pin_init(gpio_pin_t pin, gpio_state_t state);
gpio_state_t gpio_pin_get_state(gpio_pin_t);

void gpio_outpin_set(gpio_pin_t pin, bool state);
bool gpio_inpin_get(gpio_pin_t);

// functions to toggle to and from open drain state will be implemented only if the controller supports switching from the one state to the other directly
void gpio_outpin_high_to_opendrain(gpio_pin_t);
void gpio_outpin_low_to_opendrain(gpio_pin_t);
void gpio_outpin_opendrain_to_high(gpio_pin_t);
void gpio_outpin_opendrain_to_low(gpio_pin_t);
void gpio_inpin_opendrain_to_pullup(gpio_pin_t);
void gpio_inpin_pullup_to_opendrain(gpio_pin_t);


void uc_spi_transmit_byte(uint8_t mosi, uint8_t *miso);


#endif // _UCONTROLLER_H_
