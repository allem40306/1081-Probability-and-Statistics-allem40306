#include <mpi.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gmp.h>
#define BLOCK_LOW(id,p,n)  ((id)*(n)/(p))
#define BLOCK_HIGH(id,p,n) (BLOCK_LOW((id)+1,p,n)-1)
#define BLOCK_SIZE(id,p,n) (BLOCK_HIGH(id,p,n)-BLOCK_LOW(id,p,n)+1)
#define BLOCK_OWNER(index,p,n) (((p)*(index)+1)-1)/(n))
const int MXS = 100000;

int main(int argc, char **argv)
{
    int id, p;
    int node;
    double elapsed_time;  /* Time to find, count solutions */
    int L, R;
    MPI_Status status;
    
    int i;
    int n = 1000000, d = 100;

    mpf_t global_sum, sum, x, y, z;

    char *word;
    int length;
    int lExponent;
    mp_exp_t exponent;
    mpf_t rExponent, tmp;

    mpf_init2(global_sum,(1 << 13));
    mpf_init2(sum,(1 << 13));
    mpf_init2(x,(1 << 13));
    mpf_init2(y,(1 << 13));
    mpf_init2(rExponent,(1 << 13));
    mpf_init2(tmp,(1 << 13));
    mpf_set_si(x,1);

    MPI_Init(&argc, &argv);
    MPI_Barrier (MPI_COMM_WORLD);
    
    /* Start timer */
    elapsed_time = - MPI_Wtime();

    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    L = BLOCK_LOW(id,p,n) + 1;
    R = BLOCK_HIGH(id,p,n) + 1;

    for(i = L; i <= R; ++i)
    {
        mpf_div_ui(y,x,i);
        mpf_add(sum,sum,y);
    }

    if(id)
    {
        word = mpf_get_str(NULL, &exponent, 10, 0, sum);
        length = strlen(word);

        MPI_Send(&id, 1, MPI_INT, 0, 0,
                 MPI_COMM_WORLD); // So the master knows who I am
        MPI_Send(&exponent, 1, MPI_LONG, 0, 0,
                 MPI_COMM_WORLD); // Send the exponent
        MPI_Send(&length, 1, MPI_INT, 0, 0,
                 MPI_COMM_WORLD); // Send the length of the string
        MPI_Send(word, strlen(word) + 1, MPI_CHAR, 0, 0,
                 MPI_COMM_WORLD); // Send the string
    }
    else if(p > 1)
    {
        MPI_Recv(&node, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(&lExponent, 1, MPI_LONG, node, 0, MPI_COMM_WORLD, &status);
        mpf_set_d(rExponent, pow(10.0, (double)lExponent));

        MPI_Recv(&length, 1, MPI_INT, node, 0, MPI_COMM_WORLD, &status);
        word = (char *)malloc(sizeof(char) * length + 10);

        MPI_Recv(word, length + 1, MPI_CHAR, node, 0, MPI_COMM_WORLD, &status);
        
        char su[40];
        sprintf(su, "@-%d", length); // update exponent
        strcat(word, su);

        mpf_set_str(tmp, word, 10);
        mpf_mul(tmp, tmp, rExponent);
        mpf_add(global_sum, global_sum, tmp);
    }

    elapsed_time += MPI_Wtime();

    if (!id) {
        mpf_add(global_sum, global_sum, sum);
        printf ("Execution time %8.6f\n", elapsed_time);
        fflush (stdout);
        gmp_printf ("The sum is %8.*Ff\n", d, global_sum);
        fflush (stdout);
    }

    MPI_Finalize();

    mpf_clear(global_sum);
    mpf_clear(sum);
    mpf_clear(x);
    mpf_clear(y);
    mpf_clear(rExponent);
    mpf_clear(tmp);
    return 0;
}
