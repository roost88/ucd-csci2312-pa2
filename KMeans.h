// Programming Assignment 4 - KMeans Clustering

// Author:      Dylan Lang
// Date:        28 October 2015

// KMeans Class header file

// include guard
#ifndef CLUSTERING_KMEANS_H
#define CLUSTERING_KMEANS_H

#include "Cluster.h"

namespace Clustering
{
    class KMeans
    {
    private:
        // TODO: add __ before each variable
        int k;
        ClusterPtr point_space; // Pointer to initial Cluster that holds all Points
        // TODO: reimplement kClusterArray as an std::vector<Cluster>
        ClusterPtr *kClusterArray; // Pointer to array of ClusterPtrs

    public:
        // Member variables
        static const double SCORE_DIFF_THRESHOLD;

        // Constructors
        KMeans(unsigned long int numDims, int numClusters, std::string const &inputFile, std::string const &outputFile);
        ~KMeans();

        // Member functions
        double computeClusteringScore(ClusterPtr *); // implement Beta-CV criterion (coefficient variation)
    };
}

#endif //CLUSTERING_KMEANS_H