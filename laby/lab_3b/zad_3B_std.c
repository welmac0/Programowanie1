#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> // for usleep

#define M 21             // number of rows
#define N 21             // number of columns
#define OPOZNIENIE 400000 // 40ms in microseconds

// ANSI escape codes for terminal text colors
void setCzerwony() { printf("\033[1;31m"); }  // Red
void setZielony() { printf("\033[1;32m"); }   // Green
void setNiebieski() { printf("\033[1;34m"); } // Blue
void setZolty() { printf("\033[1;33m"); }     // Yellow
void setFioletowy() { printf("\033[1;35m"); } // Purple
void setTurkusowy() { printf("\033[1;36m"); } // Cyan
void setSzary() { printf("\033[1;30m"); }     // Gray
void setBialy() { printf("\033[1;37m"); }     // White
void setDomyslny() { printf("\033[0m"); }     // Reset to default

// Pierwszym argumentem wejściowym jest zawsze tablica, kolejne to rozmiar i na końcu inne zmienne
void wypelnijTablice(int tab[][N], int m, int n, int k);
void ustawKolumne(int tab[][N], int m, int n, int k, int wypelnienie);
void wypiszTablice(int tab[][N], int m, int n);
void choinka(int tab[][N], int m, int n, int img[][2]);
void prostokat(int tab[][N], int m, int n, int index);
void trojkatPrawy(int tab[][N], int m, int n, int index);
void trojkatDolny(int tab[][N], int m, int n, int index);
void transpozycja(int tab[][N], int m, int n);
void przejscie(int[][N], int ilosc_w, int ilosc_k, void(int[][N], int, int, int));

int main()
{
    /* fill in missing variables */
    int tab[M][N];

    int drzewko[][2] = {{0, 1}, {1, 3}, {2, 7}, {3, 3}, {4, 7}, {5, 11}, {6, 15}, {7, 3}, {8, 7}, {9, 11}, {10, 15}, {11, 19}, {12, 3}, {13, 7}, {14, 11}, {15, 15}, {16, 19}, {17, 21}, {18, 4}, {19, 4}, {20, 4}};

    /********************ETAP 0*******************/
    // Change text color
    setZolty();
    printf("Kolor czcionki zolty\n");
    setDomyslny();
    printf("Kolor domyslny...\n\n\n");
    // system("clear"); // Clear terminal on macOS and Linux

    /********************ETAP 1*******************/

    wypelnijTablice(tab, M, N, 1);
    ustawKolumne(tab, M, N, 4, 0);
    wypiszTablice(tab, M, N);
    system("clear");

    /********************ETAP 2*******************/

    choinka(tab, M, N, drzewko);
    wypiszTablice(tab, M, N);
    usleep(OPOZNIENIE+OPOZNIENIE);
    system("clear");

    /********************ETAP 3*******************/

    prostokat(tab, M, N, 0);
    wypiszTablice(tab, M, N);
    system("clear");
    przejscie(tab, M, N, prostokat);
    system("clear");

    /********************ETAP 4*******************/

    wypelnijTablice(tab, M, N, 1);
    trojkatPrawy(tab, M, N, 0);
    wypiszTablice(tab, M, N);
    system("clear");
    przejscie(tab, M, N, trojkatPrawy);
    system("clear");

    /********************ETAP 5*******************/

    wypelnijTablice(tab, M, N, 1);
    trojkatDolny(tab, M, N, 0);
    wypiszTablice(tab, M, N);
    system("clear");
    przejscie(tab, M, N, trojkatDolny);
    system("clear");

    return 0;
}

void przejscie(int t[][N], int ilosc_w, int ilosc_k, void funkcja(int t[][N], int w, int k, int a))
{
    int i;
    for (i = 0; i < ilosc_w / 2 + 1; i++)
    {
        system("clear");
        wypelnijTablice(t, ilosc_w, ilosc_k, 1);
        funkcja(t, ilosc_w, ilosc_k, i);
        wypiszTablice(t, ilosc_w, ilosc_k);
        usleep(OPOZNIENIE); // Pause for OPOZNIENIE microseconds
    }
    for (i = ilosc_w / 2 - 1; i >= -1; i--)
    {
        system("clear");
        wypelnijTablice(t, ilosc_w, ilosc_k, 1);
        funkcja(t, ilosc_w, ilosc_k, i);
        wypiszTablice(t, ilosc_w, ilosc_k);
        usleep(OPOZNIENIE);
    }
}

// Pierwszym argumentem wejściowym jest zawsze tablica, kolejne to rozmiar i na końcu inne zmienne

void wypelnijTablice(int tab[][N], int m, int n, int k)
{
    int i, j;
    for (i = 0; i < m; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            tab[i][j] = k;
        }
    }
}

void ustawKolumne(int tab[][N], int m, int n, int k, int wypelnienie)
{
    int i = 0;
    for (i = 0; i < m; ++i)
    {
        tab[i][k] = wypelnienie;
    }
}

void wypiszTablice(int tab[][N], int m, int n)
{
    int i, j;
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (tab[i][j] == 0)
            {
                setCzerwony();
            }
            printf("%1d", tab[i][j]);
            setDomyslny();
        }
        printf("\n");
    }
}

void choinka(int tab[][N], int m, int n, int img[][2]) {
    int i, j, zeros, start, end, middle;

    // Środek tablicy
    middle = (n - 1) / 2;

    for (i = 0; i < m; i++) {
        zeros = img[i][1]; // szerokość choinki w wierszu
        start = middle - zeros / 2; // lewa krawędź choinki
        end = middle + zeros / 2;   // prawa krawędź choinki

        for (j = 0; j < n; j++) {
            if (j >= start && j <= end) {
                tab[i][j] = 1; // wypełnij choinkę
            } else {
                tab[i][j] = 0; // reszta to "tło"
            }
        }
    }
}

void prostokat(int tab[][N], int m, int n, int index)
{
    int i, j;
    int second_height_index = m - index - 1;
    int second_width_index = n - index - 1;
    for (i = 0; i < m; ++i)
    {
        for (j = 0; j < n; j++)
        {
            if ((i == second_height_index || i == index) && j >= index && j <= second_width_index)
            {
                tab[i][j] = 0;
            }
            else if ((j == index || j == second_width_index) && i >= index && i <= second_height_index)
            {
                tab[i][j] = 0;
            }
            else
            {
                tab[i][j] = 1;
            }
        }
    }
}

void trojkatPrawy(int tab[][N], int m, int n, int index)
{
    int i, j;
    int difference = 9;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            tab[i][j] = 1;
        }
    }

    for (j = 0; j < n; j++)
    {
        if (j >= 10 && j < m-index)
        {
            i = j - 10;
            tab[10][j] = 0;
            while (i > 0) {
                tab[10+i][j] = 0;
                tab[10-i][j] = 0;
                i--;
            }
        }
    }
}

void transpozycja(int tab[][N], int m, int n) {
    int i, j, temp;
    for (i = 0; i < m; i ++) {
        for (j = i + 1; j < n; j++) {
            temp = tab[i][j];
            tab[i][j] = tab[j][i];
            tab[j][i] = temp;
        }
    }
}

void trojkatDolny(int tab[][N], int m, int n, int index) {
    trojkatPrawy(tab, m, n, index);
    transpozycja(tab, m, n);
}

// Implement missing functions here