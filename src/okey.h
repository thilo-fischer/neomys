/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/


#ifndef _OKEY_H_
#define _OKEY_H_

/// initialize the system and run the main loop of reading out the key states and transmitting key codes to the host
int main(void);

/// to be called before entering the main loop
void init();


#endif // _OKEY_H_
