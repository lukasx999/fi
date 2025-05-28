#include <Arduino.h>
#include <avr/interrupt.h>
#include <avr/io.h>

ISR(TIMER1_OVF_vect) {
    PORTD ^= _BV(PORTD4);
    TCNT1 = 0;
}

void setup() {

    TCNT1 = 0;

    DDRD |= _BV(DDD4);

    // set prescaler to 1024
    TCCR1B |=  _BV(CS10);
    TCCR1B &= ~_BV(CS11);
    TCCR1B |=  _BV(CS12);

    // enable overflow interrupts
    TIMSK1 |= _BV(TOIE1);

    TCCR1A = 0x0;

    // enable global interrupts
    sei();

}

void loop() {
}
