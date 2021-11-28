#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#define BLOCK_LOW(id,p,n)  ((id)*(n)/(p))
#define BLOCK_HIGH(id,p,n) (BLOCK_LOW((id)+1,p,n)-1)
#define BLOCK_SIZE(id,p,n) (BLOCK_HIGH(id,p,n)-BLOCK_LOW(id,p,n)+1)
#define BLOCK_OWNER(index,p,n) (((p)*(index)+1)-1)/(n))

int main(int argc, char **argv)
{
    int id, p;
    double elapsed_time;  /* Time to find, count solutions */
    
    int i;

    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Barrier (MPI_COMM_WORLD);
    
    /* Start timer */
    elapsed_time = - MPI_Wtime();

    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    int *arr = calloc(1000,sizeof(int));
    if(!id)
    {
        for(i = 1; i < p; ++i)
        {
            MPI_Send(arr, 1000, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Recv(arr, 1000, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
        }
    }
    else
    {
        MPI_Recv(arr, 1000, MPI_INT, 0, 0, MPI_COMM_WORLD, &status); 
        MPI_Send(arr, 1000, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    elapsed_time += MPI_Wtime();

    if (!id) {
        printf ("Execution time %8.6f\n", elapsed_time);
        fflush (stdout);
    }

    MPI_Finalize();

    return 0;
}
