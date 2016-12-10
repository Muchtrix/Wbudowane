// Wiktor Adamski
// 272220
// Systemy wbudowane - lista 3 - zadanie 1

#include <stdio.h>
#include <time.h>

int fibRec(int n){
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fibRec(n - 1) + fibRec(n - 2);
}

int fibIter(int n){
    int a = 1, b = 0;
    if (n == 0) return 0;
    for(int i = 1; i < n; ++i){
        int tmp = a;
        a += b;
        b = tmp;
    }
    return a;
}

void pomnoz(int a[4], int b[4], int d[4]){
    int c[4];
    c[0] = a[0]*b[0] + a[1]*b[2];
    c[1] = a[0]*b[1] + a[1]*b[3];
    c[2] = a[2]*b[0] + a[3]*b[2];
    c[3] = a[2]*b[1] + a[3]*b[3];
    for(int i = 0; i < 4; ++i) d[i] = c[i];
}

int fibMatrix(unsigned int n){
    if(n == 0) return 0;
    int mnoz[] = {1,1,1,0}, wyn[] = {1,0,0,1}, tmp[4];
    while(n > 0){
        if(n & 1) pomnoz(mnoz, wyn, wyn);
        pomnoz(mnoz, mnoz, mnoz);
        n >>= 1;
    }
    return wyn[2];
}


int main(){
    int liczba, wynik; 
    while(scanf("%d", &liczba) != EOF){
        clock_t zegar = clock();
        wynik = fibRec(liczba);
        zegar = clock() - zegar;
        printf("Rekurencja: %d\t Czas: %fs\n", wynik, (float)zegar/CLOCKS_PER_SEC);

        zegar = clock();
        wynik = fibIter(liczba);
        zegar = clock() - zegar;
        printf("Iteracja:   %d\t Czas: %fs\n", wynik, (float)zegar/CLOCKS_PER_SEC);

        zegar = clock();
        wynik = fibMatrix(liczba);
        zegar = clock() - zegar;
        printf("Maricerze:  %d\t Czas: %fs\n", wynik, (float)zegar/CLOCKS_PER_SEC);
    }
    return 0;
}