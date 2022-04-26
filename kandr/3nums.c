#include <stdio.h>
#include <stdlib.h>
#include <sys/param.h>

#define MIN3(a,b,c) MIN(MIN(a,b),c)
#define MAX3(a,b,c) MAX(MAX(a,b),c)

int main()
{
    int a, b, c;

    printf("Input three different numbers: ");
    scanf("%d%d%d", &a, &b, &c);

    printf("Sum is: %d\n", a+b+c);
    printf("Average is %.2f\n", (a+b+c)/3.0);
    printf("Product is: %d\n", a*b*c);
    printf("Smallest is %d\n", MIN3(a, b, c));
    printf("Largest is %d\n", MAX3(a, b, c));
    
    return 0;
}
