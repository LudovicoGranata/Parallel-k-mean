#include <stdio.h>
#include "./Phases/lib.h"
#include "./Dataset/point.h"
#include <omp.h>
#include <stdlib.h>
#include <math.h>
#include "./Utils/utils.h"

int main(int argc, char *argv[])
{
  const int DIM = 3;
  const int N = 500000;
  const int K = 4;
  int dataCube = 0;
  int finish = 0;


  // get datapoints
  getPoints(N, dataCube);

  //variables
  int * cluster = malloc(sizeof(int)* n_points);
  double * distances = malloc (sizeof(double) * n_points * K);
  int clusterDistribution[K];
  double * centroids = malloc (sizeof(double)* K * DIM);
  // double centroids[K][DIM];
  double clusterSum[K][DIM+1];
  double tstart, tstop;
  double t1start,t1stop,t2start,t2stop;
  int i,j,p,k;


  // start time
  tstart = omp_get_wtime();

// step 1: randomly choose k points among data point
  #pragma omp parallel for
  for (i = 0; i < K; i++){
    // double * row = getRow(points,random_int(0,n_points), DIM);
    setRow(centroids, i, DIM, getRow(points,random_int(0,n_points), DIM));
  }



  while (finish == 0) {

    // step 2: assign each data point to the nearest centroid
    #pragma omp parallel
    {


    // #pragma omp single
    // {
    // t1start = omp_get_wtime();
    // }

      #pragma omp for private(j)
      for (i = 0; i < n_points; i++)
      {
        for (j = 0; j < K; j++)
          // distances[i][j] = computeDistance(points[i], centroids[j], DIM); //TODO try to put the formula directly here
          setValue(distances, i,j, DIM, sqrt(pow( getValue(points,i,0,DIM)- getValue(centroids,j,0,DIM),2) + pow(getValue(points,i,1,DIM)- getValue(centroids,j,1,DIM), 2) + pow(getValue(points,i,2,DIM)- getValue(centroids,j,2,DIM), 2)));
      cluster[i] = argmin(distances, i, K, DIM);
      }
      
      // #pragma omp single
      //     {
      // t1stop = omp_get_wtime();
      //   }

      // step 3: compute the center of each cluster, this will be the new centroids
      #pragma omp single
      finish = 1;



      #pragma omp for collapse(2)
      for (i=0; i<K; i++){
        for (j=0; j<DIM+1; j++)
        clusterSum[i][j] = 0;
        }


      #pragma omp for reduction(+:clusterSum) private(i)
      for (p=0; p<n_points; p++ ){
        for (i=0; i<DIM; i++)
          clusterSum[cluster[p]][i] += getValue(points,p,i,DIM);
        clusterSum[cluster[p]][DIM]++;
      }

      #pragma omp for collapse(2)
      for (i=0; i<K; i++){
        for (k=0;k<DIM; k++)
          clusterSum[i][k] = clusterSum[i][k]/clusterSum[i][DIM];
      }
      // #pragma omp master
      //     {
      // t2start = omp_get_wtime();
      //   }

      #pragma omp for
      for (i=0; i<K; i++){
        if (equal(clusterSum[i], getRow(centroids,i,DIM), DIM) == 1)
          finish = 0;
        setRow(centroids, i, DIM, clusterSum[i]);
      }


      //     #pragma omp single
      //     {
      // t2stop = omp_get_wtime();
      //   }
    }
  }

    tstop = omp_get_wtime();
    printf("Elapsed time %f\n", tstop - tstart);
    // printf("Elapsed time 1 part %f\n", t1stop - t1start);
    // printf("Elapsed time 2 part %f\n", t2stop - t2start);


    // showResult(cluster, n_points, K, argc, argv, dataCube);
    free(points);
    free(distances);
    free(cluster);
    return 0;
}