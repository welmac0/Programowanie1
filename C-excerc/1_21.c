#include <stdio.h>

#define MAXLINE 1000
#define TABULATOR 4

char line[MAXLINE];

int get_line(void);

int main()
{
    int len;

    while ((len = get_line()) > 0)
        printf("%s", line);
    return 0;
}

int get_line(void)
{
    extern char line[MAXLINE];
    char c;
    int i = 0;
    int sc = 0; // space counter
    while ((c = getchar()) != EOF)
    {
        if (c == ' ')
            sc++;
        else
        {
            if (sc > 0)
            {
                int tabs = sc / 4;
                sc %= 4;
                for (int j = 0; j < tabs; j++)
                    line[i++] = '\t';
                for (int j = 0; j < sc; j++)
                    line[i++] = ' ';
                sc = 0;
            }
            if (i < MAXLINE - 1)
                line[i++] = c;
        }
    }
    line[i] = '\0';
    return i;
}