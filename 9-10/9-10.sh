#!/bin/sh 
#PBS -P ACD110146
#PBS -N hello
#PBS -q ctest
#PBS -l select=1:ncpus=2:mpiprocs=8
#PBS -l place=scatter
#PBS -l walltime=00:01:00
#PBS -j n
module purge 
module load intel/2018_u1

cd $PBS_O_WORKDIR
echo $PBS_O_WORKDIR

mpicc -o Test -lm 9-10.c

for i in $(seq 1 8)
do
    echo ""
    echo "run with $i process"
    echo ""
    mpirun -np $i ./Test
done