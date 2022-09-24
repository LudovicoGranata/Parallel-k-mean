#ifndef _point_h
#define _point_h

typedef struct point {
    double x;
    double y;
    double z;
} Point;

int n_points;
double (*points)[3];
void getPoints(int N, int cube);
double computeDistance(double * point1, double * point2, int dim);
Point computeCentroid(Point * points, int * cluster, int n_points, int k);
int equal(double * point1, double * point2, int dim);

#endif