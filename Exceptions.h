// Programming Assignment 4 - KMeans Clustering

// Author:      Dylan Lang
// Date:        28 October 2015 - 21 November 2015

// Exceptions header file

#ifndef CLUSTERING_EXCEPTIONS_H
#define CLUSTERING_EXCEPTIONS_H

#include <string>
#include <iostream>

namespace Clustering
{
    /* Exceptions */

    // Point dimensions and input dimensions don't match
    class DimensionalityMismatchEx
    {
    private:
        std::string     __name;
        int             __currDim;      // Current Point dimensions
        int             __inputDim;     // Input Point dimensions

    public:
        DimensionalityMismatchEx(int cDim, int iDim);   // Constructor
        ~DimensionalityMismatchEx() { }                 // Destructor

        /* Getters */
        std::string getName() const { return __name; }
        int getCurr() const { return __currDim; }
        int getInput() const { return __inputDim; }

        /* Overloaded Operators */
        friend std::ostream &operator <<(std::ostream &, const DimensionalityMismatchEx &);
    };
    /************************************************************/

    // Index is out of bounds
    class OutOfBoundsEx
    {
    private:
        std::string     __name;
        int             __currSize;     // Size of Point or Cluster
        unsigned int    __inputIndex;   // Index being searched for

    public:
        OutOfBoundsEx(int size, unsigned int index);    // Constructor
        ~OutOfBoundsEx() { }                            // Destructor

        /* Getters */
        std::string getName() const { return __name; }
        int getSize() const { return __currSize; }
        unsigned int getIndex() const { return __inputIndex; }
        
        /* Overloaded Operators */
        friend std::ostream &operator <<(std::ostream &, const OutOfBoundsEx &);
    };
    /************************************************************/

    // Attempt to remove Point from empty Cluster
    class RemoveFromEmptyEx
    {
    private:
        std::string     __name;
        int             __PID;          // Point unique ID number
        int             __CID;          // Cluster unique ID number

    public:
        RemoveFromEmptyEx(int pid, int cid);            // Constructor
        ~RemoveFromEmptyEx() { }                        // Destructor

        /* Getters */
        std::string getName() const { return __name; }
        int getPID() const { return __PID; }
        int getCID() const { return __CID; }

        /* Overloaded Operators */
        friend std::ostream &operator <<(std::ostream &, const RemoveFromEmptyEx &);
    };
    /************************************************************/

    // Attempt to divide something by 0
    class DivideByZeroEx
    {
    private:
        std::string     __name;

    public:
        DivideByZeroEx();                               // Constructor
        ~DivideByZeroEx() { }                           // Destructor

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
        int             __PID;          // Point unique ID number

    public:
        PointAlreadyExistsEx(int pid);                  // Constructor
        ~PointAlreadyExistsEx() { }                     // Destructor

        /* Getters */
        std::string getName() const { return __name; }
        int getPID() const { return __PID; }

        /* Overloaded Operators */
        friend std::ostream &operator <<(std::ostream &, const PointAlreadyExistsEx &);
    };
    /************************************************************/

    class DoesNotExistEx
    {
    private:
        std::string     __name;
        int             __PID;          // Point unique ID number
        int             __CID;          // Cluster unique ID number

    public:
        DoesNotExistEx(int pid, int cid);               // Constructor
        ~DoesNotExistEx() { }                           // Destructor

        /* Getters */
        std::string getName() const { return __name; }
        int getPID() const { return __PID; }
        int getCID() const { return __CID; }

        /* Overloaded Operators */
        friend std::ostream &operator <<(std::ostream &, const DoesNotExistEx &);
    };
    /************************************************************/

} // end namespace Clustering

#endif //CLUSTERING_EXCEPTIONS_H
