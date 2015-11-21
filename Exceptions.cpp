// Programming Assignment 4 - KMeans Clustering

// Author:      Dylan Lang
// Date:        28 October 2015 - 21 November 2015

// Exceptions implementation file

#include "Exceptions.h"

namespace Clustering
{
    /* Exceptions */

    // Dimensionality of Points do not match
    DimensionalityMismatchEx::DimensionalityMismatchEx(int d, int r)
    {
        __name = "EXCEPTION! Dimensionality Mismatch:";
        __currDim = d;
        __inputDim = r;
    }

    std::ostream &operator <<(std::ostream &out, const DimensionalityMismatchEx &exc)
    {
        out << exc.getName() << " Comparison of Points with dimensionalities "
        << exc.getCurr() << " and " << exc.getInput() << " is undefined!";
        return out;
    }
    /************************************************************/

    // Input index does not exist in the array
    OutOfBoundsEx::OutOfBoundsEx(int c, unsigned int i)
    {
        __name = "EXCEPTION! Out-Of-Bounds:";
        __currSize = c;
        __inputIndex = i;
    }

    std::ostream &operator <<(std::ostream &out, const OutOfBoundsEx &exc)
    {
        out << exc.getName() << " Attempt to return value from Index " << exc.getIndex()
        << " in a dimensionality of size " << exc.getSize() << " is undefined!";
        return out;
    }

    /************************************************************/

    // Cannot remove a Point from an empty Cluster
    RemoveFromEmptyEx::RemoveFromEmptyEx(int p, int c)
    {
        __name = "EXCEPTION! Remove from Empty Cluster:";
        __PID = p;
        __CID = c;
    }

    std::ostream &operator <<(std::ostream &out, const RemoveFromEmptyEx &exc)
    {
        out << exc.getName() << " Attempt to alter/remove Point " << exc.getPID()
        << " in empty Cluster " << exc.getCID() << " is undefined!";
        return out;
    }

    /************************************************************/

    // Cannot divide by zero
    DivideByZeroEx::DivideByZeroEx()
    {
        __name = "EXCEPTION! Divide by zero:";
    }

    std::ostream &operator <<(std::ostream &out, const DivideByZeroEx &exc)
    {
        out << exc.getName() << " Attempt to divide by zero is undefined!";
        return out;
    }

    /************************************************************/

    // Point already exists in Cluster
    PointAlreadyExistsEx::PointAlreadyExistsEx(int p)
    {
        __name = "EXCEPTION! Point already exists:";
        __PID = p;
    }

    std::ostream &operator <<(std::ostream &out, const PointAlreadyExistsEx &exc)
    {
        out << exc.getName() << " Point " << exc.getPID() << " already exists in Cluster!";
        return out;
    }

    /************************************************************/

    // Point does not exist in Cluster
    DoesNotExistEx::DoesNotExistEx(int p, int c)
    {
        __name = "EXCEPTION! Point does not exist:";
        __PID = p;
        __CID = c;
    }

    std::ostream &operator <<(std::ostream &out, const DoesNotExistEx &exc)
    {
        out << exc.getName() << " Point " << exc.getPID() << " does not exist in Cluster " << exc.getCID() << "!";
        return out;
    }
} // end namespace Clustering
