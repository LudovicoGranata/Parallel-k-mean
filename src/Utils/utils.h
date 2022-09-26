#ifndef _utils_h
#define _utils_h

double getValue (double * bidimensional, int i, int j, int n_column);
void setValue(double ** bidimensional, int i, int j, int n_column, double value);
int argmin(double * array, int select, int length);
double * getRow(double * array, int i, int n_column);
void setRow(double ** array, int i, int n_column, double * value);
int random_int (int min, int max);
double random_double (double min, double max);

#endif