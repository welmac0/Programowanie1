#include <stdio.h>

int any(char s1[], char s2[]);

int main() {
    char a[] = "GOWNO"; // Z
    char b[] = "DUPY";
    char c[] = "CHUJ";

    printf("%s, %s = %d\n", a, b, any(a, b));
    printf("%s, %s = %d\n", b, c, any(b, c));
    printf("%s, %s = %d\n", a, c, any(a, c));
}

int any(char s1[], char s2[]) {
    int i, j;

    for (i = 0; s1[i] != '\0'; i++) {
        for (j = 0; s2[j] != '\0'; j++) {
            if (s1[i] == s2[j])
                return j;
        }
    }

    return -1;
}