gcc -fopenmp ./src/main.c ./src/Dataset/point.c ./src/Phases/lib.c ./src/Dataset/rply.c ./src/Visualization/visualization.c -o main -Wall -lm -lGL -lGLU -lglut 
OMP_NUM_THREADS=1 ./main 
OMP_NUM_THREADS=4 ./main 
OMP_NUM_THREADS=8 ./main 
