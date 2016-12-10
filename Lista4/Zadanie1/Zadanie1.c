#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>

#include "HD44780.h"

uint16_t adc_read(uint8_t adcx) {
	ADMUX |= (1<<REFS0);
    ADCSRA = _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);
    ADMUX = (ADMUX & 0xf0);
    ADCSRA |= _BV(ADSC);
    while(bit_is_clear(ADCSRA,ADIF));;
    ADCSRA |= _BV(ADIF);

    return ADC;
}

int main(){
    LCD_Initalize();
    ADCSRA |= _BV(ADEN);
    DDRB = 0x1;
    PORTB = 0b00000110; // Nastawiamy pull-up na przyciskach

    int nast = 30;

    while(1){
        int temp = ((adc_read(0)*5/1024.0) - 0.5) *100;
        if(temp < nast + 1) PORTB |= 0x1;
        else if(temp > nast - 1) PORTB &= ~0x1;
        if(PINB & _BV(PB1)) nast += 1;
        if(PINB & _BV(PB2)) nast -= 1;
        char Napis[32];
        sprintf(Napis, "Temp: %d",temp);
        
        LCD_Home();
        LCD_WriteText(Napis);
        LCD_GoTo(0, 1);
        sprintf(Napis, "Nast: %d",nast);
        LCD_WriteText(Napis);
        //LCD_WriteText("AAAA");
        _delay_ms(100);
    }
    return 0;
}