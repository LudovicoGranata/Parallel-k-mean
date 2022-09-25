#include "lib.h"
#include <stdio.h>
#include <stdlib.h>

// int seed = 49;
// srand(seed);

int random_int (int min, int max){
    return min + (rand()) % (max+1 - min);
}

double random_double (double min, double max){
    double range = (max-min);
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

// int argmin(double * array, int length){
//     double min = array [0];
//     int min_index = 0;
//     for (int i=1; i<length; i++){
//         if (array[i]< min){
//             min = array[i];
//             min_index = i;
//         }
//     }
//     return min_index;
// }