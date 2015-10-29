// Programming Assignment 4 - KMeans Clustering

// Author:      Dylan Lang
// Date:        28 October 2015

// Exceptions implementation file

#include "Exceptions.h"

namespace Clustering
{
    /* Point Class Exceptions */
    PointDimensionalityMismatchEx::PointDimensionalityMismatchEx()
    {
        name = "PointDimensionalityMismatchEx";
    }

    PointDimensionalityMismatchEx::~PointDimensionalityMismatchEx()
    {

    }

    PointOutOfBoundsEx::PointOutOfBoundsEx()
    {
        name = "PointOutOfBoundsEx";
    }

    PointOutOfBoundsEx::~PointOutOfBoundsEx()
    {

    }

    /* Cluster Class Exceptions */
    ClusterRemoveFromEmptyEx::ClusterRemoveFromEmptyEx()
    {
        name = "ClusterRemoveFromEmptyEx";
    }

    ClusterRemoveFromEmptyEx::~ClusterRemoveFromEmptyEx()
    {

    }

    ClusterOutOfBoundsEx::ClusterOutOfBoundsEx()
    {
        name = "ClusterOutOfBoundsEx";
    }

    ClusterOutOfBoundsEx::~ClusterOutOfBoundsEx()
    {

    }
} // end namespace Clustering
