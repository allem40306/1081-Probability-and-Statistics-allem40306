#include <mpi.h>
#include <stdio.h>
#define BLOCK_LOW(id,p,n)  ((id)*(n)/(p))
#define BLOCK_HIGH(id,p,n) (BLOCK_LOW((id)+1,p,n)-1)
#define BLOCK_SIZE(id,p,n) (BLOCK_HIGH(id,p,n)-BLOCK_LOW(id,p,n)+1)
#define BLOCK_OWNER(index,p,n) (((p)*(index)+1)-1)/(n))

double f(double i)
{
    double x = i * 0.02;
    return 4.0 / (1.0 + x * x);
}

int main(int argc, char **argv)
{
    int id, p;
    double elapsed_time;  /* Time to find, count solutions */
    
    int n = 1000000;
    int i;

    int L, R;

    double global_sum;
    double sum;

    MPI_Init(&argc, &argv);
    MPI_Barrier (MPI_COMM_WORLD);
    
    /* Start timer */
    elapsed_time = - MPI_Wtime();

    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    sum = 0;
    L = BLOCK_LOW(id,p,n/2) + 1;
    R = BLOCK_HIGH(id,p,n/2) + 1;

    for(i = L; i <= R; ++i)
    {
        sum += 4 * f(2 * i - 1) + 2 * f(2 * i);
    }

    MPI_Reduce (&sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD); 

    elapsed_time += MPI_Wtime();

    if (!id) {
        printf ("Execution time %8.6f\n", elapsed_time);
        fflush (stdout);
    }

    MPI_Finalize();

    if (!id) {
        printf ("The sum is %8.6f\n", (f(0) - f(n) + global_sum) / (3.0 * n));
        fflush (stdout);
    }

    return 0;
}
