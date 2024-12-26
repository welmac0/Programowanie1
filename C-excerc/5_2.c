#include <stdio.h>
#include <ctype.h>

float getfloat(float *pn);

float getfloat(float *pn) {
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
    
    if (c == '.') {
        c = getch();
        for(int k = 0; isdigit(c); k++) {
            *pn = *pn / 10.0 + (c-'0') / (10.0 * k);
        }
    }

    *pn *= sign;
    if (c != EOF)
        ungetch();
    return c;
}