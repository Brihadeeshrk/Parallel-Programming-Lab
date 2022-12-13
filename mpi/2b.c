#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char **argv)
{
    MPI_Init(NULL, NULL);
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Request request1, request2;
    char message[100];
    int len;
    strcpy(message, "Hello, World!");
    len = strlen(message);
    if (world_rank == 0)
    {
        MPI_Isend(&message, len + 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD, &request1);
        MPI_Irecv(&message, 100, MPI_CHAR, 1, 0, MPI_COMM_WORLD, &request2);
        printf("Process 0 received string %s from process 1\n", message);
    }
    else if (world_rank == 1)
    {
        MPI_Isend(&message, len + 1, MPI_CHAR, 0, 1, MPI_COMM_WORLD, &request1);
        MPI_Irecv(&message, 100, MPI_CHAR, 0, 1, MPI_COMM_WORLD, &request2);
        printf("Process 1 received string %s from process 0\n", message);
    }
    MPI_Finalize();
}
