#include <stdio.h>

void reverse(char s[]);
void itoa(int n, char s[]);

void itoa(int n, char s[]) {
    int i, sign;
    unsigned num;

    if (n < 0) {
        s[i++] = '-';
        num = (unsigned)-n;
    } else
        num = (unsigned)n;
    
    i = 0;
    do
        s[i++] = n % 10 + '0';
    while ((n /= 10) > 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';

    s[0] == '-' ? reverse(s+1) : reverse(s);
}

void reverse(char s[]) {
    int c, i, j;
    
    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}