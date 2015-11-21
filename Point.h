// Programming Assignment 4 - KMeans Clustering

// Author:      Dylan Lang
// Date:        28 October 2015 - 21 November 2015

// Point class header file

// include guard
#ifndef CLUSTERING_POINT_H
#define CLUSTERING_POINT_H

#include "Exceptions.h"

#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <array>
#include <fstream>
#include <vector>
#include <exception>
/************************************************************/

/* TEMPLATE POINT CLASS */
/* namespace wrap */
namespace Clustering {

    /* Template declarations */
    template <typename T, int dim> class Point;
    template <typename T, int dim> std::ostream &operator <<(std::ostream &, const Point<T, dim> &);
    template <typename T, int dim> std::istream &operator >>(std::istream &, Clustering::Point<T, dim> &);
    template <typename T, int dim> Point<T, dim> &operator +=(Point<T, dim> &, const Point<T, dim> &);
    template <typename T, int dim> Point<T, dim> &operator -=(Point<T, dim> &, const Point<T, dim> &);
    template <typename T, int dim> const Point<T, dim> operator +(const Point<T, dim> &, const Point<T, dim> &);
    template <typename T, int dim> const Point<T, dim> operator -(const Point<T, dim> &, const Point<T, dim> &);
    template <typename T, int dim> bool operator ==(const Point<T, dim> &, const Point<T, dim> &);
    template <typename T, int dim> bool operator !=(const Point<T, dim> &, const Point<T, dim> &);
    template <typename T, int dim> bool operator >(const Point<T, dim> &, const Point<T, dim> &);
    template <typename T, int dim> bool operator <(const Point<T, dim> &, const Point<T, dim> &);
    template <typename T, int dim> bool operator >=(const Point<T, dim> &, const Point<T, dim> &);
    template <typename T, int dim> bool operator <=(const Point<T, dim> &, const Point<T, dim> &);
    /************************************************************/

    /* Point Class */
    template <typename T, int dim>
    class Point {
    private:
        unsigned int            __id;           // Unique Point ID
        static unsigned int     __idGenerator;  // Used to increment ID number
        int                     __dim;          // Point dimensions variable
        std::vector<T>          __values;       // Holds Point dimension values

    public:
        static const char POINT_VALUE_DELIM;    // Static Point delimiter (for I/O)

        /* Template Point Constructors */
        // Template Point Constructor
        Point() :
                __id(__idGenerator++),
                __dim(dim),
                __values(__dim)
        { }

        // Copy constructor
        Point(const Point<T, dim> &right) :
                __id(right.getID()),
                __dim(right.getDim()),
                __values(right.getValuesVector())
        { }

        Point<T, dim> &operator=(const Point<T, dim> &);            // Overloaded assignment operator
        ~Point() { }                                                // Destructor
        /************************************************************/

        /* Templatized Member functions */
        double distanceTo(const Point<T, dim> &) const;             // Calculates distance between two points
        static void rewindIdGen() { __idGenerator--; }              // Decrements __idGenerator
        /************************************************************/

        /* Setters */
        void setValue(unsigned int, T);                             // Set value of Point
        /************************************************************/

        /* Getters */
        unsigned int getID() const { return __id; }                 // Get the ID of the Point
        int getDim() const { return __dim; }                        // Return dimensions of Point
        T getValue(unsigned int) const;                             // Return value in Point array
        std::vector<T> getValuesVector() const { return __values; } // Return values vector
        /************************************************************/

        /* Overloaded operators dimension-wise (members) */
        Point<T, dim> &operator *=(T);                              // Multiply Point by right variable
        Point<T, dim> &operator /=(T);                              // Divide Point by right variable
        /************************************************************/

        /* Overloaded arithmetic operators (members) */
        const Point<T, dim> operator *(T) const;                    // Multiply Point by right variable
        const Point<T, dim> operator /(T) const;                    // Divide Point by right variable
        /************************************************************/

        /* Overloaded array operator (member) */
        T &operator [](unsigned int);                               // Return value at index
        /************************************************************/

        /* Overloaded insertion/extraction operators (friends) */
        friend std::ostream &operator << <T>(std::ostream &, const Point<T, dim> &);
        friend std::istream &operator >> <T>(std::istream &, Point<T, dim> &);
        /************************************************************/

        /* Overloaded compound assignment operators (friends) */
        friend Point<T, dim> &operator += <T>(Point<T, dim> &, const Point<T, dim> &);
        friend Point<T, dim> &operator -= <T>(Point<T, dim> &, const Point<T, dim> &);
        /************************************************************/

