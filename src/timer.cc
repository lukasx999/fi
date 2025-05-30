#include <Arduino.h>
#include <avr/interrupt.h>
#include <avr/io.h>




///////////////////////////////////////////////////////////////////////////////
// TIMER

// How to make timer overflow at 1s interval:
// fcpu  = 16,000,000Hz
// fcpu  = fcpu / 1024
// fcpu  = 15625Hz
// T     =  1 / fcpu
// T     = 0.000064s
// 4.19s = T * 65535 // counts up to 65535 every 4.19s
// 1s    = T * x     // how far it should count to for 1s
// x     = 1 / T
// x     = 15625     // counts to 15625 every second
//
// x     = 1 / (1/(fcpu/1024))
// x     = fcpu / 1024
// t0    = 65535 - x

static void reset_timer() {
    int prescaler = 1024;
    uint32_t fcpu = 16e6;
    int timer_max = UINT16_MAX;
    TCNT1 = timer_max - fcpu/prescaler;
}

ISR(TIMER1_OVF_vect) {
    Serial.println("Timer Overflow!");
    // Flip PD5
    PORTD ^= _BV(PORTD5);
    reset_timer();
}

void _setup() {
    Serial.begin(9600);

    reset_timer();

    // Set PD5 to output
    DDRD |= _BV(DDD5);

    // Enable overflow interrupts
    TIMSK1 |= _BV(TOIE1);

    // set prescaler to 1024
    TCCR1B |=  _BV(CS12);
    TCCR1B &= ~_BV(CS11);
    TCCR1B |=  _BV(CS10);

    // Reset everything else (Should already be 0 at the start?)
    TCCR1A = 0x0;

    // Enable Global Interrupts
    sei();

}

void _loop() {
    Serial.print("Timer: ");
    // Current value of timer resides withing TCNT1
    Serial.println(TCNT1);
}
