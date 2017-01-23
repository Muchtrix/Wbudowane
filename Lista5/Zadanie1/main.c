// KOMPILOWAĆ W ARDUINO

#include <arduino.h>
#include <avr/io.h>
#include <math.h>
#include <stdint.h>

#define AT_REA(x) {cli(); x = TCNT1; sei();}
#define RESULT(msg) { unsigned int rs = (kon - pocz) - przes;\
unsigned int rsus = rs >> 4, rsuss = ((rs * 100000) >> 4) % 10000;\
Serial.println(msg); sprintf(bufor, "Cykle: %6u, us: %u.%u", rs, rsus, rsuss); Serial.println(bufor);}


int main(){
    TCCR1A = 0;        // Nastawienie zegara
    TCCR1B = (1 << CS10);
    
    Serial.begin(9600);
    DDRB |= 0b00000100;
    unsigned int pocz, kon, przes = 0;
    char bufor[40];

    AT_REA(pocz);
    AT_REA(kon);
    RESULT("Suche odczytywanie licznika");
    przes = (kon - pocz);

    Serial.println("-----------------");
    
    // Testy uint8_t

    volatile uint8_t a = 0; // WAŻNE - Nie chcemy optymalizacji na zmiennej a
    AT_REA(pocz);
    for(uint8_t i = 1; i <= 100; ++i){
        a += i;
    }
    AT_REA(kon);
    RESULT("Dodawanie uint8_t x100");
    
    AT_REA(pocz);
    for(uint8_t i = 1; i <= 100; ++i){
        a *= i;
    }
    AT_REA(kon);
    RESULT("Mnozenie uint8_t x100");

    AT_REA(pocz);
    for(uint8_t i = 1; i <= 100; ++i){
        a /= i;
    }
    AT_REA(kon);
    RESULT("Dzielenie uint8_t x100");

    Serial.println("-----------------");

    // Testy uint16_t

    volatile uint16_t aa = 0;
    AT_REA(pocz);
    for(uint16_t i = 1; i <= 100; ++i){
        aa += i;
    }
    AT_REA(kon);
    RESULT("Dodawanie uint16_t x100");
    
    AT_REA(pocz);
    for(uint16_t i = 1; i <= 100; ++i){
        aa *= i;
    }
    AT_REA(kon);
    RESULT("Mnozenie uint16_t x100");

    AT_REA(pocz);
    for(uint16_t i = 1; i <= 100; ++i){
        aa /= i;
    }
    AT_REA(kon);
    RESULT("Dzielenie uint16_t x100");

    Serial.println("-----------------");

    // Testy uint32_t

    volatile uint32_t aaa = 0;
    AT_REA(pocz);
    for(uint32_t i = 1; i <= 100; ++i){
        aaa += i;
    }
    AT_REA(kon);
    RESULT("Dodawanie uint32_t x100");
    
    AT_REA(pocz);
    for(uint32_t i = 1; i <= 100; ++i){
        aaa *= i;
    }
    AT_REA(kon);
    RESULT("Mnozenie uint32_t x100");

    AT_REA(pocz);
    for(uint32_t i = 1; i <= 100; ++i){
        aaa /= i;
    }
    AT_REA(kon);
    RESULT("Dzielenie uint32_t x100");

    Serial.println("-----------------");

    // Testy float

    volatile float fl = 0.0;
    AT_REA(pocz);
    for(float i = 1; i <= 100; ++i){
        fl += i;
    }
    AT_REA(kon);
    RESULT("Dodawanie float x100");
    
    AT_REA(pocz);
    for(float i = 1; i <= 100; ++i){
        fl *= i;
    }
    AT_REA(kon);
    RESULT("Mnozenie float x100");

    AT_REA(pocz);
    for(float i = 1; i <= 100; ++i){
        fl /= i;
    }
    AT_REA(kon);
    RESULT("Dzielenie float x100");

    Serial.println("-----------------");

    // Testy double

    volatile double fll = 0.0;
    AT_REA(pocz);
    for(double i = 1; i <= 100; ++i){
        fll += i;
    }
    AT_REA(kon);
    RESULT("Dodawanie double x100");
    
    AT_REA(pocz);
    for(double i = 1; i <= 100; ++i){
        fll *= i;
    }
    AT_REA(kon);
    RESULT("Mnozenie double x100");

    AT_REA(pocz);
    for(double i = 1; i <= 100; ++i){
        fll /= i;
    }
    AT_REA(kon);
    RESULT("Dzielenie double x100");

    Serial.println("-----------------");

    AT_REA(pocz);
    for(double i = 1; i <= 100; ++i){
        fll = sin(i);
    }
    AT_REA(kon);
    RESULT("Sinus x100");
    
    AT_REA(pocz);
    for(double i = 1; i <= 100; ++i){
        fll = log(i);
    }
    AT_REA(kon);
    RESULT("Logarytm x100");

    AT_REA(pocz);
    for(double i = 1; i <= 100; ++i){
        fll = exp(i);
    }
    AT_REA(kon);
    RESULT("Exp x100");

    Serial.println("-----------------");

    AT_REA(pocz);
    for(int i = 0; i < 100; ++i){
        digitalWrite(10, i % 2);
    }
    AT_REA(kon);
    RESULT("Przelaczanie w Arduino api");

    AT_REA(pocz);
    for(int i = 0; i < 100; ++i){
        PINB ^= 0b00000100;
    }
    AT_REA(kon);
    RESULT("Manipulacja rejestrami");
    
    while(1){}
    return 0;
}