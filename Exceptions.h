// Programming Assignment 4 - KMeans Clustering

// Author:      Dylan Lang
// Date:        28 October 2015

// Exceptions header file

#ifndef CLUSTERING_EXCEPTIONS_H
#define CLUSTERING_EXCEPTIONS_H

#include "KMeans.h"

namespace Clustering
{
    /* Exceptions for class Point */
    class PointDimensionalityMismatchEx
    {
    private:
        std::string name;

    public:
        PointDimensionalityMismatchEx();
        ~PointDimensionalityMismatchEx();

    };

    class PointOutOfBoundsEx
    {
    private:
        std::string name;

    public:
        PointOutOfBoundsEx();
        ~PointOutOfBoundsEx();
    };
    /******************************************************/

    /* Exceptions for class Cluster */
    class ClusterRemoveFromEmptyEx
    {
    private:
        std::string name;

    public:
        ClusterRemoveFromEmptyEx();
        ~ClusterRemoveFromEmptyEx();
    };

    class ClusterOutOfBoundsEx
    {
    private:
        std::string name;

    public:
        ClusterOutOfBoundsEx();
        ~ClusterOutOfBoundsEx();
    };

} // end namespace Clustering

#endif //CLUSTERING_EXCEPTIONS_H
