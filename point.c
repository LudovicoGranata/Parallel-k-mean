#include "point.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lib.h"
#include "omp.h"
#include "rply.h"

const int N = 30000;
Point *points;
int index = 0;

static int vertex_xyz(p_ply_argument argument)
{
    int xyz;
    ply_get_argument_user_data(argument, NULL, &xyz);
    double point_coord = ply_get_argument_value(argument);

    if (xyz == 0)
    {
        points[index].x = point_coord;
    }
    if (xyz == 1)
    {
        points[index].y = point_coord;
    }
    if (xyz == 2)
    {
        (points[index]).z = point_coord;
        index++;
    }
    return 1;
}

Point *getPoints(int *n_points, int cube)
{
    if (cube == 0)
    {
        *n_points = N;
        Point *points = malloc(*n_points * sizeof(Point));
        if (points == NULL)
        {
            printf("problems with allocation of memory ");
        }
#pragma omp parallel for
        for (int i = 0; i < *n_points; i++)
        {
            Point p = {random_double(0, 40), random_double(0, 40), random_double(0, 40)};
            points[i] = p;
        }

        return points;
    }
    else
    {

        long nvertices;
        p_ply ply = ply_open("bun_zipper.ply", NULL, 0, NULL);
        if (!ply_read_header(ply))
            return 1;
        nvertices = ply_set_read_cb(ply, "vertex", "x", NULL, NULL, 0);
        points = malloc(nvertices * sizeof(Point));
        ply_set_read_cb(ply, "vertex", "x", vertex_xyz, NULL, 0);
        ply_set_read_cb(ply, "vertex", "y", vertex_xyz, NULL, 1);
        ply_set_read_cb(ply, "vertex", "z", vertex_xyz, NULL, 2);
        if (!ply_read(ply))
            return 1;
        ply_close(ply);
        if (N<=nvertices)
            *n_points = N;
        else *n_points = nvertices;
        Point * points_reduced =  malloc(*n_points * sizeof(Point));
        for (int i=0; i< *n_points; i++){
            points_reduced[i] = points[random_int(0, nvertices)];
        }
        free(points);
        return points_reduced;
    }
}

double computeDistance(Point point1, Point point2)
{
    // l2 distance

    double sum = 0.0;
    for (int i = 0; i < 3; i++)
    {
        if (i == 0)
            sum += pow(point1.x - point2.x, 2);
        if (i == 1)
            sum += pow(point1.y - point2.y, 2);
        if (i == 2)
            sum += pow(point1.z - point2.z, 2);
    }

    return sqrt(sum);
}

Point add(Point point1, Point point2)
{
    Point result;
    result.x = point1.x + point2.x;
    result.y = point1.y + point2.y;
    result.z = point1.z + point2.z;
    return result;
}

Point divPoint(Point point, int dividend)
{
    point.x = point.x / dividend;
    point.y = point.y / dividend;
    point.z = point.z / dividend;
    return point;
}

// TODO add parallel for with a custom reduction
Point computeCentroid(Point *points, int *cluster, int n_points, int k)
{
    double n_points_k = 0.0;
    Point newCentroid = {0.0, 0.0, 0.0};
    for (int i = 0; i < n_points; i++)
    {
        if (cluster[i] == k)
        {
            n_points_k++;
            newCentroid = add(newCentroid, points[i]);
        }
    }
    newCentroid = divPoint(newCentroid, n_points_k);
    return newCentroid;
}

int equal(Point point1, Point point2)
{
    double delta = 0.01;
    if (((fabs(point1.x - point2.x)) > delta) || ((fabs(point1.y - point2.y)) > delta) || ((fabs(point1.z - point2.z)) > delta))
        return 1;
    return 0;
}
