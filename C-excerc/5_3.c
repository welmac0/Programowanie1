#include <stdio.h>

void strcat(char *s, char *t) {
    while (*s++ != '\0')
        ;
    s--;
    while ((*s++ = *t++) != '\0')
        ;
}