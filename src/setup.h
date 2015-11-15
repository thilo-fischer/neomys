/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.

   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

#ifndef _SETUP_H_
#define _SETUP_H_


#define LIO_GPIO 1
#define LIO_SPI  2

#define LOCAL_IO LIO_SPI


#define ROLE_MASTER 1
#define ROLE_SLAVE  2

// may be defined from build script
#ifndef LOCAL_ROLE
#define LOCAL_ROLE ROLE_MASTER
#endif


#if LOCAL_ROLE == ROLE_MASTER

#  define MAX_ELEMENT_COUNT 4

#  define ROE_UART 1
#  define ROE_SPI  2

#  define READ_OTHER_ELEMENT ROE_SPI

#endif // ROLE_MASTER



#define DO_UART

#define DBG_OUT DO_UART


#endif // _SETUP_H_
