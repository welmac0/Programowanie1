#include <stdio.h>

int strend(char *s, char *t);

int main() {
    char s[] = "Hello, world!";
    char t[] = "world!";
    char t2[] = "hello";

    printf("Czy '%s' kończy się na '%s'? %d\n", s, t, strend(s, t));
    printf("Czy '%s' kończy się na '%s'? %d\n", s, t2, strend(s, t2));

    return 0;
}

int strend(char *s, char *t) {
    int len_t = 0;
    while (*++s != '\0')
        ;
    while (*++t != '\0')
        len_t++; 

    for (;len_t>0; len_t--, s--, t--) {
        if (*s != *t)
            return 0;
    }

    return 1;
}