#include <avr/io.h>
#include <util/delay.h>
#include "driver/i2c.h"

#define TARGET_ADDR 4

const char *test_text = "Hello, World!\n";
const int test_text_len = 14;

static void error_loop() {
  PORTB |= _BV(PB3);
  while(1) {

  }
}

/**
 * Setup the LED pin output
 */
static void setup_led() {
  // set pin 3 as output
  DDRB |= _BV(DDB3);
  // disable pullup
  PORTB &= ~_BV(PB3);
}

int main (void) {
  setup_led();
  i2c_init(
    true // using internal pullup resistors
  );
  while(1) {
    if(!i2c_start()) error_loop();
    if (i2c_write_address(TARGET_ADDR, true) & 0x01) {
      // error occurred.
      error_loop();
    }
    for (int i = 0; i < test_text_len; ++i) {
      if (i2c_write_byte(test_text[i]) & 0x01) {
        error_loop();
      }
    }
    i2c_stop();
    _delay_ms(1000);

    if(!i2c_start()) error_loop();

    i2c_write_address(TARGET_ADDR, false);

    unsigned char byte = i2c_read_byte(false);
    if (byte == 42) {
      PORTB ^= _BV(PB3);
    }
    i2c_stop();
    _delay_ms(1000);
  }
}
