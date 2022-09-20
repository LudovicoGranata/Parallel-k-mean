#include <stdio.h>
#include "lib.h"
#include "point.h"
#include <omp.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  const int K = 5;
  int dataCube = 1;
  int finish = 0;
  Point *points;
  int n_points = 0;
  // get datapoints
  points = getPoints(&n_points, dataCube);
  int * cluster = malloc(sizeof(int)* n_points);
  double (*distances)[K] = malloc(sizeof(double[n_points][K]));
  Point centroids[K];


  double tstart, tstop;
  int i,j;
  // double * distances = malloc(sizeof (double) * n_points * K);
  // start
  tstart = omp_get_wtime();
// step 1: randomly choose k points among data point
printf("thread n%d \n", omp_get_thread_num());

#pragma omp parallel for
  for (i = 0; i < K; i++)
  {
    centroids[i] = points[random_int(0,n_points)];
  }

  while (finish == 0) {
    // step 2: assign each data point to the nearest centroid
    #pragma omp parallel
    #pragma omp for collapse(2)
    for (i = 0; i < n_points; i++)
    {
      for (j = 0; j < K; j++)
      {
        distances[i][j] = computeDistance(points[i], centroids[j]);
      }
    }

    #pragma omp for
    for (i = 0; i < n_points; i++)
    {
      cluster[i] = argmin(distances[i], K);
    }

    // step 3: compute the center of each cluster, this will be the new centroids
    #pragma omp single
    finish = 1;
    
    #pragma omp for
    for (i = 0; i < K; i++)
    {
      Point old_centroid = centroids[i];
      centroids[i] = computeCentroid(points, cluster, n_points, i);
      if (equal(old_centroid, centroids[i]) == 1)
        finish = 0;
    }
  }
  
  tstop = omp_get_wtime();
  printf("Elapsed time %f\n", tstop - tstart);


  showResult(points, cluster, n_points, K, argc, argv, dataCube);
  free(points);
  free(distances);
  free(cluster);
  return 0;
}