        /* Overloaded binary operators (friends) */
        friend const Point<T, dim> operator + <T>(const Point<T, dim> &, const Point<T, dim> &);
        friend const Point<T, dim> operator - <T>(const Point<T, dim> &, const Point<T, dim> &);
        /************************************************************/

        /* Overloaded comparison operators (friends) */
        friend bool operator == <T>(const Point<T, dim> &, const Point<T, dim> &);
        friend bool operator != <T>(const Point<T, dim> &, const Point<T, dim> &);
        friend bool operator > <T>(const Point<T, dim> &, const Point<T, dim> &);
        friend bool operator < <T>(const Point<T, dim> &, const Point<T, dim> &);
        friend bool operator >= <T>(const Point<T, dim> &, const Point<T, dim> &);
        friend bool operator <= <T>(const Point<T, dim> &, const Point<T, dim> &);
        /************************************************************/
    };

    /* Member variables */
    template <typename T, int dim>
    unsigned int Point<T, dim>::__idGenerator = 0; // Initialize Point ID value to 0

    template <typename T, int dim>
    const char Point<T, dim>::POINT_VALUE_DELIM = ','; // Defines Point I/O delimiter
    /************************************************************/

    /* Constructors */
    // Overloaded assignment operator
    template <typename T, int dim>
    Point<T, dim> &Point<T, dim>::operator =(const Point<T, dim> &right)
    {
        __id = right.getID();   // Copy ID
        __dim = right.getDim(); // Copy dimensions
        __values.clear();       // Empty the __values vector

        // Copy __values
        for (int i = 0; i < __dim; i++)
            __values.push_back(right.__values[i]);

        return *this;
    }

    /* Template Member functions */
    // Calculates distance between two points
    template<typename T, int dim>
    double Point<T, dim>::distanceTo(const Point<T, dim> &p) const
    {
        double sum = 0;
        double distance = 0;

        // Loop through __values
        for (int i = 0; i < __dim; i++)
        {
            // Compute difference between __values
            double diff = static_cast<double> (__values[i] - p.__values[i]);

            // Add square to difference to sum (will be a positive number)
            sum += (diff * diff);
        }
        // Compute distance and return it
        distance = sqrt(sum);
        return distance;
    }
    /************************************************************/

    /* Setters */
    template<typename T, int dim>
    void Point<T, dim>::setValue(unsigned int element, T value)
    {
        // Verify index
        if (element < 0 || element > __dim)
            throw OutOfBoundsEx(__values.size(), element); // Throw exception

        __values[element - 1] = value; // Set value
    }
    /************************************************************/

    /* Getters */
    template<typename T, int dim>
    T Point<T, dim>::getValue(unsigned int element) const
    {
        // Verify index
        if (element < 0 || element >= __dim)
            throw OutOfBoundsEx(__values.size(), element); // Throw exception

        return __values[element - 1]; // Return value
    }
    /************************************************************/

    /* Overloaded operators dimension-wise (members) */
    template <typename T, int dim>
    Point<T, dim> &Point<T, dim>::operator *=(T d)
    {
        // Loop through __values of Point
        for (int i = 0; i < __dim; i++)
            __values[i] *= d; // Multiply __values by d

        return *this;
    }

    template <typename T, int dim>
    Point<T, dim> &Point<T, dim>::operator /=(T d)
    {
        // Check if d equals 0
        if (d == 0)
            throw DivideByZeroEx(); // Throw exception

        for (int i = 0; i < __dim; i++)
            __values[i] /= d; // Divide value

        return *this;
    }
    /************************************************************/

    /* Overloaded arithmetic operators (members) */
    template <typename T, int dim>
    const Point<T, dim> Point<T, dim>::operator *(T d) const
    {
        Point result(*this); // Copy left hand Point
        result *= d; // Multiply by d
        return result;
    }

    template <typename T, int dim>
    const Point<T, dim> Point<T, dim>::operator /(T d) const
    {
        // Check if d equals 0
        if (d == 0)
            throw DivideByZeroEx(); // Throw exception

        Point result(*this); // Copy left hand Point
        result /= d; // Divide by d using overloaded /= operator
        return result;
    }
    /************************************************************/

    /* Overloaded [] operator (member) */
    template<typename T, int dim>
    T &Point<T, dim>::operator [](unsigned int index)
    {
        // Verify index
        if (index < 0 || index >= __dim)
            throw OutOfBoundsEx(__dim, index); // Throw exception

        return __values[index];
    }
    /************************************************************/

    /* Overloaded insertion/extraction operators (friends) */
    // Overloaded insertion operator
    template <typename T, int dim>
    std::ostream &operator <<(std::ostream &output, const Point<T, dim> &right)
    {
        // Output will look like: x, y, z
        // Loop through __values
        for (int i = 0; i < right.getDim(); i++)
        {
            output << std::fixed << std::setprecision(1) << right.__values[i]; // Output Point values

            if (i < (right.getDim()) - 1)
                output << Point<T, dim>::POINT_VALUE_DELIM << " "; // Add in ',' and space if not the end of array
        }
        return output;
    }

