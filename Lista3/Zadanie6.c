// Wiktor Adamski
// 272220
// Systemy wbudowane - lista 3 - zadanie 6

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BIG_ENDIAN 0
#define LITTLE_ENDIAN 1

// Funkcja sprawdzajaca endianowosc maszyny
int endianowosc(){
    union{ uint32_t liczba; uint8_t znaki[4];} spr;
    spr.liczba = 0x61626364;
    if(strncmp("abcd", spr.znaki, 4) == 0) return BIG_ENDIAN;
    if(strncmp("dcba", spr.znaki, 4) == 0) return LITTLE_ENDIAN;
}

// konwersja little endian <-> PDP-endian
//                    DCBA <-> BADC
uint32_t li2pdp(uint32_t x){
    uint32_t res = 0;
    res |= (x & 0xffff0000) >> 16;
    res |= (x & 0x0000ffff) << 16;
    return res;
}

// konwersja big endian <-> PDP-endian
//                 ABCD <-> BADC
uint32_t bi2pdp(uint32_t x){
    uint32_t res = 0;
    res |= (x & 0xff00ff00) >> 8;
    res |= (x & 0x00ff00ff) << 8;
    return res;
}

int main(int argc, char* argv[]){
    uint32_t (*trans)(uint32_t) = endianowosc() ? &li2pdp : &bi2pdp;
    if(argc <= 2){
        printf("Uzycie: %s plik_wej plik wyj\n", argv[0]);
        return 1;
    }
    FILE *wej, *wyj;
    wej = fopen(argv[1], "rb");
    wyj = fopen(argv[2], "wb");
    if(wej == NULL || wyj == NULL){
        printf("Wystapil blad przy otwieraniu plikow\n");
        return 1;
    }
    uint32_t liczba;
    while(fread(&liczba, sizeof(uint32_t), 1, wej) == 1){
        liczba = trans(liczba);
        fwrite(&liczba, sizeof(uint32_t), 1, wyj);
    }


    fclose(wej);
    fclose(wyj);
    return 0;
}