/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/



#include <avr/pgmspace.h>
#include <avr/interrupt.h> // FIXME: in use??
#include "delay_wrapper.h"

#include "neomys.h"

#include "ctlrcomm.h"
#include "getkeys.h"
#include "sendkeys.h"

#include "inform.h"

// only needed for the provided init_... functions
#include "uart.h"
#include "usb_keyboard.h"
#include "io.h"


// global symbols


const uint8_t cycle_delay = 20;

// global functions

#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))

static inline void init() {
    CPU_PRESCALE(0);  // run at 16 MHz // TODO good idea?

    init_io();

    // blink LED to destinct master from slave controller
#if (CONTROLLER == CTLR_MASTER)
    init_usb_keyboard();
    inform_blink(SC_BOOT_MASTER);
#else
    inform_blink(SC_BOOT_SLAVE);
#endif

    uint8_t i;
    for (i = 0; i < 8; ++i) {
        progress_blink_pattern();
        _delay_ms(cycle_delay);        
    }

    // Initialize UART only after blinking LED. The delay before UART initialization will reduce the chance of latch up effects (at least if both controllers get powered simultaneously).
    init_uart();
}

int main(void) {
    init();
    while (true) {
        
#if (CONTROLLER == CTLR_MASTER)
        
        int rx_result = rx_keystates();
        if (rx_result == 0) {
            update_own_key_states();
            process_keystates();
        } else {
            inform(IL_ERR, SC_ERR_COMMUNICATION_FAILURE);
        }

        progress_blink_pattern();
        keyseq_queue_progress();

#else // ! (CONTROLLER == CTLR_MASTER)
        
        update_own_key_states();
        tx_keystates();
        // Slave induces the delay between loop iterations, master waits for slave in rx_keystates.
        _delay_ms(cycle_delay);
        
#endif // CONTROLLER == CTLR_MASTER

    }
    return 0;
}