    // Overloaded extraction operator
    template <typename T, int dim>
    std::istream &operator >>(std::istream &input, Clustering::Point<T, dim> &right)
    {
        /* These are here in case we read directly from a file */
        std::string line; // Create empty string
        unsigned long int num_com; // Holds # of commas in line

        std::getline(input, line, '\n'); // Get next line of input and place in string

        // Count number of commas in the line
        num_com = (unsigned) (std::count(line.begin(), line.end(), Clustering::Point<T, dim>::POINT_VALUE_DELIM));
        num_com += 1; // Add one to number of commas to use as Point dimensions

        // Verify commas and dimensions
        if (num_com != right.getDim())
        {
            right.rewindIdGen(); // Decrement __idGenerator
            throw Clustering::DimensionalityMismatchEx(right.getDim(), num_com); // Throw exception
        }

        std::stringstream lineStr(line); // Turn string into a stream

        // Loop through comma-separated __values
        for (int i = 1; i <= right.getDim(); i++)
        {
            std::string value; // Create string to hold value
            std::getline(lineStr, value, Clustering::Point<T, dim>::POINT_VALUE_DELIM); // Get value from stringstream
            T val = atof(value.c_str()); // Transform value into a float

            try
            {
                right.setValue(i, val); // Set the current value
            }
            catch (Clustering::OutOfBoundsEx e)
            {
                std::cout << "In Point extraction operator - " << e << std::endl; // Display exception
            }
        }

        return input;
    }
    /************************************************************/

    /* Overloaded compound assignment operators (friends) */
    template <typename T, int dim>
    Point<T, dim> &operator +=(Point<T, dim> &left, const Point<T, dim> &right)
    {
        // Check dimensions of both Points
        if (left.getDim() != right.getDim())
            throw DimensionalityMismatchEx(left.getDim(), right.getDim()); // Throw exception

        for (int i = 0; i < right.getDim(); i++)
            left.__values[i] += right.__values[i]; // Add right values to left values

        return left;
    }

    template <typename T, int dim>
    Point<T, dim> &operator -=(Point<T, dim> &left, const Point<T, dim> &right)
    {
        // Check dimensions of both Points
        if (left.getDim() != right.getDim())
            throw DimensionalityMismatchEx(left.getDim(), right.getDim()); // Throw exception

        for (int i = 0; i < left.getDim(); i++)
            left.__values[i] -= right.__values[i]; // Subtract right values from left values

        return left;
    }
    /************************************************************/

    /* Overloaded binary operators (friends) */
    template <typename T, int dim>
    const Point<T, dim> operator +(const Point<T, dim> &left, const Point<T, dim> &right)
    {
        // Check dimensions of both Points
        if (left.getDim() != right.getDim())
            throw DimensionalityMismatchEx(left.getDim(), right.getDim()); // Throw exception

        Point<T, dim> result(left); // Copy left hand Point

        for (int i = 0; i < result.getDim(); i++)
            result.__values[i] += right.__values[i]; // Add right values to left values

        return result;
    }

    template <typename T, int dim>
    const Point<T, dim> operator -(const Point<T, dim> &left, const Point<T, dim> &right)
    {
        // Check dimensions of both Points
        if (left.getDim() != right.getDim())
            throw DimensionalityMismatchEx(left.getDim(), right.getDim()); // Throw exception

        Point<T, dim> result(left); // Copy left hand Point

        for (int i = 0; i < result.getDim(); i++)
            result.__values[i] -= right.__values[i]; // Subtract right values from left values

        return result;
    }
    /************************************************************/

    /* Overloaded comparison operators (friends) */
    template <typename T, int dim>
    bool operator ==(const Point<T, dim> &left, const Point<T, dim> &right)
    {
        // Check dimensions of both Points
        if (left.getDim() != right.getDim())
            throw DimensionalityMismatchEx(left.getDim(), right.getDim()); // Throw exception

        // Compare IDs of both Points
        else if (left.getID() != right.getID())
        {
            // Loop through values of Points
            for (int i = 0; i < left.getDim(); i++)
            {
                // Check equality of values
                if (left.__values[i] != right.__values[i])
                    return false;
            }
        }

        return true;
    }

    template <typename T, int dim>
    bool operator !=(const Point<T, dim> &left, const Point<T, dim> &right)
    {
        // Use overloaded == operator to see if they are equal
        return !(left == right);
    }

