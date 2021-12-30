#!/bin/sh 
#PBS -P ACD110146
#PBS -N hello
#PBS -q ctest
#PBS -l select=1:ncpus=8:mpiprocs=8
#PBS -l place=scatter
#PBS -l walltime=00:30:00
#PBS -j n
module load intel/2018_u1
mpicc -o Test -lm -lgmp 6-13.c

cd $PBS_O_WORKDIR
echo $PBS_O_WORKDIR

for i in $(seq 1 8)
do
    echo ""
    echo "run with $i process"
    echo ""
    mpirun -np $i ./Test 100 25
done