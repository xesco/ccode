#include <stdio.h>

int myatoi(const char str[]);

int main() {
    printf("%d\n", myatoi("1234"));
}

int myatoi(const char s[]) {

    int i, n;

    n = 0;
    for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
        n = 10*n + (s[i] - '0');

    return n;
}