    template <typename T, int dim>
    bool operator >(const Point<T, dim> &left, const Point<T, dim> &right)
    {
        // Check dimensions of both Points
        if (left.getDim() != right.getDim())
            throw DimensionalityMismatchEx(left.getDim(), right.getDim()); // Throw exception

        // Loop through __values
        for (int i = 0; i < left.getDim(); i++)
        {
            // Compare __values
            if (left.__values[i] > right.__values[i])
            {
                // If left > right, return true
                return true;
            }
            else if (left.__values[i] == right.__values[i])
            {
                // If __values are equal, move to next value
                continue;
            }
            else
            {
                // If left value is not >= right value, return false
                break;
            }
        }

        return false;
    }

    template <typename T, int dim>
    bool operator <(const Point<T, dim> &left, const Point<T, dim> &right)
    {
        // Use overloaded > operator to compare
        return !(left > right);
    }

    template <typename T, int dim>
    bool operator >=(const Point<T, dim> &left, const Point<T, dim> &right)
    {
        // Use overloaded > and == to compare
        return (left > right || left == right);
    }

    template <typename T, int dim>
    bool operator <=(const Point<T, dim> &left, const Point<T, dim> &right)
    {
        // Use overloaded < and == to compare
        return (left < right || left == right);
    }
    /************************************************************/

} // end Clustering namespace
#endif //CLUSTERING_POINT_H


/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/


///* NON-TEMPLATE POINT CLASS */
///* namespace wrap */
//namespace Clustering {
//
//    /* Point Class */
//    class Point {
//    private:
//        unsigned int            __id;           // Unique Point ID
//        static unsigned int     __idGenerator;  // Used to increment ID number
//        unsigned long int       __dim;          // Point dimensions variable
//        std::vector<double>     __values;       // Holds Point dimension values
//
//    public:
//        static const char POINT_VALUE_DELIM;    // Static Point delimiter (for I/O)
//
//        /* Point Constructors */
//        // Default
//        Point() :
//                __id(__idGenerator++),
//                __dim(0),
//                __values(__dim) { }
//
//        // Takes dimensions
//        Point(unsigned long int dimensions) :
//                __id(__idGenerator++),
//                __dim(dimensions),
//                __values(__dim) { }
//
//        // Copy constructor
//        Point(const Point &right) :
//                __id(right.getID()),
//                __dim(right.getDim()),
//                __values(right.getValuesVector()) { }
//
//        Point &operator=(const Point &); // Overloaded assignment operator
//        ~Point() { } // Destructor
//        /************************************************************/
//
//        /* Member functions (non-templates) */
//        double distanceTo(const Point &) const; // Calculates distance between two points
//        static void rewindIdGen() { __idGenerator--; } // Decrements __idGenerator
//        /************************************************************/
//
//        /* Setters */
//        void setValue(int, double); // Set value of Point
//        /************************************************************/
//
//        /* Getters */
//        unsigned int getID() const { return __id; }
//        unsigned long int getDim() const { return __dim; } // Return dimensions of Point
//        double getValue(unsigned int) const; // Return value in Point array
//        std::vector<double> getValuesVector() const { return __values; } // Return values vector
//        /************************************************************/
//
//        /* Overloaded operators dimension-wise (members) */
//        Point &operator*=(double);
//        Point &operator/=(double);
//        /************************************************************/
//
//        /* Overloaded arithmetic operators (members) */
//        const Point operator*(double) const;
//        const Point operator/(double) const;
//        /************************************************************/
//
//        /* Overloaded array operator (member) */
//        double &operator[](unsigned int);
//        /************************************************************/
//
//        /* Overloaded insertion/extraction operators (friends) */
//        friend std::ostream &operator<<(std::ostream &, const Point &);
//        friend std::istream &operator>>(std::istream &, Point &);
//        /************************************************************/
//
//        /* Overloaded compound assignment operators (friends) */
//        friend Point &operator+=(Point &, const Point &);
//        friend Point &operator-=(Point &, const Point &);
//        /************************************************************/
//
//        /* Overloaded binary operators (friends) */
//        friend const Point operator+(const Point &, const Point &);
//        friend const Point operator-(const Point &, const Point &);
//        /************************************************************/
//
//        /* Overloaded comparison operators (friends) */
//        friend bool operator==(const Point &, const Point &);
//        friend bool operator!=(const Point &, const Point &);
//        friend bool operator>(const Point &, const Point &);
//        friend bool operator<(const Point &, const Point &);
//        friend bool operator>=(const Point &, const Point &);
//        friend bool operator<=(const Point &, const Point &);
//        /************************************************************/
//    };
//} // end namespace Clustering
//#endif //CLUSTERING_POINT_H