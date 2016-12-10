#define F_CPU 16000000UL
#define BAUD 9600

#define BASE_DEL 200

#include <util/setbaud.h>
#include <avr/io.h>
#include <string.h>
#include <util/delay.h>

#include "HD44780.h"

// Pin 9 (PB1) -> Dioda LED

// Pin 13 (PB5) <- Przycisk (Pull-up)

// Połączenie hd44780:
// 2 -> RS
// 3 -> E
// 4 -> D4
// 5 -> D5
// 6 -> D6
// 7 -> D7

static const struct {const char letter, *code;} MorseMap[] =
{
	{ 'A', ".-" },
	{ 'B', "-..." },
	{ 'C', "-.-." },
	{ 'D', "-.." },
	{ 'E', "." },
	{ 'F', "..-." },
	{ 'G', "--." },
	{ 'H', "...." },
	{ 'I', ".." },
	{ 'J', ".---" },
	{ 'K', ".-.-" },
	{ 'L', ".-.." },
	{ 'M', "--" },
	{ 'N', "-." },
	{ 'O', "---" },
	{ 'P', ".--." },
	{ 'Q', "--.-" },
	{ 'R', ".-." },
	{ 'S', "..." },
	{ 'T', "-" },
	{ 'U', "..-" },
	{ 'V', "...-" },
	{ 'W', ".--" },
	{ 'X', "-..-" },
	{ 'Y', "-.--" },
	{ 'Z', "--.." },
};

void uart_init(void) {
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;

#if USE_2X
    UCSR0A |= _BV(U2X0);
#else
    UCSR0A &= ~(_BV(U2X0));
#endif

    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); /* 8-bit data */
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);   /* Enable RX and TX */
}

char uart_getchar(void) {
    loop_until_bit_is_set(UCSR0A, RXC0); /* Wait until data exists. */
    return UDR0;
}

void uart_putchar(char c) {
    loop_until_bit_is_set(UCSR0A, UDRE0); /* Wait until data register empty. */
    UDR0 = c;
}

void blink_char(char c){
	if(c == '\n') return;
    if(c == ' '){
		PORTB = 0x00;
		_delay_ms(7 * BASE_DEL);
	}else {
		for(char* act = MorseMap[c - 'A'].code; *act != '\0'; ++act){
			switch(*act){
				case '.':
					PORTB = 0x02;
					_delay_ms(BASE_DEL);
					PORTB = 0x00;
					_delay_ms(BASE_DEL);
					break;
				case '-':
					PORTB = 0x02;
					_delay_ms(3 *BASE_DEL);
					PORTB = 0x00;
					_delay_ms(BASE_DEL);
					break;
			}
		}
	}
}

void uart_getstr(char *res){
	char * act = res;
	*act = uart_getchar();
	while (*act != '\n'){
		++act;
	}
	*act = '\0';
}

char read_char(){
    char znak[10];
    unsigned long state = 0x1;
    int cnt = 0;
        while(state & 0xfe000000){
            state = (state >> 1) | (long) ((~PINB>>5) & 1) << 31;
            _delay_ms(50);
        }
        while(state){
            short ones =0;
            while( ~state & 1) state >>= 1;
            while(state & 1){
                ++ones;
                state >>= 1;
            }
            if(ones < 3) znak[cnt] = '.';
            else znak[cnt] = '-';
            ++cnt;
        }
        znak[cnt] = '\0';
    if(!strstr("", znak)) return ' ';
    for(int i = 0; i < 26; ++i){
        if(!strstr(MorseMap[i].code, znak)) return MorseMap[i].letter;
    }
    return 'a';
}

int main(){
    uart_init();
	LCD_Initalize();
    DDRB  = 0b00000010;
    PORTB = 0b00100000;
    while(1){
        //loop_until_bit_is_clear(PINB, PB5);
		char z = read_char();
        LCD_WriteData(z);
    }
    return 0;
}