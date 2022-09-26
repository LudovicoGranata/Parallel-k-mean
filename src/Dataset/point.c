#include "point.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "omp.h"
#include "rply.h"
#include "../Utils/utils.h"


double *points;
int n_points;
int myIndex = 0;

static int vertex_xyz(p_ply_argument argument)
{
    long int xyz;
    ply_get_argument_user_data(argument, NULL, &xyz);
    double point_coord = ply_get_argument_value(argument);
    setValue(&points, myIndex, xyz, 3, point_coord);
    // points[index][xyz] = point_coord;
    if (xyz == 2) myIndex++;
    return 1;
}

void getPoints(int N, int cube)
{
    if (cube == 0)
    {
        n_points = N;
        points = malloc(sizeof(double) *n_points*3);
        if (points == NULL)
        {
            printf("problems with allocation of memory ");
        }
        for (int i = 0; i < n_points; i++)
        {
            for (int j=0;j<3; j++){
                setValue(&points,i,j,3, random_double(0,40));
            }
        }
    }
    else
    {

        long nvertices;
        p_ply ply = ply_open("./cad_models/happy.ply", NULL, 0, NULL);
        if (!ply_read_header(ply))
            return;
        nvertices = ply_set_read_cb(ply, "vertex", "x", NULL, NULL, 0);
        points = malloc(sizeof(double) * nvertices * 3);
        ply_set_read_cb(ply, "vertex", "x", vertex_xyz, NULL, 0);
        ply_set_read_cb(ply, "vertex", "y", vertex_xyz, NULL, 1);
        ply_set_read_cb(ply, "vertex", "z", vertex_xyz, NULL, 2);
        if (!ply_read(ply))
            return ;
        ply_close(ply);
        if (N<=nvertices)
            n_points = N;
        else n_points = nvertices;
        printf("total number of points:%ld\t number of points requested:%d\n", nvertices, n_points);
        double *points_reduced =  malloc(sizeof(double) * n_points*3);
        for (int i=0; i< n_points; i++){
            setRow(&points_reduced, i, 3, getRow(points,random_int(0,nvertices), 3));
        }
        points = points_reduced;
    }
}

double computeDistance(double * point1, double * point2, int dim)
{
    // l2 distance

    double sum = 0.0;
    for (int i = 0; i < dim; i++)
        sum += pow(point1[i] - point2[i], 2);
    
    return sqrt(sum);
}

int equal(double * point1, double * point2, int dim)
{
    double delta = 0.01;
    int result = 0;
    for (int i=0; i<dim; i++){
    if ((fabs(point1[i] - point2[i])) > delta) 
        result = 1;
    }
    return result;
}
