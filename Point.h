// Programming Assignment 4 - KMeans Clustering

// Author:      Dylan Lang
// Date:        28 October 2015

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
    template <typename T, int dim> std::istream &operator >>(std::istream &, Point<T, dim> &);
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
        // Template Point
        Point() :
                __id(__idGenerator++),
                __dim(dim),
                __values(__dim)
        {}

        // Copy constructor
        Point(const Point<T, dim> &right) :
                __id(right.getID()),
                __dim(right.getDim()),
                __values(right.getValuesVector())
        {}

        Point<T, dim> &operator=(const Point<T, dim> &); // Overloaded assignment operator
        ~Point<T, dim>() {  } // Destructor
        /************************************************************/

        /* Templatized Member functions */
        double distanceTo(const Point<T, dim> &) const; // Calculates distance between two points
        static void rewindIdGen() { __idGenerator--; } // Decrements __idGenerator
        /************************************************************/

        /* Setters */
        void setValue(unsigned int, T); // Set value of Point
        /************************************************************/

        /* Getters */
        unsigned int getID() const { return __id; }
        int getDim() const { return __dim; } // Return dimensions of Point
        T getValue(unsigned int) const; // Return value in Point array
        std::vector<T> getValuesVector() const { return __values; } // Return values vector
        /************************************************************/

        /* Overloaded operators dimension-wise (members) */
        Point<T, dim> &operator *=(T);
        Point<T, dim> &operator /=(T);
        /************************************************************/

        /* Overloaded arithmetic operators (members) */
        const Point<T, dim> operator *(T) const;
        const Point<T, dim> operator /(T) const;
        /************************************************************/

        /* Overloaded array operator (member) */
        T &operator [](unsigned int);
        /************************************************************/

        /* Overloaded insertion/extraction operators (friends) */
        friend std::ostream &operator << <T>(std::ostream &, const Point<T, dim> &);
