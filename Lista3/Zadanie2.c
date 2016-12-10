// Wiktor Adamski
// 272220
// Systemy wbudowane - lista 3 - zadanie 2

#include <stdio.h>

int main(int argc, char* argv[]){
    if(argc < 3){
        printf("Użycie: %s plik_wej plik_wyj [-d]\n", argv[0]);
        printf("    Flaga -d powoduje dekompresje pliku wejsciowego do pliku wyjsciowego.\n");
        printf("    Jej brak spowoduje kompresje.\n");
        return 1;
    }
    FILE* wej = fopen(argv[1], "r");
    FILE* wyj = fopen(argv[2], "w");

    if(wej == NULL || wyj == NULL){
        printf("Problem z podanymi plikami.");
        return 1;
    }

    char znak;
    char licznik = 1;

    if(argc == 3){ // Kodowanie z wejscia standardowego
        znak = getc(wej);
        while (znak != EOF){
            char nowy = getc(wej);
            if(nowy != znak || licznik == 127){
                putc(licznik, wyj);
                putc(znak, wyj);
                znak = nowy;
                licznik = 1;
            } else ++licznik;
        }
    } else { // Dekodowanie z wejscia standardowego
        licznik = getc(wej);
        while(licznik != EOF){
            znak = getc(wej);
            while(licznik-- > 0) putc(znak, wyj);
            licznik = getc(wej);
        }
    }

    fclose(wej);
    fclose(wyj);
    return 0;
}