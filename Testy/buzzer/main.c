#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

short val = 0;

int main(){
    DDRD = 0x0a;
    TCCR2A = _BV(COM2A0) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
    TCCR2B = _BV(WGM22) | _BV(CS22);
    OCR2A = 180;
    OCR2B = 50;
    while (1){
        OCR2A = val;
        _delay_ms(200);
        OCR2A = 0;
        _delay_ms(200);
        val = OCR2A + 5 % 256;
    };

    return 0;
}