/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.

   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

/**
 * @file
 * UART-specific implementation for communication among the two teensy controllers.
 * @todo Move all UART-specific stuff from ctlrcomm.c to here.
 */

#include "teensy_codelib/uart/uart.h"

#include "neomys.h"

// UART

// common baudrates: 1200, 2400, 4800, 9600, 14400, 19200, 28800, 38400, 57600, 115200
// Baud rates higher than 4800 seems to cause problems, signal looks pretty messed up in my signal analyser. Is it the UART driver, the Teensy or just my signal analyser that does not work correctly at higher baud rates? FIXME.
//#define UART_BAUD_RATE 38400
#define UART_BAUD_RATE 38400

// Test pattern for experimenting with other baud rates:
#if 0
    while (true) {
        uart_putchar(0xAA);
        _delay_ms(1);
        uart_putchar(0x00);
        _delay_ms(1);
        uart_putchar(0xAA);
        _delay_ms(1);
        uart_putchar(0xFF);
        _delay_ms(1);
        uart_putchar(0xAA);
        _delay_ms(1);
        uart_putchar(0x0F);
        _delay_ms(1);
        uart_putchar(0xAA);
        _delay_ms(1);
        uart_putchar(0xF0);
        _delay_ms(10);
    }
#endif

void init_uart() {
	// Initialize UART only after blinking LED. The delay before UART initialization will reduce the chance of latch up effects (at least if both controllers get powered simultaneously).
	uart_init(UART_BAUD_RATE);
#if (CONTROLLER == CTLR_MASTER)
    uart_putchar(0);
    uart_putchar('M');
#else
    uart_putchar(1);
    uart_putchar('S');
#endif

}

