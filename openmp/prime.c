
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int isPrime(int x)
{
    for (int i = 2; i <= x / 2; i++)
    {
        if (x % i == 0)
        {
            return 0;
        }
    }
    return 1;
}

void parallelprime(int n)
{
    int x = 2;
#pragma omp parallel
    while (x <= n)
    {
        if (isPrime(x))
        {
            printf("%d ", x);
        }
#pragma omp atomic
        x++;
    }
}

void serialprime(int n)
{
    int x = 2;
    while (x <= n)
    {
        if (isPrime(x))
        {
            printf("%d ", x);
        }
        x++;
    }
}
int main(int argc, char *argv[])
{
    double start = omp_get_wtime();
    parallelprime(100);
    double end = omp_get_wtime();
    printf("Time for parallel execution is %f\n", end - start);
    start = omp_get_wtime();
    serialprime(100);
    end = omp_get_wtime();
    printf("Time for serial execution is %f\n", end - start);
}