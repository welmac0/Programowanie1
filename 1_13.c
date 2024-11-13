#include <stdio.h>
#define SIZE 30

int main() {
	int nwords[SIZE];
	int c, counter, i, j;
	counter = 0;

	for (i = 0; i < SIZE; ++i)
		nwords[i] = 0;

	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\n' || c =='\t') {
			if (counter < SIZE)
				++nwords[counter];
			counter = 0;
		}
		else 
			++counter;
	}

	if (counter > 0 && counter < SIZE)
		++nwords[counter];

	printf("WORDS:");
	for (i = 1; i < SIZE; ++i) {
		if (nwords[i] > 0) {
			printf("\n%2d|%2d:", i, nwords[i]);
			for (j = 0; j < nwords[i]; ++j)
				printf("-");
		}
	}
		

	return 0;
}