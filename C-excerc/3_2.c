#include <stdio.h>

void escape(char s[], char t[]);
void escape_reverse(char t[], char u[]);

int main() {
    char t[1000], s[1000], c, u[1000];
    int i = 0;
    while ((c = getchar())!=EOF)
        s[i++] = c;
    s[i] = '\0';
    escape(s, t);   
    printf("Przetworzony tekst: %s\n", t);
    escape_reverse(t, u);
    printf("Przetworzony tekst: %s\n", u);

    return 0;
}

void escape(char s[], char t[]) {
    int i = 0, j = 0;
    
    while (s[i] != '\0') {
        switch (s[i]) {
            case '\t':
                t[j++] = '\\';
                t[j++] = 't';
                break;
            case '\n':
                t[j++] = '\\';
                t[j++] = 'n';
                break;
            default:
                t[j++] = s[i];
                break;
        }
        i++;
    }
    t[j] = '\0';
}

void escape_reverse(char t[], char u[]) {
    int i = 0, j = 0;

    while (t[i] != '\0') {
        if (t[i] == '\\' && t[i + 1] != '\0') {
            switch (t[i + 1]) {
                case 't':
                    u[j++] = '\t';
                    i += 2;
                    continue;
                case 'n':
                    u[j++] = '\n';
                    i += 2; 
                    continue;
                default:
                    u[j++] = t[i++];
                    break;
            }
        } else {
            u[j++] = t[i++];
        }
    }
    u[j] = '\0';
}