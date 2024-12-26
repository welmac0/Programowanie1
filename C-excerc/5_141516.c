#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <strings.h>

#define MAXLINES 5000
char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines, int reversed);

void qsort(void *lineptr[], int left, int right, int (*comp)(void *, void *));
int numcmp(char *, char *);
int dircmp(const char *s1, const char *s2);

int main(int argc, char *argv[]) { // 5.14, 5.15, 5.16
    int nlines;
    int numeric = 0;
    int reversed = 0;
    int ignore_capitalised = 0;
    int dir_order = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0)
            numeric = 1;
        else if (strcmp(argv[i], "-r") == 0)
            reversed = 1;
        else if (strcmp(argv[i], "-f") == 0)
            ignore_capitalised = 1;
        else if (strcmp(argv[i], "-d") == 0)
            dir_order = 1;
    }


    if (argc > 1 && strcmp(argv[1], "-n") == 0) {
        numeric = 1;
    } else if (argc > 1 && strcmp(argv[1], "-r") == 0) {
        reversed = 1;
    }
    
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        if (ignore_capitalised)
            qsort((void**) lineptr, 0, nlines-1, (int (*)(void *, void *))(numeric ? numcmp : strcasecmp));
        else if (dir_order)
            qsort((void**) lineptr, 0, nlines-1, (int (*)(void *, void *))(numeric ? numcmp : dircmp));
        else
            qsort((void**) lineptr, 0, nlines-1, (int (*)(void *, void *))(numeric ? numcmp : strcmp));
        writelines(lineptr, nlines, reversed);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}

void qsort(void *v[], int left, int right, int (*comp)(void *, void *)) { // comp jest wskaznikiem do funkcji
    int i, last;                     // ktora pobiera dwa argumenty void * i zwraca int
    void swap(void *v[], int, int);

    if (left >= right)
        return;
    swap(v, left, (left+right)/2);
    last = left;
    for (i = left+1; i<=right; i++) 
        if ((*comp)(v[i], v[left])<0)
            swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last-1, comp);
    qsort(v, last+1, right, comp);
}

int numcmp(char *s1, char *s2) {
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);
    if (v1<v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

void swap(void *v[], int i, int j) {
    void *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/* atof: convert string s to double */
double atof(char s[]) {
    double val, power;
    int i, sign;

    /* Skip white space */
    for (i = 0; isspace(s[i]); i++)
        ;

    /* Handle sign */
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;

    /* Process integer part */
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');

    /* Process fractional part */
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }

    /* Return result with sign */
    return sign * val / power;
}

void writelines(char *lineptr[], int nlines, int reversed) {
    if (reversed) {
        lineptr += nlines;
        while (nlines-- > 0) {
            printf("%s\n", *lineptr--);
        }
    } else {
        while (nlines-- > 0) {
            printf("%s\n", *lineptr++);
        }
    } 
}


int readlines(char *lineptr[], int maxlines) {
    int len, nlines = 0;
    char *p, line[5000];

    while ((len = get_line(line, 5000)) > 0) {
        if (nlines >= maxlines || (p = malloc(len + 1)) == NULL) {
            return -1;
        } else {
            line[len - 1] = '\0';  // Usuń znak nowej linii
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

int dircmp(const char *s1, const char *s2) {
    while (*s1 != '\0' || *s2 != '\0') {
        // Pomijanie niealfanumerycznych znaków
        while (*s1 != '\0' && !isalnum((unsigned char)*s1) && !isspace((unsigned char)*s1))
            s1++;
        while (*s2 != '\0' && !isalnum((unsigned char)*s2) && !isspace((unsigned char)*s2))
            s2++;

        // Porównywanie alfanumerycznych znaków
        if (tolower((unsigned char)*s1) != tolower((unsigned char)*s2))
            return tolower((unsigned char)*s1) - tolower((unsigned char)*s2);

        // Przejście do następnego znaku
        if (*s1 != '\0') s1++;
        if (*s2 != '\0') s2++;
    }
    return 0;
}