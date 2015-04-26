/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.

   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

/**
 * @file
 * Communication among the two teensy controllers (master and slave keyboard controller).
 * @todo Abstraction from UART interface.
 */

#include "delay_wrapper.h"

#include "ctlrcomm.h"

// XXX
#include "teensy_codelib/uart/uart.h"


extern uint8_t key_states[2][ROW_COUNT]; // XXX

    // No row has 8 keys (COL_COUNT < 8), so every row state byte will always have at least one 0-bit in it. 0xFF is an impossible row byte value, so if can be used to mark beginning and end of a transmission.
    const uint8_t startendbyte = 0xFF;

    void tx_keystates() {
        uint8_t row;
        uart_putchar(startendbyte);
        for (row = 0; row < ROW_COUNT; ++row) {
            uart_putchar(key_states[CTLR_SLAVE][row]);
        }
        uart_putchar(startendbyte);
    }

    void discard_uart() {
        uint8_t available;
        do {
            _delay_ms(1);
            available = uart_available();
            int i;
            for (i = 0; i < available; ++i) {
                uart_getchar();
            }
        } while (available != 0);
    }

    /**
     * @return 0 on success, error code if transmission failure detected: 1 -- start byte not found; 2 -- end byte too early; 3 -- end byte not found.
     */
    int rx_keystates() {
        while (uart_available() == 0);
        uint8_t rx_byte;
        rx_byte = uart_getchar();
        if (rx_byte != startendbyte) {
            discard_uart();
            return 1;
        }
        uint8_t row;
        for (row = 0; row < ROW_COUNT; ++row) {
            rx_byte = uart_getchar();
            if (rx_byte == startendbyte) {
                discard_uart();
                return 2;
            }
            key_states[CTLR_SLAVE][row] = rx_byte;
        }
        rx_byte = uart_getchar();
        if (rx_byte != startendbyte) {
            discard_uart();
            return 3;
        }
        if (uart_available() > 0) {
            discard_uart();
            return 4;
        }
        return 0;
    }

