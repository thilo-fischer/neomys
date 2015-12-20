#include "ucontroller_teensy++-2.0.h"

#include "ucontroller_AT90USB1286.c"



// TODO
#if 0
void io_init_onboard_led() {
    DDRD |= (1<<6);
}

void io_switch_onboard_led(bool on) {
    if (on == true) {
        PORTD |=  (1<<6);
    } else {
        PORTD &= ~(1<<6);
    }
}

void io_generic_init() {
    init_onboard_led();
}
#endif
