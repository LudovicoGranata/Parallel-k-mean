#include "point.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../Phases/lib.h"
#include "omp.h"
#include "rply.h"


double (*points) [3];
int n_points;
int index = 0;

static int vertex_xyz(p_ply_argument argument)
{
    int xyz;
    ply_get_argument_user_data(argument, NULL, &xyz);
    double point_coord = ply_get_argument_value(argument);
    points[index][xyz] = point_coord;
    if (xyz == 2) index++;
    return 1;
}

void getPoints(int N, int cube)
{
    if (cube == 0)
    {
        n_points = N;
        points = malloc(sizeof(double[n_points][3]));
        if (points == NULL)
        {
            printf("problems with allocation of memory ");
        }
        for (int i = 0; i < n_points; i++)
        {
            for (int j=0;j<3; j++){
                points[i][j] = random_double(0,40);
            }
        }
    }
    else
    {

        long nvertices;
        p_ply ply = ply_open("./cad_models/happy.ply", NULL, 0, NULL);
        if (!ply_read_header(ply))
            return 1;
        nvertices = ply_set_read_cb(ply, "vertex", "x", NULL, NULL, 0);
        points = malloc(sizeof(double[nvertices][3]));
        ply_set_read_cb(ply, "vertex", "x", vertex_xyz, NULL, 0);
        ply_set_read_cb(ply, "vertex", "y", vertex_xyz, NULL, 1);
        ply_set_read_cb(ply, "vertex", "z", vertex_xyz, NULL, 2);
        if (!ply_read(ply))
            return 1;
        ply_close(ply);
        if (N<=nvertices)
            n_points = N;
        else n_points = nvertices;
        printf("total number of points:%d\t number of points requested:%d\n", nvertices, n_points);
        double (*points_reduced)[3] =  malloc(sizeof(double[n_points][3]));
        for (int i=0; i< n_points; i++){
           int random_point = random_int(0,nvertices);
            for (int j=0; j<3; j++){
                points_reduced[i][j] = points[random_point][j];
            }
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
    double delta = 0.0001;
    int result = 0;
    for (int i=0; i<dim; i++){
    if ((fabs(point1[i] - point2[i])) > delta) 
        result = 1;
    }
    return result;
}
