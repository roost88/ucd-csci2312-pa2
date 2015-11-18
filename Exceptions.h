// Programming Assignment 4 - KMeans Clustering

// Author:      Dylan Lang
// Date:        28 October 2015

// Exceptions header file

#ifndef CLUSTERING_EXCEPTIONS_H
#define CLUSTERING_EXCEPTIONS_H

// TODO: Remove these?
#include <string>
#include <iostream>

//#include "KMeans.h"

namespace Clustering
{
    /* Exceptions */

    class DimensionalityMismatchEx
    {
    private:
        std::string         __name;
        int                 __currDim;
        int                 __inputDim;

    public:
        DimensionalityMismatchEx(int, int);
        ~DimensionalityMismatchEx();

        /* Getters */
        std::string getName() const { return __name; }
        int getCurr() const { return __currDim; }
        int getInput() const { return __inputDim; }

        /* Overloaded Operators */
        friend std::ostream &operator <<(std::ostream &, const DimensionalityMismatchEx &);
    };
    /************************************************************/

    class OutOfBoundsEx
    {
    private:
        std::string         __name;
        int                 __currSize;
        unsigned int        __inputIndex;

    public:
        OutOfBoundsEx(int, unsigned int);
        ~OutOfBoundsEx();

        /* Getters */
        std::string getName() const { return __name; }
        int getSize() const { return __currSize; }
        unsigned int getIndex() const { return __inputIndex; }
        
        /* Overloaded Operators */
        friend std::ostream &operator <<(std::ostream &, const OutOfBoundsEx &);
    };
    /************************************************************/

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
    /************************************************************/

    class DivideByZeroEx
    {
    private:
        std::string     __name;

    public:
        DivideByZeroEx();
        ~DivideByZeroEx();

        /* Getters */
        std::string getName() const { return __name; }

        /* Overloaded Operators */
        friend std::ostream &operator <<(std::ostream &, const DivideByZeroEx &);
    };
    /************************************************************/

    class PointAlreadyExistsEx
    {
    private:
        std::string     __name;
        int             __PID;

    public:
        PointAlreadyExistsEx(const int &);
        ~PointAlreadyExistsEx();

        /* Getters */
        std::string getName() const { return __name; }
        int getPoint() const { return __PID; }

        /* Overloaded Operators */
        friend std::ostream &operator <<(std::ostream &, const PointAlreadyExistsEx &);
    };
    /************************************************************/

    class DoesNotExistEx
    {
    private:
        std::string     __name;
        int             __index;
    };

} // end namespace Clustering

#endif //CLUSTERING_EXCEPTIONS_H