//        friend std::istream &operator >> <T>(std::istream &, Point<T, dim> &);
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
        // Copy ID
        __id = right.getID();

        // Copy dimensions
        __dim = right.getDim();

        // Clear the __values vector
        __values.clear();

        // Copy __values
        for (int i = 0; i < __dim; i++)
        {
            __values.push_back(right.__values[i]);
        }

        return *this;
    }

    /* Templatized Member functions */
    // Calculates distance between two points
    template<typename T, int dim>
    double Point<T, dim>::distanceTo(const Point<T, dim> &p) const
    {
        // Create variables to increment
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
        if (element >= 1 && element <= __dim)
            __values[element - 1] = value;
        else
        {
            // TODO: Throw OutOfBoundsEx
            throw OutOfBoundsEx(__values.size(), element);
        }
    }
    /************************************************************/

    /* Getters */
    template<typename T, int dim>
    T Point<T, dim>::getValue(unsigned int element) const
    {
        if (element >= 1 && element <= __dim)
        {
            return __values[element - 1];
        }
        else
        {
            // TODO: Throw OutOfBoundsEx
            throw OutOfBoundsEx(__dim, element);
        }
    }
    /************************************************************/

    /* Overloaded operators dimension-wise (members) */
    template <typename T, int dim>
    Point<T, dim> &Point<T, dim>::operator *=(T d)
    {
        // Loop through __values of Point
        for (int i = 0; i < __dim; i++)
        {
            // Multiply __values by d
            __values[i] *= d;
        }
        return *this;
    }

    template <typename T, int dim>
    Point<T, dim> &Point<T, dim>::operator /=(T d)
    {
        // Check if d == 0
        if (d != 0)
        {
            // Loop through __values and divide by d
            for (int i = 0; i < __dim; i++)
            {
                __values[i] /= d;
            }
        }
        else
        {
            // TODO: Throw DivideByZeroEx
            throw DivideByZeroEx();
        }
        return *this;
    }
    /************************************************************/

    /* Overloaded arithmetic operators (members) */
    template <typename T, int dim>
    const Point<T, dim> Point<T, dim>::operator *(T d) const
    {
        // Copy left hand Point
        Point result(*this);

        // Multiply by d and return result
        result *= d;
        return result;
    }

    template <typename T, int dim>
    const Point<T, dim> Point<T, dim>::operator /(T d) const
    {
        // Copy point
        Point result(*this);

        // Divide by d and return result
        result /= d;
        return result;
    }
    /************************************************************/

    /* Overloaded [] operator (member) */
    template<typename T, int dim>
    T &Point<T, dim>::operator [](unsigned int index)
    {
        // TODO: Throw OutOfBoundsEx
        if (index < 0 || index >= __dim)
            throw OutOfBoundsEx(__dim, index);

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
            // Output Point __values to one decimal place
            output << std::fixed << std::setprecision(1) << right.__values[i];

            // Add in ',' and space if not the end of array
            if (i < (right.getDim()) - 1)
            {
                output << Point<T, dim>::POINT_VALUE_DELIM << " ";
            }
        }
        return output;
    }

    // Overloaded extraction operator
    template <typename T, int dim>
    std::istream &operator >>(std::istream &input, Point<T, dim> &right)
    {
        // TODO: check for proper input formatting (x,y,z,,)

        /* These are here in case we read directly from a file */
        // Create empty string
        std::string line;
        unsigned long int num_com;

        // Get next line of input and place in string
        std::getline(input, line, '\n');

        // Count number of commas in the line
        num_com = (unsigned) (std::count(line.begin(), line.end(), Point<T, dim>::POINT_VALUE_DELIM));

        // Add one to number of commas to use as Point dimensions
        num_com += 1;

        // Throw DimensionalityMismatch exception
        if (num_com != right.getDim())
        {
            // Decrement __idGenerator
            right.rewindIdGen();

            // TODO: Throw DimensionalityMismatchEx
            throw DimensionalityMismatchEx(right.getDim(), num_com);
        }

        // Turn string into a stream
        std::stringstream lineStr(line);

        // Loop through comma-separated __values
        for (int i = 1; i <= right.getDim(); i++)
        {
            // Create string to hold value
            std::string value;

            // Get the value from the stringstream
            std::getline(lineStr, value, Point<T, dim>::POINT_VALUE_DELIM);

            // Transform value into a double
            // TODO: What do we do with this?
            T val = atof(value.c_str());

            // Set Point's dimension __values
            right.setValue(i, val);
        }

        return input;
    }
    /************************************************************/

    /* Overloaded compound assignment operators (friends) */
    template <typename T, int dim>
    Point<T, dim> &operator +=(Point<T, dim> &left, const Point<T, dim> &right)
    {
        // TODO: Throw DimensionalityMismatch exception
        // Throw DimensionalityMismatchEx exception
        if (left.getDim() != right.getDim())
            throw DimensionalityMismatchEx(left.getDim(), right.getDim());

        // Loop through __values and add right to left
        for (int i = 0; i < right.getDim(); i++)
            left.__values[i] += right.__values[i];

        // Return new left side
        return left;
    }

    template <typename T, int dim>
    Point<T, dim> &operator -=(Point<T, dim> &left, const Point<T, dim> &right)
    {
        // TODO: Throw DimensionalityMismatch exception
        // Throw DimensionalityMismatchEx exception
        if (left.getDim() != right.getDim())
            throw DimensionalityMismatchEx(left.getDim(), right.getDim());

        // Loop through __values and subtract right from left
        for (int i = 0; i < left.getDim(); i++)
            left.__values[i] -= right.__values[i];

        // Return new left side
        return left;
    }
    /************************************************************/

    /* Overloaded binary operators (friends) */
    template <typename T, int dim>
    const Point<T, dim> operator +(const Point<T, dim> &left, const Point<T, dim> &right)
    {
        // TODO: Throw DimensionalityMismatch exception
        if (left.getDim() != right.getDim())
            throw DimensionalityMismatchEx(left.getDim(), right.getDim());

        // Copy left hand Point
        Point<T, dim> result(left);

        // Loop through __values and add right to new left
        for (int i = 0; i < result.getDim(); i++)
            result.__values[i] += right.__values[i];

        return result;
    }

    template <typename T, int dim>
    const Point<T, dim> operator -(const Point<T, dim> &left, const Point<T, dim> &right)
    {
        // TODO: Throw DimensionalityMismatch exception
        if (left.getDim() != right.getDim())
            throw DimensionalityMismatchEx(left.getDim(), right.getDim());

        // Copy left hand Point
        Point<T, dim> result(left);

        // Loop through __values and add right to new left
        for (int i = 0; i < result.getDim(); i++)
            result.__values[i] -= right.__values[i];

        return result;
    }
    /************************************************************/

    /* Overloaded comparison operators (friends) */
    template <typename T, int dim>
    bool operator ==(const Point<T, dim> &left, const Point<T, dim> &right)
    {
        // TODO: Throw DimensionalityMismatch exception
        // Throw DimensionalityMismatchEx exception
        if (left.getDim() != right.getDim())
            throw DimensionalityMismatchEx(left.getDim(), right.getDim());

        else if (left.getID() != right.getID()) // Compare Point IDs
        {
            // Loop through __values
            for (int i = 0; i < left.getDim(); i++)
            {
                // Compare for equality
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
        // TODO: Throw DimensionalityMismatch exception
        // Throw DimensionalityMismatchEx exception
        if (left.getDim() != right.getDim())
            throw DimensionalityMismatchEx(left.getDim(), right.getDim());

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