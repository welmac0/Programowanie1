#include <stdio.h>
#define MAXLINE 1000

int get_line(char line[], int maxline);
void add(char to[], char from[], int index);

int main() {
	int len, max, index;
	char line[MAXLINE], united[MAXLINE];

	max = 0;
    index = 0;
	while ((len = get_line(line, MAXLINE)) > 0)
		if (len > 80) {
			max += (len);
			add(united, line, index);
            index += (len);
		}

	for (int i = 0; i < max; i++) {
        if (united[i] == '\0') {
            printf("%c", '\n');
        } else {
            printf("%c", united[i]);
        }
    }
	return 0;
}

int get_line(char s[], int lim) {
    int c, i;

    for (i = 0; i < lim-1 && (c=getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        i++;
    }
    s[i] = '\0';
    return i;
}

void add(char to[], char from[], int index) {
    int i = 0;
    while ((to[index+i] = from[i]) != '\0')
        ++i;
}