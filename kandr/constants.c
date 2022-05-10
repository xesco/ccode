#include <stdio.h>

int main() {

    // long long float
    printf("%Lf\n", 123.0L);
    // byte
    printf("%hhd\n", '\xb');
    // parameter
    printf("%2$d %1$d\n", 10, 20);
    // print base
    printf("%#o\n", 255);
    // width
    printf("%4d\n", 10);
    printf("%*d\n", 4, 10);

    return 0;
}
