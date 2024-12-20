#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 1000000

int binsearch_1(int x, int v[], int n);
int binsearch_2(int x, int v[], int n);

int main() {
    int v[N];
    for (int i = 0; i < N; i++) {
        v[i] = i; // Tablica posortowana od 0 do N-1
    }

    int x = N / 2; // Wartość do znalezienia (środek tablicy)
    int result;
    clock_t start, end;

    // Testowanie binsearch_1
    start = clock();
    for (int i = 0; i < 1000; i++) { // Powtarzamy wiele razy, by zmierzyć czas
        result = binsearch_1(x, v, N);
    }
    end = clock();
    printf("binsearch_1 found %d at index %d in %.5f seconds.\n", x, result, (double)(end - start) / CLOCKS_PER_SEC);

    // Testowanie binsearch_2
    start = clock();
    for (int i = 0; i < 1000; i++) { // Powtarzamy wiele razy, by zmierzyć czas
        result = binsearch_2(x, v, N);
    }
    end = clock();
    printf("binsearch_2 found %d at index %d in %.5f seconds.\n", x, result, (double)(end - start) / CLOCKS_PER_SEC);
    
    return 0;
}

int binsearch_1(int x, int v[], int n) {
    int low, high, mid;
    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = low + (high - low) / 2; // Unikamy przepełnienia
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

int binsearch_2(int x, int v[], int n) {
    int low, high, mid;
    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = low + (high - low) / 2; // JAKIES KURWA PRZEPELNIENIE XDDDDD
        if (x <= v[mid])
            high = mid - 1;
        else 
            low = mid + 1;
    }

    if (v[low] == x)
        return low;

    return -1;
}