// Wiktor Adamski
// 272220
// Systemy wbudowane - lista 3 - zadanie 7

#include <stdio.h>

int main(){
    int licz, i, j;
    scanf("%d %d %d", &licz, &i, &j);
    licz = (licz & 1 << i)? licz | 1 << j : licz & ~(1 << j);
    printf("%d\n", licz);

    return 0;
}