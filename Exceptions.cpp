// Programming Assignment 4 - KMeans Clustering

// Author:      Dylan Lang
// Date:        28 October 2015

// Exceptions implementation file

#include "Exceptions.h"

namespace Clustering
{
    /* Exceptions */

    // Dimensionality of Points do not match
    DimensionalityMismatchEx::DimensionalityMismatchEx(unsigned long int d, unsigned long int r)
    {
        __name = "EXCEPTION! Dimensionality Mismatch:";
        __currDim = d;
        __inputDim = r;
    }

    DimensionalityMismatchEx::~DimensionalityMismatchEx(){}

    std::ostream &operator <<(std::ostream &out, const DimensionalityMismatchEx &exc)
    {
        out << exc.getName() << " Comparison of Points with dimensionalities "
        << exc.getCurr() << " and " << exc.getInput() << " is undefined!";
        return out;
    }
    // ******************************************

    // Input index does not exist in the array
    OutOfBoundsEx::OutOfBoundsEx(unsigned long int c, unsigned int i)
    {
        __name = "EXCEPTION! Out-Of-Bounds:";
        __currSize = c;
        __inputIndex = i;
    }

    OutOfBoundsEx::~OutOfBoundsEx(){}

    std::ostream &operator <<(std::ostream &out, const OutOfBoundsEx &exc)
    {
        out << exc.getName() << " Attempt to return value from Index " << exc.getIndex()
        << " in an array of Size " << exc. getSize() << " is undefined!";
        return out;
    }

    // ******************************************

    // Cannot remove a Point from an empty Cluster
    RemoveFromEmptyEx::RemoveFromEmptyEx(unsigned int p, unsigned int c)
    {
        __name = "EXCEPTION! Remove from Empty Cluster:";
        __pointID = p;
        __clusterID = c;
    }

    RemoveFromEmptyEx::~RemoveFromEmptyEx(){}

    std::ostream &operator <<(std::ostream &out, const RemoveFromEmptyEx &exc)
    {
        out << exc.getName() << " Attempt to remove Point " << exc.getPID()
        << " from empty Cluster " << exc.getCID() << " is undefined!";
        return out;
    }
} // end namespace Clustering
