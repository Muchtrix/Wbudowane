// Wiktor Adamski
// 272220
// Systemy wbudowane - lista 3 - zadanie 4

// Funkcje wypisuja trojkaty na stderr, aby można było wyświetlić tylko
// wyniki pomiaru czasu dla dużych trojkatow

// Dla trojkata o boku 10000 znakow otrzymalem 
// nastepujace (usrednione z 5 prob) wyniki:
// Czas rekursji:          17.75s
// Czas petli podwojnej:   18.54s
// Czas petli pojedynczej: 0.047s

#include <stdio.h>
#include <time.h>

void trojRec(int n){
    if(!n) return;
    trojRec(n - 1);
    for(; n > 0; --n) putc('*', stderr);
    putc('\n', stderr);
    return;
}

void trojPetl(int n){
    for(int i = 1; i <= n; ++i){
        for(int j = 0; j < i; ++j) putc('*', stderr);
        putc('\n', stderr);
    }
    return;
}

void trojTab(int n){
    char tab[n + 1];
    for(int i = 0; i <= n; ++i) tab[i] = '\0';

    for(int i = 0; i < n; ++i){
        tab[i] = '*';
        fprintf(stderr, "%s\n", tab);
    } 
}


int main(){
    int n;
    scanf("%d", &n);
    clock_t zegar = clock();
    trojRec(n);
    zegar = clock() - zegar;
    printf("Czas rekursji:          %fs\n", (float)zegar/CLOCKS_PER_SEC);

    zegar = clock();
    trojPetl(n);
    zegar = clock() - zegar;
    printf("Czas petli podwojnej:   %fs\n", (float)zegar/CLOCKS_PER_SEC);

    zegar = clock();
    trojTab(n);
    zegar = clock() - zegar;
    printf("Czas petli pojedynczej: %fs\n", (float)zegar/CLOCKS_PER_SEC);

    return 0;
}