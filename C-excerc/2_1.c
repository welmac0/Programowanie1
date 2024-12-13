#include <stdio.h>
#include <limits.h>

int main() {
    printf("Char: od %d do %d\n", CHAR_MIN, CHAR_MAX);
    printf("Unsigned char: od 0 do %u\n", UCHAR_MAX);
    printf("Short: od %d do %d\n", SHRT_MIN, SHRT_MAX);
    printf("Unsigned short: od 0 do %u\n", USHRT_MAX);
    printf("Int: od %d do %d\n", INT_MIN, INT_MAX);
    printf("Unsigned int: od 0 do %u\n", UINT_MAX);
    printf("Long: od %ld do %ld\n", LONG_MIN, LONG_MAX);
    printf("Unsigned long: od 0 do %lu\n", ULONG_MAX);
    return 0;
}