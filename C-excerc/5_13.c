#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLEN 1000
#define ALLOCSIZE 10000

char allocbuf[ALLOCSIZE];  // Bufor pamięci
char *allocp = allocbuf;  // Następny wolny wskaźnik

char *alloc(int n) {
    if (allocbuf + ALLOCSIZE - allocp >= n) {  // Sprawdź, czy jest miejsce
        allocp += n;
        return allocp - n;  // Zwróć wskaźnik na początek przydzielonego obszaru
    } else
        return NULL;  
}

void afree(char *p) {
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
}

int readlines(char *lineptr[], int maxlines);
int get_line(char line[], int maxlen);
void writelines(char *lineptr[], int nlines, int n);

char *lineptr[1000];

int main(int argc, char *argv[]) {
    int n = 10, nlines;
    if (argc == 2 && argv[1][0] == '-')
        n = atoi(&argv[1][1]);
    printf("%d",n);
    
    if ((nlines = readlines(lineptr, MAXLEN)) >= 0) {
        writelines(lineptr, nlines, n);
        return 0;
    } else
        return -1;
}

int readlines(char *lineptr[], int maxlines) {
    int len, nlines = 0;
    char *p, line[MAXLEN];
    
    while ((len = get_line(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len - 1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

int get_line(char line[], int maxlen) {
    int c, i = 0;
    while (--maxlen > 0 && (c = getchar()) != EOF && c != '\n') {
        line[i++] = c;
    }
    if (c == '\n') {
        line[i++] = c;
    }
    line[i] = '\0';
    return i;
}

void writelines(char *lineptr[], int nlines, int n) {
    printf("%d", n);
    for (int i = 0; i < n && i < nlines; i++)
        printf("\n%s", lineptr[nlines - n + i]);
}