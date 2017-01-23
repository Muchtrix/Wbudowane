#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>

volatile unsigned int aktualna = 0;
int kod[] ={0b00000, 0b00001, 0b00011, 0b00010,
            0b00110, 0b00111, 0b00101, 0b00100,
            0b01100, 0b01101, 0b01111, 0b01110,
            0b01010, 0b01011, 0b01001, 0b01000,
            0b11000, 0b11001, 0b11011, 0b11010,
            0b11110, 0b11111, 0b11101, 0b11100,
            0b10100, 0b10101, 0b10111, 0b10110,
            0b10010, 0b10011, 0b10001, 0b10000,};

ISR(INT0_vect){
    for(int i = 0; i < 400; ++i){
        _delay_us(1000);
    }
	aktualna = (aktualna + 1) % 32;
	PORTB = kod[aktualna] << 1;
}

ISR(INT1_vect){
	for(int i = 0; i < 400; ++i){
        _delay_us(1000);
    }
	aktualna = (aktualna - 1) % 32;
	PORTB = kod[aktualna] << 1;
}

ISR(PCINT0_vect){
	aktualna = 0;
    PORTB &= ~(0b00111110);
}

int main(void){
	DDRD = 0x0;
	EICRA = 0b1010; 
	EIMSK |= (1 << INT0) | (1 << INT1);     // Turns on INT0 and INT1

	DDRB = 0b00111110;
	PCICR |= (1 << PCIE0);    // set PCIE0 to enable PCMSK0 scan
	PCMSK0 |= (1 << PCINT0);  // set PCINT0 to trigger an interrupt on state change
	sei();

    set_sleep_mode(SLEEP_MODE_PWR_DOWN);   // sleep mode is set here
 
    sleep_enable();     

    while (1){
        sleep_mode();
    }
}