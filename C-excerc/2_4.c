#include <stdio.h>

void read_t(char t[]);
void squeeze(char s1[], char s2[]);

int main() {
    char a[] = "ABCDEFGHIJKLMNOPRSTUVWYZ";
    char b[] = "ALFABET";

    squeeze(a, b);
    read_t(a);
    read_t(b);
}

void squeeze(char s1[], char s2[]) {
    int i, j, k, flag;
    char s3[1000];

    for (i = 0; s1[i] != '\0'; i++) {
        flag = 0;
        for (j = 0; s2[j] != '\0'; j++) {
            if (s1[i] == s2[j])
                flag = 1;
        }
        if (!flag)
            s3[k++] = s1[i];
    }

    s3[k] = '\0';
    
    for (i = 0; s3[i] != '\0'; i++)
        s1[i] = s3[i];

    s1[++i] = '\0';
}

void read_t(char t[]) {
    int i = 0;

    for(; t[i] != '\0'; i++)
        printf("%c", t[i]);
    
    printf("\n");
}