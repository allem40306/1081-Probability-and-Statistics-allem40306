#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int id, p;
    double elapsed_time;  /* Time to find, count solutions */
    
    int n = 1000000;
    int i;

    int global_sum;
    int sum;

    MPI_Init(&argc, &argv);
    MPI_Barrier (MPI_COMM_WORLD);
    
    /* Start timer */
    elapsed_time = - MPI_Wtime();

    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    sum = 0;
    for(i = id + 1; i <= n; i += p)
        sum = sum + i;

    MPI_Reduce (&sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD); 

    elapsed_time += MPI_Wtime();

    if (!id) {
        printf ("Execution time %8.6f\n", elapsed_time);
        fflush (stdout);
    }

    MPI_Finalize();

    if (!id) {
        printf ("The sum is %d\n", global_sum);
        fflush (stdout);
    }

    return 0;
}
