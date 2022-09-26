#!/bin/bash

cd src
gcc -fopenmp ./main.c ./Dataset/point.c ./Utils/utils.c ./Phases/phases.c ./Dataset/rply.c ./Visualization/visualization.c -o main -Wall -lm -lGL -lGLU -lglut 

max_strong_scaling=1
npoint=500000
k=100
for i in `seq 1 $max_strong_scaling`
do
    OMP_NUM_THREADS=$i ./main $npoint $k
done

max_weak_scaling=10
npoint=100
k=1
for i in `seq 1 $max_weak_scaling`
do 
    OMP_NUM_THREADS=$i ./main $npoint $k
    npoint=$(($npoint * 2))
    k=$(($k * 2))

    echo $npoint
done



