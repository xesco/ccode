#include <stdio.h>

short lenstr(char str[]);

int main() {

    int n = lenstr("Cesc");
    printf("Len is: %d\n", n);

    return 0;
}

short lenstr(char s[]) {
    int i;
    for (i=0; s[i] != '\0'; i++);

    return i;
}
