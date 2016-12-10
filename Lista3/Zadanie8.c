#include <avr/io.h>

#define DDRREG DDRB
#define PORTREG PORTB

void transfer_byte(char msg, int port, int clk){
    DDRREG |= _BV(port) | _BV(clk);
    PORTREG &= ~_BV(clk);
    for(int i = 0; i < 8; ++i){
        if(msg & 1 << i){
            PORTREG |= _BV(port);
        } else {
            PORTREG &= ~_BV(port);
        }

        PORTREG |= _BV(clk);
        PORTREG &= ~_BV(clk);
    }
}

int main(){
    char *napis = "Przesylane dane";

    for(int i = 0; i < 15; ++i){
        transfer_byte(napis[i], 1, 2);
    }
    while(1){}

    return 0;
}