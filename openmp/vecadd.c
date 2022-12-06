#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
void vector_add(int *a, int *b, int *c)
{
#pragma omp parallel for
    for (int i = 0; i < 10; i++)
    {
        c[i] = a[i] + b[i];
        printf("a%d + b%d = \n", i, i);
        printf("%d + %d = %d\n", a[i], b[i], c[i]);
    }
}
int main()
{
    int a[10];
    int b[10];
    for (int i = 0; i < 10; i++)
    {
        a[i] = rand() % 20;
        b[i] = rand() % 20;
    }
    int *c = (int *)malloc(10 * sizeof(int));
    vector_add(a, b, c);
    for (int i = 0; i < 10; i++)
    {
        printf("c[%d] = %d", i, c[i]);
    }
}