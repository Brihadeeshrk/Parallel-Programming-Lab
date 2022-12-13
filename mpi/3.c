#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);
    // Get number of processes and check that 4 processes are used
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    // Determine root's rank
    int root_rank = 0;
    // Get my rank
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    // Define my value
    int my_value[2];
    if (my_rank == root_rank)
    {
        int buffer[16];
        for (int i = 0; i < 16; i++)
        {
            buffer[i] = rand() % 30;
        }
        printf("Values to scatter from process %d: %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d\n",
               my_rank, buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5], buffer[6],
               buffer[7], buffer[8], buffer[9], buffer[10], buffer[11], buffer[12], buffer[13], buffer[14],
               buffer[15]);
        MPI_Scatter(buffer, 4, MPI_INT, &my_value, 4, MPI_INT, root_rank,
                    MPI_COMM_WORLD);
    }
    else
    {
        MPI_Scatter(NULL, 4, MPI_INT, &my_value, 4, MPI_INT, root_rank, MPI_COMM_WORLD);
    }
    printf("Process %d, my value = (%d, %d, %d, %d).\n", my_rank, my_value[0],
           my_value[1], my_value[2], my_value[3]);
    int x = my_value[0] + my_value[1];
    int y = my_value[2] + my_value[3];
    int resultVector[2] = {x, y};
    printf("Process %d, my value = (%d, %d).\n", my_rank, resultVector[0], resultVector[1]);
    if (my_rank == root_rank)
    {
        int buffer[8];
        MPI_Gather(&resultVector, 2, MPI_INT, buffer, 2, MPI_INT, root_rank, MPI_COMM_WORLD);
        printf("Values collected on process %d: %d, %d, %d, %d, %d, %d, %d, %d.\n",
               my_rank, buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5], buffer[6],
               buffer[7]);
    }
    else
    {
        MPI_Gather(&resultVector, 2, MPI_INT, NULL, 0, MPI_INT, root_rank, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}