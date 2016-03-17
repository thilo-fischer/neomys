#include "ucontroller_teensy++-2.0.h"
#include "teensy_codelib/uart/uart.h"

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


#define UART_BAUD_RATE 38400
//#define  UART_BAUD_RATE 19200
//#define UART_BAUD_RATE 9600

void uc_uart_init() {
#if 0
  UCSR1C =
    // 2 Stop bits
    (1<<USBS1)
    |
    // even parity bit
    (1<<UPM11)
    ;
#endif
  uart_init(UART_BAUD_RATE);
}

void uc_uart_cycle() {}

void uc_uart_send_char(char data) {
  uart_putchar(data);
}

void uc_uart_send_blob(const char *data, uint8_t size) {
  const char *end = data + size;
  for (; data != end; ++data) {
    uart_putchar(*data);
  }
  //uc_sleep((msg_size + 4) / 4); // FIXME magic number 4 depends on UART_BAUD_RATE
}

