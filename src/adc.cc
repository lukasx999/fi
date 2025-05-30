#include <Arduino.h>
#include <avr/interrupt.h>
#include <avr/io.h>

// adc = (Vin*1024) / Vref
// Vref = 1.1V

ISR(ADC_vect) {
    Serial.print("Conversion complete: ");
    Serial.println(ADC);
}

void ____setup() {
    Serial.begin(9600);

    // // Voltage Reference: AVcc
    // ADMUX &= ~_BV(REFS1);
    // ADMUX |=  _BV(REFS0);

    // Voltage Reference: Internal
    ADMUX |= _BV(REFS1);
    ADMUX |= _BV(REFS0);

    // ADC4
    ADMUX &= ~_BV(MUX3);
    ADMUX |=  _BV(MUX2);
    ADMUX &= ~_BV(MUX1);
    ADMUX &= ~_BV(MUX0);

    // ADC Enable
    ADCSRA |= _BV(ADEN);

    // Enable ADC Interrupt
    ADCSRA |= _BV(ADIE);

    // Set prescaler to 64
    ADCSRA |=  _BV(ADPS2);
    ADCSRA |=  _BV(ADPS1);
    ADCSRA &= ~_BV(ADPS0);

    // Enable Global Interrupts
    sei();

}

void ___loop() {

    // Start Conversion
    ADCSRA |= _BV(ADSC);

}
