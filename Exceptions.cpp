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
        << " in a dimensionality of size " << exc.getSize() << " is undefined!";
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
        out << exc.getName() << " Attempt to alter/remove Point " << exc.getPID()
        << " in empty Cluster " << exc.getCID() << " is undefined!";
        return out;
    }

    // ******************************************

    // Cannot divide by zero
    DivideByZeroEx::DivideByZeroEx(unsigned int p)
    {
        __name = "EXCEPTION! Divide by zero:";
        __pointID = p;
    }

    DivideByZeroEx::~DivideByZeroEx() {}

    std::ostream &operator <<(std::ostream &out, const DivideByZeroEx &exc)
    {
        out << exc.getName() << " Attempt to divide Point " << exc.getPID() << " by zero is undefined!";
        return out;
    }

    // ******************************************

    // Point already exists in Cluster
    PointAlreadyExistsEx::PointAlreadyExistsEx(const Point &p)
    {
        __name = "EXCEPTION! Point already exists:";
        __point = p;
    }

    PointAlreadyExistsEx::~PointAlreadyExistsEx() {}

    std::ostream &operator <<(std::ostream &out, const PointAlreadyExistsEx &exc)
    {
        out << exc.getName() << " Point " << exc.getPoint() << " already exists in Cluster!";
        return out;
    }
} // end namespace Clustering
