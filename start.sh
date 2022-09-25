cd src
gcc -fopenmp ./main.c ./Dataset/point.c ./Utils/utils.c ./Phases/lib.c ./Dataset/rply.c ./Visualization/visualization.c -o main -Wall -lm -lGL -lGLU -lglut 
OMP_NUM_THREADS=1 ./main 
OMP_NUM_THREADS=2 ./main 
OMP_NUM_THREADS=3 ./main 
OMP_NUM_THREADS=4 ./main 
OMP_NUM_THREADS=5 ./main 
OMP_NUM_THREADS=6 ./main 
OMP_NUM_THREADS=7 ./main 
OMP_NUM_THREADS=8 ./main 

