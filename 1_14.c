#include <stdio.h>
#define SIZE 62

int main() {
	int ascii[SIZE];
	int c, i;

	for (i = 0; i < SIZE; ++i)
		ascii[i] = 0;

	while ((c = getchar()) != EOF) {
		if (c != ' ' && c != '\t' && c != '\n') {
			++ascii[c - 'A'];
		}
	}

	for (i = 0; i < SIZE; ++i) {
		if (ascii[i] > 0) {
			printf("%c:%2d\n", i+'A',ascii[i]);
		}
	}

	return 0;
}