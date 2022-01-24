#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#define BLOCK_LOW(id,p,n)  ((id)*(n)/(p))
#define BLOCK_HIGH(id,p,n) (BLOCK_LOW((id)+1,p,n)-1)
#define BLOCK_SIZE(id,p,n) (BLOCK_HIGH(id,p,n)-BLOCK_LOW(id,p,n)+1)
#define BLOCK_OWNER(index,p,n) ((((p)*(index)+1)-1)/(n))
#define FOR(i, L, R) for(i = L; i < R; ++i)
const int N = 2000;
int dx[8] = {-1,-1,-1,0,0,1,1,1};
int dy[8] = {-1,0,1,1,-1,-1,0,1};


void generate(char a[N][N])
{
    int i,j;
    for(i = 0; i < N; ++i){
        for(j = 0; j < N; ++j){
            if(i==0|| i == N - 1 || j == 0 || j == N - 1)a[i][j] = ' ';
            else if(rand()%2) a[i][j] = ' ';
            else a[i][j] = '@';
        }
    }
}

int main(int argc, char **argv)
{
    int id, p;
    double elapsed_time;  /* Time to find, count solutions */
    MPI_Status   status;

    char arr[N][N];
    char **own;
    int i, j, k, x = atoi(argv[1]), y = atoi(argv[2]), xi;
    int row, offset, cnt, node;

    generate(arr);

    MPI_Init(&argc, &argv);
    MPI_Barrier (MPI_COMM_WORLD);
    
    /* Start timer */
    elapsed_time = - MPI_Wtime();

    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    row = BLOCK_SIZE(id,p,N);

    own = malloc(row * sizeof(char *));
    for(i = 0; i < row; ++i){
        own[i] = malloc(N * sizeof(char));
    }

    for(xi = 1; xi <= x; ++xi)
    {
        // calculate the xi-th generation
        FOR(i,0,row)
        {
            offset = i + BLOCK_LOW(id,p,N);
            FOR(j,1,N-1)
            {
                cnt = 0;
                FOR(k,0,8) if(arr[offset + dx[k]][j + dy[k]]=='@')++cnt;
                if(arr[offset][j] == ' ' && cnt == 3)
                    own[i][j] = '@';
                else if (arr[offset][j] == '@' && cnt != 2 && cnt != 3)
                    own[i][j] = ' ';
                else
                    own[i][j] = arr[offset][j];  
            } 
        }
        
        // fill back to arr
        FOR(i,0,row) 
        {
            offset = i + BLOCK_LOW(id,p,N);
            FOR(j,1,N-1) arr[offset][j] = own[i][j];
        }

        // even-odd commication
        if(id % 2 == 0 && id + 1 < p)
        {
            MPI_Send(arr[BLOCK_HIGH(id,p,N)],     N, MPI_CHAR, id + 1, 0, MPI_COMM_WORLD);
            MPI_Recv(arr[BLOCK_HIGH(id,p,N) + 1], N, MPI_CHAR, id + 1, 0, MPI_COMM_WORLD, &status);
        }
        else if(id % 2 == 1 && id - 1 >= 0)
        {
            MPI_Recv(arr[BLOCK_LOW(id,p,N) - 1],  N, MPI_CHAR, id - 1, 0, MPI_COMM_WORLD, &status);
            MPI_Send(arr[BLOCK_LOW(id,p,N)],      N, MPI_CHAR, id - 1, 0, MPI_COMM_WORLD);
        }

        // odd-even commication
        if(id % 2 == 1 && id + 1 < p)
        {
            MPI_Send(arr[BLOCK_HIGH(id,p,N)],     N, MPI_CHAR, id + 1, 0, MPI_COMM_WORLD);
            MPI_Recv(arr[BLOCK_HIGH(id,p,N) + 1], N, MPI_CHAR, id + 1, 0, MPI_COMM_WORLD, &status);
        }
        else if(id % 2 == 0 && id - 1 >= 0)
        {
            MPI_Recv(arr[BLOCK_LOW(id,p,N) - 1],  N, MPI_CHAR, id - 1, 0, MPI_COMM_WORLD, &status);
            MPI_Send(arr[BLOCK_LOW(id,p,N)],      N, MPI_CHAR, id - 1, 0, MPI_COMM_WORLD);
        }

        if(xi % y != 0 && xi != x) continue;

        if(id)
        {
            FOR(i, 0, BLOCK_SIZE(id,p,N)) 
            {
                offset = i + BLOCK_LOW(id,p,N);
                MPI_Send(&id, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
                MPI_Send(&offset, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
                MPI_Send(arr[offset], N, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
            }
        }
        else
        {
            FOR(i, 0, N - BLOCK_SIZE(id,p,N))
            {
                MPI_Recv(&node, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
                MPI_Recv(&offset, 1, MPI_INT, node, 0, MPI_COMM_WORLD, &status);
                MPI_Recv(arr[offset], N, MPI_CHAR, node, 0, MPI_COMM_WORLD, &status);
            }
            printf("The %d-th:\n", xi);
            FOR(i, 0, N)
            {
                FOR(j, 0, N)
                {
                    printf("%c", arr[i][j]);
                    fflush (stdout);
                }
                printf("\n");
                fflush (stdout);
            }
            printf("\n");
            fflush (stdout);
        }
    }

    elapsed_time += MPI_Wtime();

    if (!id) {
        printf ("Execution time %8.6f\n", elapsed_time);
        fflush (stdout);
    }

    MPI_Finalize();

    return 0;
}
