#include <stdio.h>

#define MAXLINE 1000
#define EOL 10

char line[MAXLINE];

int get_line(void);

int main()
{
    int len;
    while ((len = get_line()) > 0)
        printf("%s", line);
    
    return 0;
}

int get_line(void) {
    char c, last_c;
    int i = 0;
    int ignored = 0;

    while ((c = getchar()) != EOF){
        if (i > 0 && c == '/' && last_c == '/' && !ignored) {
            ignored = 1;
            i--;
            if (i > 0)
                i--;
        }
        if (!ignored) {
            line[i++] = c;
        }
        if (c == '\n') {
            ignored = 0;
        }

        last_c = c;
    }

    line[i] = '\0';
    return i;
}