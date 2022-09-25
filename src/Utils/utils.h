#ifndef _utils_h
#define _utils_h

double getValue (double * bidimensional, int i, int j, int n_column);
void setValue(double * bidimensional, int i, int j, int n_column, double value);
int argmin(double * array, int select, int length, int n_column);
double * getRow(double * array, int i, int n_column);
void setRow(double * array, int i, int n_column, double * value);

#endif