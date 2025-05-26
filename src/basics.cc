#include <Arduino.h>

void _setup() {

    // Set bit to 1
    PORTD = PORTD | (1 << PORTD5);
    // OR
    PORTD |= 1 << PORTD5;
    // OR
    PORTD |= _BV(PORTD5);

    // Set bit to 0
    PORTD &= ~_BV(PORTD5);

    // Toggle bit
    PORTD ^= _BV(PORTD5);

    // Set pin to output
    DDRD |= _BV(DDD5);
    // Set pin value
    PORTD ^= _BV(PORTD5);

    // Inverted because of pull-up-resistor
    if (PINC & _BV(PINC1)) {
        /* Button is not pressed */
    } else {
        /* Button is pressed */
    }

}
