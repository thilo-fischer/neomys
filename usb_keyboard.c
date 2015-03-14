/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.

   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.

   usb_keyboard.c - USB HID keyboard support
*/

#include "delay_wrapper.h"

#include "teensy_codelib/usb_keyboard/usb_keyboard.h"


void init_usb_keyboard() {
	// Initialize the USB, and then wait for the host to set configuration.
	// If the Teensy is powered without a PC connected to the USB port,
	// this will wait forever.
	usb_init();
	while (!usb_configured()) {
		_delay_ms(5);
	};
	// Wait an extra second for the PC's operating system to load drivers
	// and do whatever it does to actually be ready for input
	_delay_ms(1000);
}

