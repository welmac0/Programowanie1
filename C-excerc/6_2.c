#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define NKEYS (sizeof(keytab) / sizeof(struct key))
#define MAXWORD 100

int getword(char *, int);
struct key *
binsearch(char *, struct key *, int);

struct key {
    char *word;
    int count;
};

struct key keytab[] = {
    "auto", 0,
    "break", 0,
    "case", 0,
    "char", 0,
    "continue", 0,
    "default", 0,
    "unsigned", 0,
    "void", 0,
    "volatile", 0,
    "while", 0
};

// int binsearch(char *word, struct key tab[], int n);
int is_special_char(char c);

#define BUFSIZE 100

char buf[BUFSIZE];  // Buffer for ungetch
int bufp = 0;       // Next free position in buf

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE) {
        printf("ungetch: too many characters\n");
    } else {
        buf[bufp++] = c;
    }
}


int main() {
    char word[MAXWORD];
    struct key *p;

    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            if ((p = binsearch(word, keytab, NKEYS)) != NULL)
                p->count++;
    for(p = keytab; p < keytab + NKEYS; p++)
        if (p->count > 0)
            printf("%4d %s\n", p-> count, p->word);
    return 0;
}



struct key *
binsearch(char *word, struct key *tab, int n) {
    int cond;
    struct key *low = &tab[0];
    struct key *high = &tab[n];
    struct key *mid;
    while (low < high) {
        mid = low + (high-low)/2;
        if ((cond = strcmp(word, mid->word))<0)
            high = mid;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return NULL;
}

int getword(char *word, int lim) {
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))
        ;
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    for (; --lim > 0; w++) 
        if (!is_special_char(*w = getch())) {
            ungetch(*w);
            break;
        }
    
    *w = '\0';
    return word[0];
}

// 6.1
int is_special_char(char c) {
    return c == '_' || c == '/' || c== '#' || isalnum(c);
}
