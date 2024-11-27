#include <stdio.h>

// int power(int m, int n);

// int main()
// {
// 	int i;

// 	for (i = 0; i < 10; ++i) 
// 		printf("%d %d %d\n", i, power(2, i), power(-3, i)); // argumenty to 2, i; -3, i

// 	return 0;
// }

// int power(int base, int n) // parametr base i n
// {
// 	int i, p;

// 	p = 1;
// 	for (i = 1; i <= n; ++i)
// 		p = p * base;

// 	return p;
// }

float scale(int fahr);

int main()
{
	int i;

	for (i = 0; i < 300; i = i + 20)
		printf("%3dF %3.1fC\n", i, scale(i));
}

float scale(int fahr)
{
	return 5.0 * (fahr - 32.0) / 9.0;
}