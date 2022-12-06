#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#define SIZE 100000

int *list_gen(int n)
{
    int *list = malloc(sizeof(int) * n);
    for (int i = 0; i < n; ++i)
        list[i] = rand() % n;
    return list;
}

void list_show(int *list, int n)
{
    for (int i = 0; i < n; ++i)
        printf("%d\n", list[i]);
}

void merge(int *list, int *left, int m, int *right, int n)
{
    int p = 0, lp = 0, rp = 0;

    while (lp < m && rp < n)
    {
        if (left[lp] < right[rp])
            list[p++] = left[lp++];
        else
            list[p++] = right[rp++];
    }
    while (lp < m)
        list[p++] = left[lp++];
    while (rp < n)
        list[p++] = right[rp++];
}

void merge_sort(int *list, int n)
{
    if (n < 2)
        return;

    int mid = (n - 1) / 2;
    int *left = malloc(sizeof(int) * (mid + 1));
    int *right = malloc(sizeof(int) * (n - 1 - mid));
    memcpy(left, list, sizeof(int) * (mid + 1));
    memcpy(right, &list[mid + 1], sizeof(int) * (n - 1 - mid));

    merge_sort(left, mid + 1);
    merge_sort(right, n - mid - 1);

    merge(list, left, mid + 1, right, n - mid - 1);

    free(left);
    free(right);
}

void merge_sort_parallel(int *list, int n)
{
    if (n < 2)
        return;

    int mid = (n - 1) / 2;
    int *left = malloc(sizeof(int) * (mid + 1));
    int *right = malloc(sizeof(int) * (n - 1 - mid));
    memcpy(left, list, sizeof(int) * (mid + 1));
    memcpy(right, &list[mid + 1], sizeof(int) * (n - 1 - mid));

#pragma omp task
    merge_sort(left, mid + 1);

#pragma omp task
    merge_sort(right, n - mid - 1);

#pragma omp taskwait
    merge(list, left, mid + 1, right, n - mid - 1);

    free(left);
    free(right);
}

int main(int argc, char *argv[])
{
    double start, stop;
    int *list = list_gen(SIZE);
    int *parallel_list = malloc(sizeof(int) * SIZE);
    memcpy(parallel_list, list, sizeof(int) * SIZE);

    start = omp_get_wtime();
    merge_sort(list, SIZE);
    stop = omp_get_wtime();
    printf("Serial time: %f\n", stop - start);

    start = omp_get_wtime();
    merge_sort_parallel(parallel_list, SIZE);
    stop = omp_get_wtime();
    printf("Parallel time: %f\n", stop - start);

    // list_show(list, SIZE);

    return 0;
}
