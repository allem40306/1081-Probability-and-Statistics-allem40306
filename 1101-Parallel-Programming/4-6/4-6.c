#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int id, size;
    double elapsed_time;  /* Time to find, count solutions */

    MPI_Init(&argc, &argv);
    MPI_Barrier (MPI_COMM_WORLD);
    
    /* Start timer */
    elapsed_time = - MPI_Wtime();

    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    printf("Hello world, from process %d\n", id);
    fflush(stdout);

    elapsed_time += MPI_Wtime();

    if (!id) {
        printf ("Execution time %8.6f\n", elapsed_time);
        fflush (stdout);
    }

    MPI_Finalize();
    return 0;
}
