/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

/** @file
 * API to address implementation aspects specific to the concrete micro controller in use. 
 */

#ifndef _UCONTROLLER_H_
#define _UCONTROLLER_H_

#include <stdint.h>
#include <stdbool.h>

/// specifies a certain GPIO pin of the microcontroller
struct gpio_pin_struct;
typedef struct gpio_pin_struct gpio_pin_t;

/// parameters to specify a certain SPI baudrate
struct spi_baudrate_struct;
typedef struct spi_baudrate_struct spi_baudrate_t;

/// parameters to specify a certain SPI baudrate
struct uart_baudrate_struct;
typedef struct uart_baudrate_struct uart_baudrate_t;

/// to specify application of a GPIO pin or to query its current application
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
  GPIO_OTHER,            ///< may be a result when querying the pin, e.g. if pin is not used as GPIO but for a special purpose by a specific device (UART, PWM, SPI, ...) and the micro controller's implementation allows to detect this.
  GPIO_INVALID           ///< may be a result when querying the pin (but shouldn't ...)
} gpio_state_t;


/// initialize the controller: register at host computer as USB keyboard and controller specific initialization (e.g. set up timers, cpu prescaler, ...)
void uc_init();

/// transmit one byte via SPI.
/// @param[out] mosi the value to send
/// @param[in]  miso write the value received to this memory location
void uc_spi_transmit_byte(uint8_t mosi, uint8_t *miso);

/// sleep for specified number of milliseconds
void uc_sleep(uint16_t milliseconds);


/// configure the operation mode of a GPIO pin
void gpio_pin_init(gpio_pin_t pin, gpio_state_t state);
/// query the operation mode of a GPIO pin
gpio_state_t gpio_pin_get_state(gpio_pin_t);

/// Set the state of an output pin.
/// Function does (for performance reasons) not verify whether the specified pin really is an output pin. Behavior is undefined if used with a pin that is not an output pin.
void gpio_outpin_set(gpio_pin_t pin, bool state);
/// Read the state of an input pin.
/// Function does (for performance reasons) not verify whether the specified pin really is an input pin. Behavior is undefined if used with a pin that is not an input pin.
bool gpio_inpin_get(gpio_pin_t);

/// functions to toggle to and from open drain state will be implemented only if the controller supports switching from the one state to the other directly
///@{
void gpio_outpin_high_to_opendrain(gpio_pin_t);
void gpio_outpin_low_to_opendrain(gpio_pin_t);
void gpio_outpin_opendrain_to_high(gpio_pin_t);
void gpio_outpin_opendrain_to_low(gpio_pin_t);
void gpio_inpin_opendrain_to_pullup(gpio_pin_t);
void gpio_inpin_pullup_to_opendrain(gpio_pin_t);
///@}

#endif // _UCONTROLLER_H_
