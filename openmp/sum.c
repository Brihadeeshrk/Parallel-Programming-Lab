#include <stdio.h>
#include <omp.h>

void main()
{
    int sum = 0;
    /* OpenMP Parallel For Directive And Critical Section */

#pragma omp parallel for shared(sum)
    for (int i = 1; i <= 100; i++)
    {
#pragma omp critical
        sum = sum + i;
    }

    int serial_sum = 0;

    /* Serial Calculation */
    for (int i = 1; i <= 100; i++)
        serial_sum = serial_sum + i;

    if (serial_sum == sum)
        printf("\nThe Serial And Parallel Sums Are Equal\n");
    else
    {
        printf("\nThe Serial And Parallel Sums Are UnEqual\n");
        exit(1);
    }

    printf("\nThe SumOfElements Of The Array Using OpenMP Directives Is %d\n", sum);
    printf("\nThe SumOfElements Of The Array By Serial Calculation Is %d\n", serial_sum);
}