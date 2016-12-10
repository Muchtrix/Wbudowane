#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

// Pin 9  (PB1) -> Dioda IR
// Pin 12 (PB4) <- Odbiornik IR
// Pin 13 (PB5) -> Dioda LED (wbudowana)

int main(){
    DDRB    = 0b00100010;
    TCCR1A  = _BV(COM1A0);
    TCCR1B  = _BV(WGM12) | _BV(CS10);
    OCR1A   = 210;

    while (1){
        OCR1A = 210;
        _delay_ms(1000);
        if (PINB & _BV(PB4)) PORTB |= _BV(PB5);
        else PORTB &= ~_BV(PB5);
        OCR1A = 0;
        _delay_ms(100);
    }
    return 0;
}