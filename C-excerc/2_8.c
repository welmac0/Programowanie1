
unsigned rightrot(unsigned x, int n) {
    unsigned mask_x = (1 << n) - 1;
    unsigned cycle = x & mask_x;
    cycle = cycle << n;
    x = x >> n;
    return x | cycle;
}