#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define N 1000000
void main()
{
    double factor = 1.0, sum = 0.0;
    int i;
#pragma omp parallel for reduction(+ \
                                   : sum) // private(factor)
    for (int i = 0; i < N; i++)
    {
        factor = (i % 2 == 0) ? 1 : -1;
        sum += factor / (2 * i + 1);
    }
    double pi;
    pi = 4 * sum;
    printf("pi= %1.18f", pi);
}
