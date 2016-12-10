#define F_CPU 16000000UL
#define BAUD 9600

#define BASE_DEL 200

#include <util/setbaud.h>
#include <avr/io.h>
#include <util/delay.h>

// Pin 9 (PB1) -> Dioda LED
// Pin 3 (PD3) -> Brzęczyk (PWM)

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

    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);
}

char uart_getchar(void) {
    loop_until_bit_is_set(UCSR0A, RXC0);
    return UDR0;
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
					OCR2A = 100;
					PORTB |= 0x02;
					_delay_ms(BASE_DEL);
					OCR2A = 0;
					PORTB &= ~0x02;
					_delay_ms(BASE_DEL);
					break;
				case '-':
					OCR2A = 100;
					PORTB |= 0x02;
					_delay_ms(3 *BASE_DEL);
					OCR2A = 0;
					PORTB &= ~0x02;
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

int main(){
    uart_init();
	LCD_Initalize();
	DDRD |= 0b00001000;
    DDRB = 0b00000010;

	TCCR2A = _BV(COM2A0) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
    TCCR2B = _BV(WGM22) | _BV(CS22);
    OCR2A = 0;

    while(1){
		char napis[30];
		short i = 0;
		while(i < 30 && napis[i - 1] != '\n'){
			napis[i++] = uart_getchar();
		}
		for(short j = 0; j < i-1; ++j){
			blink_char(napis[j]);
		}
    }
    return 0;
}