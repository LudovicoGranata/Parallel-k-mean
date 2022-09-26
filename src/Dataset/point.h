#ifndef _point_h
#define _point_h

extern int n_points;
extern double *points;
void getPoints(int N, int cube);
double computeDistance(double * point1, double * point2, int dim);
int equal(double * point1, double * point2, int dim);

#endif