#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[])
{
    int iterns, i, itern = 1;
    iterns = 4;
#pragma omp parallel for schedule(static, 2)
    for (i = 0; i < iterns; i++)
    {
        int t = omp_get_thread_num();
        itern += 1;
        itern %= 2;
        printf("thread %d itern %d value: %d\n", t, itern + 1, i);
    }
}