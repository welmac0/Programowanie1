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

int get_line(void) { // zmienione przez gpt na potrzeby 5.12
    int c, i = 0, pos = 0;

    while ((c = getchar()) != EOF && c != '\n' && i < MAXLINE - 1) {
        if (c == '\t') {
            int spaces = TABULATOR - (pos % TABULATOR); // Liczba spacji do najbliższego punktu tabulacji
            if (i + spaces >= MAXLINE - 1) // Zapobiega przepełnieniu
                break;
            for (int j = 0; j < spaces; j++) {
                line[i++] = ' ';
                pos++;
            }
        } else {
            line[i++] = c;
            pos++;
        }
    }
    if (c == '\n') {
        line[i++] = c;
    }
    line[i] = '\0'; // Kończy linię
    return i;
}