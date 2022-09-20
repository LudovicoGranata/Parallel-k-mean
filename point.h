#ifndef _point_h
#define _point_h

typedef struct point {
    double x;
    double y;
    double z;
} Point;


Point * getPoints(int *n_points, int cube);
double computeDistance(Point point1, Point point2);
Point computeCentroid(Point * points, int * cluster, int n_points, int k);
int equal(Point point1, Point point2);

#endif