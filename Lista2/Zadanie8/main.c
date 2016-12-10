# define F_CPU 16000000UL

#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>

// Piny 9, 10, 11 (PB1, PB2, PB3) -> diody
// Piny 5, 6, 7 (PD5, PD6, PD7) <- przyciski (pull-up)

#define MAX_PATTERN_LEN 5
#define MIN_DELAY 200

unsigned short pattern[MAX_PATTERN_LEN];
unsigned short trans[3] = {0xdf, 0xbf, 0x7f};
unsigned short pattern_len = 1;

void seedADC(){                // seedowanie rng
    ADMUX |= (1<<REFS0);
    ADCSRA = _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);
    ADMUX = (ADMUX & 0xf0);
    ADCSRA |= _BV(ADSC);
    while(bit_is_clear(ADCSRA,ADIF));;
    ADCSRA |= _BV(ADIF);

    srand(ADC);
}

void display_pattern(){
    for(unsigned short i = 0; i < pattern_len; ++i){
        if(i) _delay_ms(500);
        PORTB |= 1 << (pattern[i] + 1);
        _delay_ms(1000);
        PORTB &= ~(1 << (pattern[i] + 1));
    }
}

void flash_error(){
    for(unsigned short i = 0; i < 5; ++i){
        if(i) _delay_ms(MIN_DELAY);
        PORTB |= 0b00001110;
        _delay_ms(MIN_DELAY);
        PORTB &= 0b11110001;
    }
}

void flash_win(){
    for(unsigned short i = 0; i < 10; ++i){
        PORTB = 0b00001010;
        _delay_ms(MIN_DELAY);
        PORTB = 0b00000100;
        _delay_ms(MIN_DELAY);
    }
    PORTB = 0b00000000;
}

short read_pattern(){
    for(unsigned short i = 0; i < pattern_len; ++i){
        do {} while(PIND >> 5 == 0x7);
        if((PIND | 0x1f) != trans[pattern[i]]) return 0;
        _delay_ms(MIN_DELAY);
        do {} while(PIND >> 5 != 0x7);
    }
    _delay_ms(MIN_DELAY);
    return 1;
}


int main(){
    DDRB  = 0b00001110; // Włączamy output na pinach 9, 10 i 11 (diody)
    DDRD  = 0b00000000;
    PORTD = 0b11100000; // Przyciski będą podłączone pod piny 5, 6, 7 (pull-up)

    seedADC();
    while(1){
        pattern_len = 1;
        for(int i = 0; i < MAX_PATTERN_LEN; ++i){
            pattern[i] = (rand() % 3);
        }
        while(pattern_len <= MAX_PATTERN_LEN){
            display_pattern();
            if(read_pattern()) ++pattern_len;
            else {
                flash_error();
                break;
            }
            if(pattern_len > MAX_PATTERN_LEN) flash_win();
        }
        _delay_ms(MIN_DELAY);
    }
    return 0;
}