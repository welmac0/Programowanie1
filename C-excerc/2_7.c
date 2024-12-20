#include <stdio.h>

unsigned invert(x, p, n) {
    return x ^ (~(~0<<(n-1))<<(p+1-n)); // ale to juz napisalem sam i dziala hehe
}