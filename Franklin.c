#include <mpi.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


int main(int argc, char** argv) {
    // process rank
    int my_rank;
    // number of processes
    int n;
    
    MPI_Status status; 
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &n);

    MPI_Finalize();
    return 0;
}