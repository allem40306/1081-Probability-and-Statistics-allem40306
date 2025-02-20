#include <mpi.h>
#include <stdio.h>
#define BLOCK_LOW(id,p,n)  ((id)*(n)/(p))
#define BLOCK_HIGH(id,p,n) (BLOCK_LOW((id)+1,p,n)-1)
#define BLOCK_SIZE(id,p,n) (BLOCK_HIGH(id,p,n)-BLOCK_LOW(id,p,n)+1)
#define BLOCK_OWNER(index,p,n) (((p)*(index)+1)-1)/(n))

int isPrime(int n)
{
    int i;
    for(i = 2; i * i <= n; ++i)
    {
        if(n % i == 0)return 0;
    }
    return 1;
}

int main(int argc, char **argv)
{
    int id, p;
    double elapsed_time;  /* Time to find, count solutions */
    
    int n = 1000000;
    int i;

    int L, R;

    int global_ans;
    int ans;

    MPI_Init(&argc, &argv);
    MPI_Barrier (MPI_COMM_WORLD);
    
    /* Start timer */
    elapsed_time = - MPI_Wtime();

    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    ans = 0;
    L = BLOCK_LOW(id,p,n);
    R = BLOCK_HIGH(id,p,n);
    if(L % 2 == 0) --L;
    if(R % 2 == 0) ++R;

    int last_prime = 0;
    for(i = L; i <= R; ++i)
    {
        if(isPrime(i) == 0)
            continue;
        if(last_prime && ans < i - last_prime)
        {
            ans = i - last_prime;
        }
        last_prime = i;
    }

    MPI_Reduce (&ans, &global_ans, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD); 

    elapsed_time += MPI_Wtime();

    if (!id) {
        printf ("Execution time %8.6f\n", elapsed_time);
        fflush (stdout);
    }

    MPI_Finalize();

    if (!id) {
        printf ("The max gap between two prime pair %d\n", global_ans);
        fflush (stdout);
    }

    return 0;
}
