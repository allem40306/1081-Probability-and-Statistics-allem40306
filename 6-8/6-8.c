#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int id, p;

    int size[2] = {1, 100000000};
    double global_time[2] = {};  /* Time to find, count solutions */
    double elapsed_time;  /* Time to find, count solutions */
    char *arr;
    int i, j, k;

    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Barrier (MPI_COMM_WORLD);
    
    /* Start timer */

    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    
    for(i = 0; i < 2; ++i)
    {
        for(j = 0; j < 50; ++j)
        {
            arr = calloc(size[i], sizeof(char));
            for (k = 0; k < size[i] - 1; ++k) arr[j] = '0';
            arr[size[i] - 1] = '\0';
            elapsed_time = 0.0;
            if(id % 2 == 0)
            {
                elapsed_time = - MPI_Wtime();
                MPI_Send(arr, size[i], MPI_CHAR, id + 1, 0, MPI_COMM_WORLD);
                MPI_Recv(arr, size[i], MPI_CHAR, id + 1, 0, MPI_COMM_WORLD, &status);
                elapsed_time += MPI_Wtime();
                // if(!i)printf("%8.6f\n",elapsed_time);
            }
            else
            {
                MPI_Recv(arr, size[i], MPI_CHAR, id - 1, 0, MPI_COMM_WORLD, &status); 
                MPI_Send(arr, size[i], MPI_CHAR, id - 1, 0, MPI_COMM_WORLD);
            }
            if(!id)
            {
                global_time[i] += elapsed_time;
            }
            free(arr);
        }
    }
    if(!id)
    {
        global_time[0] /= 100;
        global_time[1] /= 100;
        printf("lambda: %8.6f\n", global_time[0]);
        fflush (stdout);
        double beta = size[i] / (global_time[1] - global_time[0]);
        printf ("size=%d: %8.6f, beta=%8.6f\n", size[1], global_time[1], beta);
        fflush (stdout);
    }
    MPI_Finalize();

    return 0;
}
