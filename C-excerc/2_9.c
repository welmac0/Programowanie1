
int bitcount(unsigned x) {
    int b = 0;
    while (x &= (x-1))
        b += 1;

    return b;
}