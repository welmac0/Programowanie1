#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define WYM 2
#define ILE_RESTAURACJI 6
#define TYMCZASOWE_ILE_RESTAURACJI 4
#define MAX_OPINII 10
#define DLUGOSC_OPISU 50
#define PROG 4


enum budzet { tanio = 0, umiarkowanie = 1, drogo = 2 };

struct recenzja {
    char opis[DLUGOSC_OPISU];
    int gwiazdki;
};
struct restauracja {
    float wspolrzedne[WYM];
    char* nazwa;
    int ile_opinii;
    struct recenzja* opinie_klientow;
    enum budzet b;
};
typedef struct recenzja recenzja;
typedef struct restauracja restauracja;


restauracja* inicjuj(int ile);
void wypisz_restauracje(restauracja* tab, int ile);
void znajdz_najdalsza(float w[WYM], restauracja* szukane, int ile);
void sprzataj(restauracja* tab, int ile);
void sortuj_recenzje(restauracja* tab, int ile);
void usun_negatywne_recenzje(restauracja* tab, int ile, int prog);
float oblicz_d(float v[2], float u[2]);

int main(int argc, const char * argv[]) {
    float w1[] = { 52.215049, 21.097538 };
    float w2[] = { 52.23049, 21.01532 };
    /*Etap 1 2pkt*/
    restauracja* spis_restauracji = NULL;
    spis_restauracji = inicjuj(TYMCZASOWE_ILE_RESTAURACJI);
    wypisz_restauracje(spis_restauracji, TYMCZASOWE_ILE_RESTAURACJI);
    sprzataj(spis_restauracji, TYMCZASOWE_ILE_RESTAURACJI);
    spis_restauracji = inicjuj(ILE_RESTAURACJI);
    wypisz_restauracje(spis_restauracji, ILE_RESTAURACJI);
    
    /*Etap 2 1pkt*/
    printf("\nSzukanie najdalszej restauracji:\n");
    znajdz_najdalsza(w1, spis_restauracji, ILE_RESTAURACJI);
    znajdz_najdalsza(w2, spis_restauracji, ILE_RESTAURACJI);
    
    /*Etap 3 2pkt*/
    printf("\nPo usunieciu negatywnych recenzji:\n");
    usun_negatywne_recenzje(spis_restauracji, ILE_RESTAURACJI, PROG);
    wypisz_restauracje(spis_restauracji, ILE_RESTAURACJI);
    
    /*Etap 4 2pkt*/
    printf("\nPo posortowaniu recenzji:\n");
    sortuj_recenzje(spis_restauracji, ILE_RESTAURACJI);
    wypisz_restauracje(spis_restauracji, ILE_RESTAURACJI);
   
    sprzataj(spis_restauracji, ILE_RESTAURACJI);
    system("PAUSE");
    return 0;
}


restauracja* inicjuj(int ile)
{
    char* wejscie_recenzja_opis[] = { "Smaczne", "OK","Brudno","Mila obsluga","Stare ziemniaki","Nie ok", "Za drogo","wszystko fajnie","super","opinia negatywna" };
    char* wejscie_nazwa[MAX_OPINII] = { "Smaki ludowe","Kuchnia fusion","Tanie sushi","Bar mleczny","Szybki kes","Slow food" };
    enum budzet wejscie_budzet[] = { tanio,tanio,umiarkowanie,drogo,umiarkowanie,tanio };
    float wejscie_wspolrzedne[][WYM] = { { 52.237049, 21.017532 },{ 52.237049, 21.087538 },{ 52.215049, 21.087538 },{ 52.215049, 21.037538 },{ 52.215049, 21.097538 },{ 52.215449, 21.073530 } };
    //kontynuuj od tego miejsca nie usuwajac powyzszych deklaracji
    //uwaga: aktualnie w funkcji brakuje "return"
    srand((unsigned)time(NULL));

    restauracja *A = (restauracja*)malloc(ile*sizeof(restauracja));
    for (int i = 0; i < ile; i++) {
        restauracja knajpa;
        A[i] = knajpa;

        knajpa.wspolrzedne[0] = wejscie_wspolrzedne[rand() % (5 + 1)][0];
        knajpa.wspolrzedne[1] = wejscie_wspolrzedne[rand() % (5 + 1)][1];
        knajpa.nazwa = wejscie_nazwa[rand() % (5 + 1)];
        knajpa.b = wejscie_budzet[rand() % (2 + 1)];
        knajpa.ile_opinii = 1 + rand() % (9 - 1 + 1);
        recenzja *B = (recenzja*)malloc(knajpa.ile_opinii*(sizeof(recenzja)));
        for (int j = 0; j < knajpa.ile_opinii; j++) {
            recenzja opinia;
            B[j] = opinia;
            opinia.gwiazdki = 1 + rand() % (5 - 1 + 1);
            strncpy(opinia.opis, wejscie_recenzja_opis[rand() % (9 + 1)], DLUGOSC_OPISU);
            opinia.opis[DLUGOSC_OPISU-1] = '\0';
        }
        knajpa.opinie_klientow = B;
    }

    return A;
}

