#include <stdio.h>
#define MAXLINE 1000

int get_line(char line[], int maxline);
int add(char to[], char from[], int index);

int main() {
	int len, max, index;
	char line[MAXLINE], united[MAXLINE];

	index = 0;
	while ((len = get_line(line, MAXLINE)) > 0) {
			if (len > 1) {
            index += add(united, line, index);
        }
		}

	for (int i = 0; i < index; i++) {
        printf("%c", united[i]);
    }
	return 0;
}

int get_line(char s[], int lim) {
    int c, i, j;

    for (i = 0; i < lim-1 && (c=getchar()) != EOF && c != '\n'; ++i) {
        s[i] = c;
    }
    while (i >= 0 && (s[i] == '\t' || s[i] == ' ')) {
        s[i] = '\0';
        i--;
    }
    if (c == '\n') {
        s[i] = c;
        i++;
    }
    s[i] = '\0';
    return i;
}

int add(char to[], char from[], int index) {
    int i = 0;
    while ((to[index+i] = from[i]) != '\0')
        ++i;

    return index + i;
}