#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y) {
    unsigned y_mask, x_mask; // troche mi tu czat pomagal hehehehe

    y_mask = y & ~(~0 << n);
    y_mask = y_mask << (p + 1 - n);
    x_mask = ~(~(~0 << n) << (p + 1 - n));
    x &= x_mask;
    x |= y_mask;

    return x;
}