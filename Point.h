// Programming Assignment 3 - KMeans Clustering

// Author:      Dylan Lang
// Date:        20 October 2015

// Point class header file

// include guard
#ifndef CLUSTERING_POINT_H
#define CLUSTERING_POINT_H

#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <array>
#include <fstream>

/* namespace wrap */
namespace Clustering
{
    class Point
    {
    private:
        int     dim; // Point dimensions variable
        double  *values; // Point values array

    public:
        /* Public member variables */
        static const char POINT_VALUE_DELIM; // Static Point delimiter (for I/O)

        /* Constructors */
        Point(int);
        Point(const Point &); // Copy constructor
        Point &operator=(const Point &); // Overloaded assignment operator
        ~Point() { delete [] values; }; // Destructor

        /* Member functions */
        double distanceTo(const Point &) const; // Calculates distance between two points

        /* Setters */
        void setValue(int, double) const; // Set value of Point

        /* Getters */
        int getDim() const { return dim; }; // Return dimensions of Point
        double getValue(int) const; // Return value in Point array

        /* Overloaded operators dimension-wise (members) */
        Point &operator *=(double);
        Point &operator /=(double);
        const Point operator *(double) const;
        const Point operator /(double) const;

        /* Overloaded array operator */
        double &operator[](int index) { return values[index - 1]; }

        /* Overloaded insertion/extraction operators (friends) */
        friend std::ostream &operator <<(std::ostream &, const Point &);
        friend std::istream &operator >>(std::istream &, Point &);

        /* Overloaded compound assignment operators (friends) */
        friend Point &operator +=(Point &, const Point &);
        friend Point &operator -=(Point &, const Point &);

        /* Overloaded binary operators (friends) */
        friend const Point operator +(const Point &, const Point &);
        friend const Point operator -(const Point &, const Point &);

        /* Overloaded comparison operators (friends) */
        friend bool operator ==(const Point &, const Point &);
        friend bool operator !=(const Point &, const Point &);
        friend bool operator >(const Point &, const Point &);
        friend bool operator <(const Point &, const Point &);
        friend bool operator >=(const Point &, const Point &);
        friend bool operator <=(const Point &, const Point &);
    };
} // end Clustering namespace
#endif //CLUSTERING_POINT_H