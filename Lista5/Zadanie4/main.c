// KOMPILACJA W ARDUINO

#define KOD_URZ 0x00

#include <Wire.h>

char generujSume(char[] tab, int ile){
    char res = 0;
    for (int i = 0; i < ile; ++i){
        res += tab[i];
    }
    return (~tab) + 1;
}

int main(){
    Serial.begin(9600);
    Wire.begin();

    while(1){
        string dir = Serial.readStringUntil(' ');
        unsigned int adres = Serial.parseInt();
        string r = Serial.readStringUntil('\n');
        unsigned int dlugosc = r.toInt();
        if(dir == "read"){
            if(dlugosc){
                Wire.beginTransmission(KOD_URZ);
                Wire.requestFrom(adres, dlugosc);
                char odebrane[dlugosc];
                int i = 0;
                while(Wire.availible()){
                    odebrane[i++] = Wire.read();
                }
                Wire.endTransmission();
                char suma = generujSume(odebrane, i);
                Serial.print(":");
                Serial.print(adres, HEX);
                Serial.print("00");
                for(int j = 0; j < i; ++i){
                    Serial.print(odebrane[j], HEX);
                }
                Serial.println(suma, HEX);
            } else {
                Wire.beginTransmission(KOD_URZ);
                Wire.requestFrom(adres, 1);
                while(Wire.availible()){
                    Serial.println(Wire.read(), HEX);
                }
                Wire.endTransmission();
            }
        }
        else if(dir == "write"){
            if(r.trim() == ""){
                
            }
        }
    }
    return 0;
}