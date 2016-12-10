// Wiktor Adamski
// 272220
// Systemy wbudowane - lista 3 - zadanie 3

#include <stdio.h>

int main(){
    unsigned int licz;
    while(scanf("%u", &licz) != EOF){
        if(licz & (licz - 1) && licz > 0) printf("%u\n", licz);
    }

    return 0;
}