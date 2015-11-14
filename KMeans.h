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
        unsigned long int       __k;
        ClusterPtr              __point_space; // Pointer to initial Cluster that holds all Points
        std::vector<Cluster>    __kClusterArray;

    public:
        // Member variables
        static const double SCORE_DIFF_THRESHOLD;

        // Constructors
        KMeans(unsigned long int numDims, unsigned long int numClusters,
               std::string const &inputFile, std::string const &outputFile);
        ~KMeans();

        // Member functions
        // implement Beta-CV criterion (coefficient variation)
        double computeClusteringScore(std::vector<Cluster>&, const hashMap&);
    };
}

#endif //CLUSTERING_KMEANS_H