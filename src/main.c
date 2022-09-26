#include <stdio.h>
#include "./Dataset/point.h"
#include <omp.h>
#include <stdlib.h>
#include <math.h>
#include "./Utils/utils.h"
#include "./Visualization/visualization.h"

int main(int argc, char *argv[])
{
  // omp_set_num_threads(8);
  if (argc != 3) {
    printf("not enough arguments\n");
    return 1;
  }
  const int DIM = 3;
  const int N = atoi(argv[1]);
  const int K = atoi(argv[2]);
  // const int N = 500000;
  // const int K = 4;
  int dataCube = 1;
  int finish = 0;
  int schedule = 1;
  int num_threads = 0;
  srand(49);

  // get datapoints
  getPoints(N, dataCube);

  // variables
  int *cluster = malloc(sizeof(int) * n_points);
  double *distances = malloc(sizeof(double) * n_points * K);
  double *centroids = malloc(sizeof(double) * K * DIM);
  double clusterSum[K][DIM + 1];
  double tstart, tstop;
  int i, j, p, k;

  int prova1;

  // start time
  tstart = omp_get_wtime();

  //step 1: randomly choose k points among data point
#pragma omp parallel for schedule(static,schedule)
  for (i = 0; i < K; i++){
    setRow(&centroids, i, DIM, getRow(points, random_int(0, n_points), DIM));
  }
// phase1(&centroids, points, K, DIM);


  while (finish == 0)
  {
    // step 2: assign each data point to the nearest centroid
#pragma omp parallel
    {

#pragma omp for private(j) schedule(static,schedule)
      for (i = 0; i < n_points; i++)
      {
        for (j = 0; j < K; j++){
          // distances[i][j] = computeDistance(points[i], centroids[j], DIM); //TODO try to put the formula directly here
          // setValue(&distances, i, j, DIM, sqrt(pow(getValue(points, i, 0, DIM) - getValue(centroids, j, 0, DIM), 2) + pow(getValue(points, i, 1, DIM) - getValue(centroids, j, 1, DIM), 2) + pow(getValue(points, i, 2, DIM) - getValue(centroids, j, 2, DIM), 2)));
          double distance = sqrt(pow(getValue(points, i, 0, DIM) - getValue(centroids, j, 0, DIM), 2) + pow(getValue(points, i, 1, DIM) - getValue(centroids, j, 1, DIM), 2) + pow(getValue(points, i, 2, DIM) - getValue(centroids, j, 2, DIM), 2));
          setValue(&distances, i, j, K, distance);
        
        }
        cluster[i] = argmin(distances, i, K);
      }

// step 3: compute the center of each cluster, this will be the new centroids
#pragma omp single
      finish = 1;

#pragma omp for collapse(2) schedule(static,schedule)
      for (i = 0; i < K; i++)
      {
        for (j = 0; j <= DIM + 1; j++)
          clusterSum[i][j] = 0;
      }

#pragma omp for reduction(+:clusterSum) private(i) schedule(static,schedule)
      for (p = 0; p < n_points; p++)
      {
        for (i = 0; i < DIM; i++){
          clusterSum[cluster[p]][i] += getValue(points, p, i, DIM);
        }
        clusterSum[cluster[p]][DIM]++;
      }

#pragma omp for collapse(2) schedule(static,schedule)
      for (i = 0; i < K; i++)
      {
        for (k = 0; k < DIM; k++)
          clusterSum[i][k] = clusterSum[i][k] / clusterSum[i][DIM];
      }

#pragma omp for schedule(static,schedule)
      for (i = 0; i < K; i++)
      {
        if (equal(clusterSum[i], getRow(centroids, i, DIM), DIM) == 1)
          finish = 0;
        setRow(&centroids, i, DIM, clusterSum[i]);
      }
    }
  }

  tstop = omp_get_wtime();
  printf("Elapsed time %f\n", tstop - tstart); 
  FILE *fp;
  int fileExists = 1;
  char filename[20] = "output.csv";
  if ( fp = fopen(filename,"r")!=NULL){
    fileExists = 0;
    close(fp);
  }
  
  fp = fopen ("output.csv", "a");
  if (fileExists)
    fprintf(fp, "n_thread, n_points, n_cluster, time\n");
  
  fprintf(fp, "%d,%d,%d,%f\n", num_threads, n_points, K, (tstop-tstart));

  // showResult(cluster, n_points, K, argc, argv, dataCube);
  free(points);
  free(distances);
  free(cluster);
  free(centroids);
  return 0;
}