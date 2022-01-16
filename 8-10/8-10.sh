#!/bin/sh 
#PBS -P ACD110146
#PBS -N hello
#PBS -q ctest
#PBS -l select=1:ncpus=8:mpiprocs=8
#PBS -l place=scatter
#PBS -l walltime=00:30:00
#PBS -j n

gcc -o Test gen.c
./Test 10000 10000 a.txt
./Test 10000 1 b.txt

module load intel/2018_u1
mpicc -o Test -lm -lgmp 8-10.c MyMPI.c

cd $PBS_O_WORKDIR
echo $PBS_O_WORKDIR

for i in $(seq 1 8)
do
    echo ""
    echo "run with $i process"
    echo ""
    mpirun -np $i ./Test ./a.txt ./b.txt
done