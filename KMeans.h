// Programming Assignment 3 - KMeans Clustering

// Author:      Dylan Lang
// Date:        6 October 2015

// KMeans Class header file

// include guard
#ifndef CLUSTERING_KMEANS_H
#define CLUSTERING_KMEANS_H

#include "Cluster.h"

namespace Clustering
{
    typedef Cluster *ClusterPtr;

    class KMeans
    {
    private:
        int k;
        ClusterPtr point_space; // Pointer to initial Cluster that holds all Points
        ClusterPtr *kClusterArray; // Pointer to array of ClusterPtrs

    public:
        // Member variables
        static const double SCORE_DIFF_THRESHOLD;

        // Constructors
        KMeans(int numDims, int numClusters, std::string const &inputFile, std::string const &outputFile);
        ~KMeans();

        // Member functions
        double computeClusteringScore(ClusterPtr *); // implement Beta-CV criterion (coefficient variation)
    };
}

#endif //CLUSTERING_KMEANS_H