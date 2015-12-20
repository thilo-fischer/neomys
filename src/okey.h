/*
   Neomys - Driver software for my Teensy-based DIY keyboard for the Neo2 keyboard layout.
  
   Copyright (c) 2015 Thilo Fischer
   This program is licenced under GPLv3.
*/

/**
  Central TODO list. Other TODO issues can be found scattered over the
  source code marked with "FIXME" for important issues, "TODO" for
  normal issues, "XXX" for minor issues (eclipse IDE TODO comment
  convention).

  @TODO FIXME provide LED to indicate current level
  @TODO TODO display current target layout selection (extra hardware ?)
  @TODO TODO clean up include dependencies in between generic okay and specific okay adaptation code
  @TODO TODO Teensy-LC (Teensy-3.x) support (http://hackaday.com/2014/04/14/bare-metal-programming-on-the-teensy-3/, http://www.seanet.com/~karllunt/bareteensy31.html)
  @TODO XXX autoadapt numlock/capslock/scrolllock/neo-levellock states based on keyboard led states
  @TODO XXX unicode-characters for different target layouts and Neo2 levels 5&6 (and ẞ•…¥№¤ and such on levels 2, 3 and 4)

 */


#ifndef _OKEY_H_
#define _OKEY_H_

/// initialize the system and run the main loop of reading out the key states and transmitting key codes to the host
int main(void);

/// to be called before entering the main loop
void init();


#endif // _OKEY_H_
