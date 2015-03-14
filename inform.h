/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.

   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

#ifndef INFORM_H_
#define INFORM_H_

// TODO
#include "teensy_codelib/uart/uart.h"

enum warnings_e {
    W_TOO_MANY_KEYS,
    W_COMMUNICATION_FAILURE,
    W_PROGRAMMING_ERROR,
    W_MASTER, // FIXME not a warning ... blink LED differently on master or slave controller at startup
    W_SLAVE,  // FIXME not a warning ... blink LED differently on master or slave controller at startup
};


#if (CONTROLLER == CTLR_MASTER)
#  define UART_LOGLEVEL 1
#else
#  define UART_LOGLEVEL 0
#endif

#if (UART_LOGLEVEL == 0)
#define dbg_uarttx_byte(b)
#define dbg_uarttx_usb_keys()

#elif (UART_LOGLEVEL == 1)
static inline void dbg_uarttx_byte(uint8_t b) {
        uart_putchar(b);
}
#define dbg_uarttx_usb_keys()

#else
static inline void dbg_uarttx_byte(uint8_t b) {
    uart_putchar(b);
}
static inline void dbg_uarttx_usb_keys() {
    uart_putchar(0xFF);
    uart_putchar(keyboard_modifier_keys);
    int i;
    for (i = 0; i < 6; ++i) {
        uart_putchar(keyboard_keys[i]);
    }
}

#endif



void init_warn_led();
void warning(enum warnings_e code);
void flash_led();
void update_warn_led();


#endif /* INFORM_H_ */
