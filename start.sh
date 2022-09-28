#!/bin/bash

cd src
gcc -fopenmp ./main.c ./Dataset/point.c ./Utils/utils.c ./Phases/phases.c ./Dataset/rply.c ./Visualization/visualization.c -o main -Wall -lm -lGL -lGLU -lglut 

max_strong_scaling=11
npoint=500000
k=100
num_threads=1
for i in `seq 1 $max_strong_scaling`
do
    OMP_NUM_THREADS=$num_threads ./main $npoint $k 
    num_threads=$(($num_threads * 2))
done

max_weak_scaling=5
npointValues=(10000 14142 20000 28284 40000 56569)
kValues=(10 14 20 28 40 57)
num_threads=1
npoint=100
k=1
for i in `seq 1 $max_weak_scaling`
do 
    npoint=${npointValues[i-1]}
    k=${kValues[i-1]}
    OMP_NUM_THREADS=$num_threads ./main $npoint $k
    num_threads=$(($num_threads * 2))

done



