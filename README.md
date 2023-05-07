# Parallel-k-mean
![alt text](https://github.com/LudovicoGranata/Parallel-k-mean/blob/main/comparison.png)


In this project, I implemented a parallel version of the K-means algorithm using OpenMP. The goal was to enhance the performance of K-means by exploiting the parallelism of modern CPUs. Clustering is a crucial task in data analysis with various applications, including pattern recognition, image processing and data mining. K-means is a popular clustering algorithm due to its simplicity, effectiveness, and scalability; however it can be computationally expensive, especially for large datasets or high-dimensional spaces. Therefore, parallelizing K-means using OpenMP can significantly improve its performance and make it feasible to handle big data.

OpenMP is a widely used library for parallel programming in shared memory architectures. It provides a set of directives, pragmas, and libraries that enable to parallelize a program using multiple threads. OpenMP is portable, easy to use, and supported by most modern compilers.

To test the implementation, I used point cloud data, which is a collection of 3D points in space, commonly used in computer graphics, robotics, and computer vision. Specifically, I used scans of real objects from the Stanford 3D Scanning Repository, which offers a large collection of 3D object's models.