void wypisz_restauracje(restauracja* tab, int ile) {
    for (int i = 0; i < ile; i++) {
        printf("\nRestauracja o nazwie %s, polozna w (%f, %f), polka cenowa: %u\n", tab[i].nazwa, tab[i].wspolrzedne[0], tab[i].wspolrzedne[1], tab[i].b);
        for (int j = 0; j < tab[i].ile_opinii; j++) {
            printf("Recenzja nr %d: %s, gwiazdki: %d\n", j, tab[i].opinie_klientow[j].opis, tab[i].opinie_klientow[j].gwiazdki);
        }
    }
}

void sprzataj(restauracja* tab, int ile) {
    for (int i = 0; i < ile; i++) {
        free(tab[i].opinie_klientow);
    }
    free(tab);
}

void znajdz_najdalsza(float w[WYM], restauracja* szukane, int ile) {
    int najdalsza, i;
    float odleglosc = 0;
    float odleglosc_temp;
    for (i = 0; i < ile; i++) {
        odleglosc_temp = oblicz_d(szukane[i].wspolrzedne, w);
        if (odleglosc_temp > odleglosc) {
            odleglosc = odleglosc_temp;
            najdalsza = i;
        }
    }

    printf("Najdalsza restauracja: %s\n", szukane[najdalsza].nazwa);
    printf("Odleglosc: %f", odleglosc);
}

float oblicz_d(float v[WYM], float u[WYM]) {
    return sqrt(pow(v[0]-u[0], 2) + pow(v[1]-u[1], 2));
}

void usun_negatywne_recenzje(restauracja* tab, int ile, int prog) {
    for (int i = 0; i < ile; i++) {
        int ile_usunietych = 0;

        for (int j = 0; j < tab[i].ile_opinii; ) {
            if (tab[i].opinie_klientow[j].gwiazdki < prog) {
                for (int k = j; k < tab[i].ile_opinii - 1; k++) {
                    tab[i].opinie_klientow[k] = tab[i].opinie_klientow[k+1];
                }
                tab[i].ile_opinii--;
                ile_usunietych++;
            } else {
                j++;
            }
        }

        if (ile_usunietych > 0) {
            recenzja* temp = realloc(tab[i].opinie_klientow, tab[i].ile_opinii * sizeof(recenzja));
            if (temp != NULL) {
                tab[i].opinie_klientow = temp;
            } else {
                printf("Błąd podczas alokacji pamięci!\n");
                exit(1);
            }
        }
    }
}

void sortuj_recenzje(restauracja* tab, int ile) {
    for (int i = 0; i < ile; i++) {
        for (int j = 0; j < tab[i].ile_opinii - 1; j++) {
            for (int k = 0; k < tab[i].ile_opinii - 1 - j; k++) {
                if (tab[i].opinie_klientow[k].gwiazdki > tab[i].opinie_klientow[k+1].gwiazdki) {
                    recenzja temp = tab[i].opinie_klientow[k];
                    tab[i].opinie_klientow[k] = tab[i].opinie_klientow[k+1];
                    tab[i].opinie_klientow[k+1] = temp;
                }
            }
        }
    }
}
