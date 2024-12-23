#include <stdio.h>
#include <math.h>
#include <string.h>

void itob(int n, char s[], int b, int max_w);
void reverse(char s[]);

int main() {
    char buffer[20];

    itob(255, buffer, 16, 10);
    printf("255 w systemie szesnastkowym: %s\n", buffer);

    itob(-255, buffer, 16, 8);
    printf("-255 w systemie szesnastkowym: %s\n", buffer);

    itob(10, buffer, 2, 6);
    printf("10 w systemie binarnym: %s\n", buffer);  // Oczekiwane: 1010

    itob(0, buffer, 2, 4);
    printf("0 w systemie binarnym: %s\n", buffer);  // Oczekiwane: 0

    return 0;
}

void itob(int n, char s[], int b, int max_w) {
    int i = 0, k = 0, j, m, w = n;

    if (n == 0)
        s[i++] = '0';

    if (n < 0) {
        s[i++] = '-';
        n = -n;
    }

    while (n / (int)pow(b, k) >= b)
        k++;
    
    while (n>0) {
        m = n / (int)pow(b, k);
        s[i++] = m > 9 ? m - 10 + 'A' : m + '0';
        n -= m * (int)pow(b, k);
        if (n==0 && k>0)
            s[i++] = '0';
        k--;
        
    }

    while (i < max_w)
        s[i++] = 'x';

    s[i] = '\0';
}

void reverse(char s[]) {
    int c, i, j;
    
    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}