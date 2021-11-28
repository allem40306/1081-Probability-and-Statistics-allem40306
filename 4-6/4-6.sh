#!/bin/sh 
module load intel/2018_u1
mpicc -o Test -lm 4-6.c

for i in $(seq 1 8)
do
    echo ""
    echo "run with $i process"
    echo ""
    mpirun -np $i ./Test
done