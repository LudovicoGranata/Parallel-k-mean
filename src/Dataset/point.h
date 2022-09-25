#ifndef _point_h
#define _point_h

typedef struct point {
    double x;
    double y;
    double z;
} Point;

extern int n_points;
extern double *points;
void getPoints(int N, int cube);
double computeDistance(double * point1, double * point2, int dim);
Point computeCentroid(Point * points, int * cluster, int n_points, int k);
int equal(double * point1, double * point2, int dim);

#endif