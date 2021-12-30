#!/bin/sh
#PBS -P ACD110146
#PBS -N hello
#PBS -q ctest
#PBS -l select=2:ncpus=1:mpiprocs=1
#PBS -l place=scatter
#PBS -l walltime=00:30:00
#PBS -j n
module purge
module load intel/2018_u1

cd $PBS_O_WORKDIR
echo $PBS_O_WORKDIR

mpicc -o Test -lm 6-8.c
date
mpirun -np 2 ./Test