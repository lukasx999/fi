#include <Arduino.h>
#include <avr/interrupt.h>
#include <avr/io.h>

// adc = (Vin*1024) / Vref
// Vref = 1.1V


ISR(ADC_vect) {
    Serial.print("conversion complete: ");
    Serial.println(ADC);
}


void setup() {
    Serial.begin(9600);

    // Voltage Reference
    ADMUX &= ~(1 << REFS1);
    ADMUX |=  (1 << REFS0);

    // ADC2
    ADMUX &= ~(1 << MUX3);
    ADMUX |=  (1 << MUX2);
    ADMUX &= ~(1 << MUX1);
    ADMUX &= ~(1 << MUX0);

    // ADC Enable
    ADCSRA |= (1 << ADEN);

    // Enable ADC Interrupt
    ADCSRA |= (1 << ADIE);

    // Enable Global Interrupts
    sei();

}

void loop() {
    delay(100);

    // Start Conversion
    ADCSRA |= (1 << ADSC);
}
