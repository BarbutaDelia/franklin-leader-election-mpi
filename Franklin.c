#include <mpi.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#define COM 0
#define TERMINATE 1

int getMinimium(int a, int b){
    return a < b ? a : b;
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

    int lefts[6] = {5, 3, 4, 2, 0, 1}; 
    int rights[6] = {4, 5, 3, 1, 2, 0};
    int left = lefts[my_rank];
    int right = rights[my_rank];
    bool isActive = true;
    int valueFromLeft, valueFromRight;

    while (true){
        if(isActive){
            MPI_Send(&my_rank, 1, MPI_INT, left, COM, MPI_COMM_WORLD);
            MPI_Send(&my_rank, 1, MPI_INT, right, COM, MPI_COMM_WORLD);
            MPI_Recv(&valueFromLeft, 1, MPI_INT, right, COM, MPI_COMM_WORLD, &status);
            MPI_Recv(&valueFromRight, 1, MPI_INT, left, COM, MPI_COMM_WORLD, &status);

            if(getMinimium(valueFromLeft, valueFromRight) > my_rank){
                isActive = false;
            } else if (getMinimium(valueFromLeft, valueFromLeft) == my_rank){
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
                printf("Eu sunt procesul %d si leaderul este %d\n", my_rank, valueFromLeft);
                break;
            }
        }
    }
    MPI_Finalize();
    return 0;  
}