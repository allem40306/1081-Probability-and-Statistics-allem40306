#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

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
    int L = 33550000, ans = 0;
    int terminated = 0;

    do
    {
        MPI_Recv(&res, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        src = status.MPI_SOURCE;

        if (res)
        {
            ans = res;
        }

        if (ans == 0)
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
    printf ("%d\n", ans);
    fflush (stdout);
}

void worker(int p, int id)
{
    int len;
    MPI_Status status;   /* Info about message */
    int i;
    int tar = 0, tmp;
    MPI_Send(&tar, 0, MPI_INT, 0, 0, MPI_COMM_WORLD);

    do{
        MPI_Recv(&tar, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        if(tar == 0)
            break;
        
        tmp = 1;
        for(i = 2; i <= tar / 2; ++i)
        {
            if(tar % i == 0)
                tmp += i;
        }

        if(tmp != tar)
        {
            tar = 0;
        }

        MPI_Send(&tar, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }while(1);
}