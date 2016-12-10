// Wiktor Adamski
// 272220
// Systemy wbudowane - lista 3 - zadanie 5

#include <stdio.h>

int parzysta(int licz){
    return ! ((licz & 0x55555555) && (licz & 0xaaaaaaaa));
}

void wypisz_liczbe(int licz){
    for(unsigned int i = 1 << 31; i > 0; i >>= 1){
        putchar(i&licz? '1': '0');
    }
    printf(": %d\n", licz);
}


int main(){
    int pocz, kon;
    scanf("%d %d", &pocz, &kon);
    for(int i = pocz; i <= kon; ++i){
        if(parzysta(i)) wypisz_liczbe(i);
    }
    return 0;
}
