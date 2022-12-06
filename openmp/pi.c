#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 4
static long num_steps = 1000000;
double step;
void main()
{
    int i;
    double x, pi, sum[NUM_THREADS];
    step = 1.0 / (double)num_steps;
#pragma omp parallel private(i, x)
    {
        int id = omp_get_thread_num();
        for (i = id, sum[id] = 0.0; i < num_steps; i = i + NUM_THREADS)
        {
            x = (i + 0.5) * step;
            sum[id] += 4.0 / (1.0 + x * x);
        }
    }
    for (i = 1; i < NUM_THREADS; i++)
        sum[0] += sum[i];
    pi = sum[0] / num_steps;
    printf("pi = %1.12f\n", pi);
}