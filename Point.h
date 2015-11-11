// Programming Assignment 4 - KMeans Clustering

// Author:      Dylan Lang
// Date:        28 October 2015

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
#include <vector>
#include <exception>

/* namespace wrap */
namespace Clustering
{
    class Point
    {
    private:
        unsigned int            __id;           // Unique Point ID
        static unsigned int     __idGenerator;  // Used to increment ID number
        unsigned long int       __dim;          // Point dimensions variable
        std::vector<double>     __values;       // Holds Point dimension values

    public:
        /* Public member variables */
        static const char POINT_VALUE_DELIM; // Static Point delimiter (for I/O)

        /* Constructors */
        Point();
        Point(unsigned long int, bool);
        Point(const Point &); // Copy constructor
        Point &operator=(const Point &); // Overloaded assignment operator
        ~Point() {} // Destructor

        /* Member functions */
        double distanceTo(const Point &) const; // Calculates distance between two points
        static void rewindIdGen() { __idGenerator--; } // Decrements __idGenerator

        /* Setters */
        void setValue(int, double); // Set value of Point

        /* Getters */
        unsigned int getID() const { return __id; }
        unsigned long int getDim() const { return __dim; } // Return dimensions of Point
        double getValue(unsigned int) const; // Return value in Point array
        std::vector<double> getValues() const { return __values; } // Return values vector

        /* Overloaded operators dimension-wise (members) */
        Point &operator *=(double);
        Point &operator /=(double);
        const Point operator *(double) const;
        const Point operator /(double) const;

        /* Overloaded array operator */
        double &operator [](unsigned int);

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