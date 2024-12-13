#include <stdio.h>

#define MAXLINE 1000
#define TABULATOR 4

int max;
char line[MAXLINE];

int get_line(void);

int main() {
    int len;

    max = 0;
    while ((len = get_line()) > 0)
        printf("%s", line);
    return 0;
}

int get_line(void) {
    extern char line[MAXLINE];
    char c;
    int i = 0;
    while ((c=getchar()) != EOF) {
        if (c == '\t') {
            for (int j = 0; j < TABULATOR; j ++)
                line[i+j] = 'v';
            i += TABULATOR;
        } else {
            line[i] = c;
            ++i;
        }
    }
    line[i] = '\0';
    return i;
}