#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char **argv)
{
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);
    // Find out rank, size
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    char message[100];
    int len;
    if (world_rank == 0)
    {
        strcpy(message, "hello world!");
        len = strlen(message);
        MPI_Send(
            /* data */ &message,
            /* count  */ len + 1,
            /* datatype  */ MPI_CHAR,
            /* destination  = */ 1,
            /* tag          = */ 0,
            /* communicator = */ MPI_COMM_WORLD);
    }
    else if (world_rank == 1)
    {
        MPI_Recv(
            /* data */ &message,
            /* count */ 100,
            /* datatype */ MPI_CHAR,
            /* source */ 0,
            /* tag */ 0,
            /* communicator = */ MPI_COMM_WORLD,
            /* status       = */ MPI_STATUS_IGNORE);
        printf("Process 1 received string %s from process 0\n", message);
    }
    MPI_Finalize();
}