#include <mpi.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#define COM 0
#define TERMINATE 1

int getMaximum(int a, int b){
    return a < b ? b : a;
}
int main(int argc, char** argv) {
    // process rank
    int my_rank;
    // number of processes
    int n;

    MPI_Status status; 
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &n);

    // Create the ring by increasing the rank for the right neighbour with 1
    int left = (my_rank - 1 + n) % n;
    int right = (my_rank + 1) % n;

    double startTime, endTime;

    bool isActive = true;
    int valueFromLeft, valueFromRight;

    if (my_rank == n - 2) {
        startTime = MPI_Wtime();
    }

    while (true){
        if(isActive){
            MPI_Send(&my_rank, 1, MPI_INT, left, COM, MPI_COMM_WORLD);
            MPI_Send(&my_rank, 1, MPI_INT, right, COM, MPI_COMM_WORLD);
            MPI_Recv(&valueFromLeft, 1, MPI_INT, right, COM, MPI_COMM_WORLD, &status);
            MPI_Recv(&valueFromRight, 1, MPI_INT, left, COM, MPI_COMM_WORLD, &status);

            if(getMaximum(valueFromLeft, valueFromRight) > my_rank){
                isActive = false;
            } else if (getMaximum(valueFromLeft, valueFromLeft) == my_rank){
                printf("Eu sunt procesul %d si sunt leaderul\n", my_rank);
                MPI_Send(&my_rank, 1, MPI_INT, right, TERMINATE, MPI_COMM_WORLD);
                break;
            }
        } else {
            MPI_Recv(&valueFromLeft, 1, MPI_INT, left, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            if(status.MPI_TAG == COM){
                MPI_Send(&valueFromLeft, 1, MPI_INT, right, COM, MPI_COMM_WORLD);
                MPI_Recv(&valueFromRight, 1, MPI_INT, right, COM, MPI_COMM_WORLD, &status);
                MPI_Send(&valueFromRight, 1, MPI_INT, left, COM, MPI_COMM_WORLD);
            } else {
                MPI_Send(&valueFromLeft, 1, MPI_INT, right, TERMINATE, MPI_COMM_WORLD);
                // printf("Eu sunt procesul %d si leaderul este %d\n", my_rank, valueFromLeft);
                break;
            }
        }
    }

    if (my_rank == n - 2) {
        endTime = MPI_Wtime();
        printf("Timpul total de executie: %f secunde\n", endTime - startTime);
    }
   
    MPI_Finalize();
    return 0;  
}

