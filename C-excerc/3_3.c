#include <stdio.h>
#define MAXLINE 1000

void expand(char s1[], char s2[]);

int main() {
    char a[] = "a-zp-sa-c0-5";
    char b[MAXLINE];

    expand(a, b);
    printf("%s", b);
}

void expand(char s1[], char s2[]) {
    int i, k = 0;
    char init, last;

    for (i = 0; s1[i] != '\0'; i++) {
        if (i > 0 && s1[i] == '-' && s1[i + 1] != '\0') {
            init = s1[i - 1];
            last = s1[i + 1];
            if ((init >= 'a' && init <= 'z' && last >= 'a' && last <= 'z' && init < last) ||
                (init >= 'A' && init <= 'Z' && last >= 'A' && last <= 'Z' && init < last) ||
                (init >= '0' && init <= '9' && last >= '0' && last <= '9' && init < last)) {
                for (char c = init + 1; c <= last; c++)
                    s2[k++] = c;
                i++;
            } else
                s2[k++] = s1[i];
        } else
            s2[k++] = s1[i];
    }
    s2[k] = '\0';
}

