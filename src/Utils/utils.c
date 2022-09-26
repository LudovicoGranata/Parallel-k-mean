#include "utils.h"
#include <stdlib.h>
#include <stdio.h>


double getValue (double * bidimensional, int i, int j, int n_column){
    return bidimensional[i*n_column+j];
}

void setValue(double ** bidimensional, int i, int j, int n_column, double value){
    (*bidimensional)[i*n_column+j] = value;
}

int argmin(double * array, int select, int length){

    double min = getValue (array, select, 0, length) ;
    int min_index = 0;
    for (int i=1; i<length; i++){
        if (getValue(array, select,i, length)< min){
            min = getValue(array, select,i, length);
            min_index = i;
        }
    }
    return min_index;
}

double * getRow(double * array, int i, int n_column){
    double * result = malloc(sizeof(double)*n_column);
    for (int j=0; j<n_column; j++){
        result[j] = getValue(array, i,j, n_column);
    }
    return result;
}

void setRow(double ** array, int i, int n_column, double * value){
    for (int j=0; j<n_column; j++){
        setValue(array, i,j, n_column, value[j]);
    }
}


int random_int (int min, int max){
    return min + (rand()) % (max+1 - min);
}

double random_double (double min, double max){
    double range = (max-min);
    double div = RAND_MAX / range;
    return min + (rand() / div);
}