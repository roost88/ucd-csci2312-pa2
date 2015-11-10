// Programming Assignment 4 - KMeans Clustering

// Author:      Dylan Lang
// Date:        28 October 2015

// Exceptions header file

#ifndef CLUSTERING_EXCEPTIONS_H
#define CLUSTERING_EXCEPTIONS_H

#include "KMeans.h"

namespace Clustering
{
    /* Exceptions */

    // TODO: Define and implement DivideByZeroEx and PointNotFoundEx

    class DimensionalityMismatchEx
    {
    private:
        std::string         __name;
        unsigned long int   __currDim;
        unsigned long int   __inputDim;

    public:
        DimensionalityMismatchEx(unsigned long int, unsigned long int);
        ~DimensionalityMismatchEx();

        /* Getters */
        std::string getName() const { return __name; }
        unsigned long int getCurr() const { return __currDim; }
        unsigned long int getInput() const { return __inputDim; }

        /* Overloaded Operators */
        friend std::ostream &operator <<(std::ostream &, const DimensionalityMismatchEx &);
    };
    // ******************************************

    class OutOfBoundsEx
    {
    private:
        std::string         __name;
        unsigned long int   __currSize;
        unsigned int        __inputIndex;

    public:
        OutOfBoundsEx(unsigned long int, unsigned int);
        ~OutOfBoundsEx();

        /* Getters */
        std::string getName() const { return __name; }
        unsigned long int getSize() const { return __currSize; }
        unsigned int getIndex() const { return __inputIndex; }
        
        /* Overloaded Operators */
        friend std::ostream &operator <<(std::ostream &, const OutOfBoundsEx &);
    };
    // ******************************************

    class RemoveFromEmptyEx
    {
    private:
        std::string     __name;
        unsigned int    __pointID;
        unsigned int    __clusterID;

    public:
        RemoveFromEmptyEx(unsigned int, unsigned int);
        ~RemoveFromEmptyEx();

        /* Getters */
        std::string getName() const { return __name; }
        unsigned int getPID() const { return __pointID; }
        unsigned int getCID() const { return __clusterID; }

        /* Overloaded Operators */
        friend std::ostream &operator <<(std::ostream &, const RemoveFromEmptyEx &);
    };

} // end namespace Clustering

#endif //CLUSTERING_EXCEPTIONS_H
