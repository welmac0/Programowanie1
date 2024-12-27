#include <stdio.h>

// 6.2
# define min(a, b) ((a) < (b) ? (a) : (b))
# define max(a, b) ((a) > (b) ? (a) : (b))
struct point {
    int x;
    int y;
};

struct rect {
    struct point pt1;
    struct point pt2;
};

struct point makepoint(int x, int y) {
    struct point temp;

    temp.x = x;
    temp.y = y;
    return temp;
}

// int main() {
//     struct rect screen;
//     struct point middle;
//     struct point makepoint(int, int);

//     screen.pt1 = makepoint(0, 0);
//     screen.pt2 = makepoint(400, 200);
//     middle = makepoint((screen.pt1.x + screen.pt2.x) / 2, (screen.pt1.y + screen.pt2.y) / 2);

//     struct point origin, *pp;
//     origin = makepoint(20, 22);
//     pp = &origin;
//     printf("origin is (%d,%d)\n", (*pp).x, (*pp).y);
//     printf("origin is (%d,%d)\n", pp->x, pp->y); // rownowazne z powyzszym
// }

struct point addpoint(struct point p1, struct point p2) {
    p1.x += p2.x;
    p1.y += p2.y;
    return p1;
}

int ptinrect(struct point p, struct rect r) {
    return p.x >= r.pt1.x && p.x < r.pt2.x && p.y >= r.pt1.y && p.y < r.pt2.y;
}

struct rect canonrect(struct rect r) {
    struct rect temp;

    temp.pt1.x = min(r.pt1.x, r.pt2.x);
    temp.pt1.y = min(r.pt1.y, r.pt2.y);
    temp.pt2.x = max(r.pt1.x, r.pt2.x);
    temp.pt2.y = max(r.pt1.y, r.pt2.y);

    return temp;
}

// 6.3
#include <ctype.h>
#include <string.h>
#define NKEYS (sizeof(keytab) / sizeof(struct key))
#define MAXWORD 100

int getword(char *, int);

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

int binsearch(char *word, struct key tab[], int n);
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
    int n;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            if ((n = binsearch(word, keytab, NKEYS)) >= 0)
                keytab[n].count++;
    for( n = 0; n < NKEYS; n++)
        if (keytab[n].count > 0)
            printf("%4d %s\n", keytab[n].count, keytab[n].word);
    return 0;
}

int binsearch(char *word, struct key tab[], int n) {
    int cond;
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low+high)/2;
        if ((cond = strcmp(word, tab[mid].word))<0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
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
