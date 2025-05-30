#include <Arduino.h>
#include <avr/interrupt.h>
#include <avr/io.h>



void setup() {
    DDRD |= _BV(DDD5);
    DDRD |= _BV(DDD2);
}

void loop() {

    if (millis() % 1000 == 0) {
        PORTD ^= _BV(PORTD5);
    }

    if (!(PINC & _BV(PINC5))) {
        PORTD |= _BV(PORTD2);
    } else {
        PORTD &= ~_BV(PORTD2);
    }

}
