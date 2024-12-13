#include <stdio.h>
#define MAXLINE 1000

int get_line(char line[]);
void reverse(char s[], int len);

int main() {
    int len;
    char line[MAXLINE];

    while ((len = get_line(line)) > 0) {
        reverse(line, len);
        for (int i = 0; i < len; i++) {
            printf("%c", line[i]);
        }
    }
}

int get_line(char s[]) {
    int c, i, j;

    for (i = 0; i < MAXLINE-1 && (c=getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;

    if (c == '\n') {
        s[i] = c;
        i++;
        }

    s[i] = '\0';
    return i;
}

void reverse(char s[], int len) {
    char z[MAXLINE];
    int i, j;
    for (i = len-1, j = 0; i >= 0; i--, j++)
        z[j] = s[i];
    for (i = 0; i < len; i++)
        s[i] = z[i];
}