#include <stdio.h>
#include <ctype.h>

// void swap(int *px, int *py);
int getint(int *pn);

int main() {
    int a = 25;
    printf("%d", getint(&a));
}


int getint(int *pn) {
    int c, sign;

    while (isspace(c=getch()))
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch();
        return 0;
    }

    sign = (c == '-') ? -1 : 1;
    
    if (c == '+' || c == '-') {
        int temp = c;
        c = getch();
        if (!isdigi(c)) {
            ungetch(c);
            ungetch(temp);
            return 0;
        }
    }

    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c-'0');
    *pn *= sign;
    if (c != EOF)
        ungetch();
    return c;
}

// void swap(int *px, int *py) {
//     int temp = *px;
//     *px = *py;
//     *py = temp;
// }