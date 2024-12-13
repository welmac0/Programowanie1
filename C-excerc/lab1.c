#include<stdio.h>
#include<time.h>
#include<stdlib.h>

void fill1(int tab[], int n, int k);

int main () {
	srand(time(NULL));
	int tab[20];
	for (int i = 0; i < 20; ++i)
		tab[i] = (rand()%(30-0+1));
	fill1(tab, 20, 2);
}

void fill1(int tab[], int n, int k) {
	int i = 0;
	while (i < k) {
		tab[i] = i;
		i++;
	}
	for (i = k; i < n; i++) {
		int suma = 0;
		int j = 0;
		while (j < k) {
			suma += tab[i-j];
			++j;
		}
		tab[i] = suma;
	}
	
	for (i = 0; i < n; ++i) 
		printf("%d ", tab[i]); 
	}
