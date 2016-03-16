#include "ucontroller_teensy++-2.0.h"

#include "ucontroller_AT90USB1286.c"


void uc_io_init_onboard_led() {
    DDRD |= (1<<6);
}

void uc_io_switch_onboard_led(bool on) {
    if (on == true) {
        PORTD |=  (1<<6);
    } else {
        PORTD &= ~(1<<6);
    }
}
