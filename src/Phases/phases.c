#include "phases.h"
#include "../Dataset/point.h"
#include <omp.h>
#include "../Utils/utils.h"

void phase1(double ** centroids, double * points, int K, int DIM){
#pragma omp parallel for
  for (int i = 0; i < K; i++){
    double * prova = getRow(points, random_int(0, n_points), DIM);
    double prova0 = prova[0];
    setRow(centroids, i, DIM, getRow(points, random_int(0, n_points), DIM));
  }
}
