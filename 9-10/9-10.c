#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int isPrime(long long n)
{
    long long i;
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

    MPI_Init(&argc, &argv);
    MPI_Barrier (MPI_COMM_WORLD);
    void manager(int, int);
    void worker(int, int);

    /* Start timer */
    elapsed_time = - MPI_Wtime();

    MPI_Comm_size(MPI_COMM_WORLD, &p);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);

    if(p < 2)
    {
        printf("Too few process\n");
        fflush (stdout);
        MPI_Finalize();
    }

    if (!id)
    {
        manager(p, id);
    }
    else
    {
        worker(p, id);
    }

    elapsed_time += MPI_Wtime();

    if (!id) {
        printf ("Execution time %8.6f\n", elapsed_time);
        fflush (stdout);
    }

    MPI_Finalize();
    return 0;
}

void manager(int p, int id)
{
    int src, res = 0;
    MPI_Status status;   /* Info about message */
    int L = 2;
    int terminated = 0, cnt = 0;

    do
    {
        MPI_Recv(&res, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        src = status.MPI_SOURCE;

        if (res != 0)
        {
            ++cnt;
            printf ("%lld\n", (1LL << (res-1LL)) * ((1LL << (res)) - 1LL));
            fflush (stdout);
        }

        if (cnt < 8 && L <= 31)
        {
            MPI_Send(&L, 1, MPI_INT, src, 0, MPI_COMM_WORLD);
            ++L;
        }
        else
        { 
            res = 0;
            MPI_Send(&res, 1, MPI_INT, src, 0, MPI_COMM_WORLD);
            ++terminated;
        }
    } while (terminated < (p - 1));
}

void worker(int p, int id)
{
    MPI_Status status;   /* Info about message */
    int tar = 0;
    long long tmp = 0;
    MPI_Send(&tar, 0, MPI_INT, 0, 0, MPI_COMM_WORLD);

    do{
        MPI_Recv(&tar, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        if(tar == 0)
            break;
        tmp = (1LL << (tar)) - 1LL;
        if(isPrime(tmp) == 0)
            tar = 0;

        MPI_Send(&tar, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }while(1);
}