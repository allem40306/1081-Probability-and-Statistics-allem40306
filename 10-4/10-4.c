/*
 *   C program that uses the Monte Carlo method to solve the neutron
 *   transport problem posed in Section 10.5.1.
 *
 *   Programmed by Michael J. Quinn
 */

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define BLOCK_LOW(id,p,n)  ((id)*(n)/(p))
#define BLOCK_HIGH(id,p,n) (BLOCK_LOW((id)+1,p,n)-1)
#define BLOCK_SIZE(id,p,n) (BLOCK_HIGH(id,p,n)-BLOCK_LOW(id,p,n)+1)
#define BLOCK_OWNER(index,p,n) (((p)*(index)+1)-1)/(n))
#define C  2.0
#define CS 1.5
#define CC (C - CS)
#define PI 3.1415926

int main (int argc, char *argv[])
{
    int id, p;
    double elapsed_time;  /* Time to find, count solutions */
    long int i, its = 1e9;
    double d = 0.3;
    double s = 2;
    unsigned short x1[3], y1[3], z1[3];
    double rand_x, rand_y, rand_z;
    double distance;
    double cube_volume = pow(s,3);
    double actual_cylindrical_hole_volume = (pow(d/2.0,2))*PI*(sqrt(3.0)*s);
    int global_outside_count = 0;
    int outside_count;

    for(i = 0; i < 3; i++){
        x1[i] = i;
        y1[i] = i+1;
        z1[i] = i+2;
    }

    MPI_Init(&argc, &argv);
    MPI_Barrier (MPI_COMM_WORLD);

    /* Start timer */
    elapsed_time = - MPI_Wtime();
    outside_count = 0;

    MPI_Comm_size(MPI_COMM_WORLD, &p);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);

    for (i = 1; i <= BLOCK_SIZE(id,p,its); i++) {
        rand_x = s*erand48(x1);
        rand_y = s*erand48(y1);
        rand_z = s*erand48(z1);
//        printf("x = %f, y = %f, z = %f\n", rand_x, rand_y, rand_z);
        distance = sin( acos( (rand_x+rand_y+rand_z) / ( sqrt(3) * sqrt(rand_x*rand_x + rand_y*rand_y + rand_z*rand_z) ) ) ) * sqrt(rand_x*rand_x + rand_y*rand_y + rand_z*rand_z);
        if(distance > d/2) outside_count++;

    }
    
    MPI_Reduce (&outside_count, &global_outside_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD); 

    elapsed_time += MPI_Wtime();

    if (!id) {
        // printf("%d\n", global_outside_count);
        printf("the volume of the portion of the cube that remains is %10.6f\n", ( (double) (global_outside_count)/(its)) * cube_volume);
        printf("actual value: %10.6f\n", cube_volume - actual_cylindrical_hole_volume);
        printf ("Execution time %8.6f\n", elapsed_time);
        fflush (stdout);
    }

    MPI_Finalize();
    return 0;

}
