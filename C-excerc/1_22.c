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
    char c;
    int i = 0;
    int search_EOL = 0;

    while ((c = getchar()) != EOF){
        line[i++] = c;
        if (i % EOL == 0)
            search_EOL = 1;
        if (search_EOL == 1 && (c == ' ' || c == '\t')) {
            line[i++] = '\n';
            search_EOL = 0;
        }
    }

    line[i] = '\0';
    return i;
}