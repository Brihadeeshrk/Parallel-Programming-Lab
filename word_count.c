// to find the word count of a file using scatter and gather

#include <stdlib.h>
#include <stdio.h>
#include "mpi.h"
#include <string.h>
#define MAXCHAR 73
#define MAXLENGTH 100

int main(int argc, char **argv)
{
    FILE *fp;
    char *filename = "sample.txt";
    char *line = (char *)malloc(MAXLENGTH);
    char *matA = NULL;
    char str[MAXCHAR];
    int rowCount, num_rows, i, my_id,
        root_process, num_procs, rows_per_process, j;

    MPI_Init(&argc, &argv);
    root_process = 0;

    /* find out MY process ID, and how many processes were started. */
    MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    // READ TXT FILE INTO DYNAMIC ARRAY
    if (my_id == root_process)
    {
        fp = fopen(filename, "r");
        if (fp == NULL)
        {
            printf("Could not open file %s", filename);
            return 1;
        }
        // NUMBER OF lines
        size_t count = 1000;
        rowCount = 0;
        while (getline(&line, &count, fp) != -1)
        {
            rowCount++;
        }
        // REWIND file
        rewind(fp);

        matA = (char *)malloc(rowCount * MAXCHAR * sizeof(char));
        i = 0;
        while (getline(&line, &count, fp) != -1)
        {
            for (j = 0; j < MAXCHAR; j++)
            {
                matA[i * MAXCHAR + j] = line[j];
            }
            i++;
            num_rows = i;
        }
        fclose(fp);
    }

    // BCAST rowCount to Calculate rows each process will receive
    MPI_Bcast(&rowCount, 1, MPI_INT, 0, MPI_COMM_WORLD);
    rows_per_process = rowCount / num_procs;

    char *part_matrix = NULL;
    part_matrix = (char *)malloc(rows_per_process * MAXCHAR * sizeof(char));

    MPI_Scatter(matA, rows_per_process * MAXCHAR, MPI_CHAR, part_matrix, rows_per_process * MAXCHAR, MPI_CHAR, 0, MPI_COMM_WORLD);

    if (my_id == root_process)
    {
        free(matA);
    }

    int charsPerThread[4] = {0, 0, 0, 0};
    char lineString[MAXCHAR];

    printf("Process %i received %i rows:\n", my_id, rows_per_process);
    // PRINTING
    for (i = 0; i < rows_per_process; i++)
    {
        printf("PROCESS %i PRINTS LINE NUMBER %zu:\n", my_id, i);
        for (j = 0; j < MAXCHAR; j++)
        {
            printf("%c", part_matrix[i * MAXCHAR + j]);
            printf("%d", size);
        }
        printf("%d", charsPerThread[0]);
        printf("\n");
        // printf("\n%d %d %d %d", charsPerThread[0], charsPerThread[1], charsPerThread[2], charsPerThread[3]);
    }

    free(part_matrix);
    MPI_Finalize();
    return 0;
}