// Programming Assignment 4 - KMeans Clustering

// Author:      Dylan Lang
// Date:        28 October 2015

// KMeans Class header file

// include guard
#ifndef CLUSTERING_KMEANS_H
#define CLUSTERING_KMEANS_H

#include <cfloat> // For DBL_MAX

#include "Cluster.h"

/* NON-TEMPLATE KMEANS CLASS */
/* namespace wrap */
namespace Clustering
{
    class KMeans
    {
    private:
        unsigned long int       __k;
        Cluster*                __point_space; // Pointer to initial Cluster that holds all Points
        std::vector<Cluster>    __kClusterArray;

    public:
        /* Member variables */
        static const double SCORE_DIFF_THRESHOLD;

        /* Constructors */
        KMeans(unsigned long int numClusters, unsigned long int numDims); // Default
        ~KMeans(); // Destructor

        /* Member functions */
        // TODO: readFromFile function
        // TODO: writeToFile function
        // TODO: performClustering function
        // implement Beta-CV criterion (coefficient variation)
        double computeClusteringScore(std::vector<Cluster>&, const std::unordered_map<Key, double, KeyHash, KeyEqual>&);
    };
} // end Clustering namespace

#endif //CLUSTERING_KMEANS_H



/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/



//#include "Exceptions.h"

/* TEMPLATE KMEANS CLASS */
/* namespace wrap */
