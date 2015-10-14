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
        ClusterPtr point_space; // Pointer to initial Cluster that holds all Points
        ClusterPtr kClusterArray; // Pointer to array of ClusterPtrs

    public:
        // Member variables
        static const double SCORE_DIFF_THRESHOLD;

        // Constructors
        KMeans(int, std::string const &, std::string const &);
        ~KMeans();

        // Member functions
        double computeClusteringScore(); // implement Beta-CV criterion (coefficient variation)
    };
}

#endif //CLUSTERING_KMEANS_H