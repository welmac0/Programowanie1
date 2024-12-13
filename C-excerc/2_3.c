#include <stdio.h>
#include <math.h>

int htoi(char h[]);

int main() {
    printf("%d\n", htoi("0x32"));
}

int htoi(char h[]) {
    int i, d;
    int n = 0;

    if (h[0] == '0' && h[1] == 'x') {
        i = 2;
    } else {
        i = 0;
    }

    for (; h[i] != '\0'; i++) {
        if (i >= 2) {
            if (h[i] >= 'A' && h[i] <= 'F') {
                d = h[i] - 'A' + 10;
            } else if (h[i] >= 'a' && h[i] <= 'f') {
                d = h[i] - 'a' + 10;
            } else if (h[i] >= '0' && h[i] <= '9') {
                d = h[i] - '0';
            } else 
                return -1;
            
            n = 16 * n + d;
        }
    }

    return n;
}