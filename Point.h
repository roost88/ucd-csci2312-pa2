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
    /* Template declaration */
//    template <typename T, unsigned long int dim>
    /************************************************************/

    /* Point Class */
    class Point
    {
    private:
        unsigned int            __id;           // Unique Point ID
        static unsigned int     __idGenerator;  // Used to increment ID number
        unsigned long int       __dim;          // Point dimensions variable
//        std::vector<T>          __values;       // Holds Point dimension values
        std::vector<double>     __values;       // Holds Point dimension values

    public:
        static const char POINT_VALUE_DELIM;    // Static Point delimiter (for I/O)

        /* Point Constructors */
        // Default
        Point() :
                __id(__idGenerator++),
                __dim(0),
                __values(__dim)
        {}

//        // Template Point
//        Point() :
//                __id(__idGenerator++),
//                __dim(dim),
//                __values(__dim)
//        {}

        // Takes dimensions
        Point(unsigned long int dimensions) :
                __id(__idGenerator++),
                __dim(dimensions),
                __values(__dim)
        {}

        // Copy constructor
        Point(const Point &right) :
                __id(right.getID()),
                __dim(right.getDim()),
                __values(right.getValuesVector())
        {}

        Point &operator=(const Point &); // Overloaded assignment operator
        ~Point() {} // Destructor
        /************************************************************/

        /* Member functions */
        double distanceTo(const Point &) const; // Calculates distance between two points
        static void rewindIdGen() { __idGenerator--; } // Decrements __idGenerator
        /************************************************************/

        /* Setters */
        void setValue(int, double); // Set value of Point
        /************************************************************/

        /* Getters */
        unsigned int getID() const { return __id; }
        unsigned long int getDim() const { return __dim; } // Return dimensions of Point
        double getValue(unsigned int) const; // Return value in Point array
        std::vector<double> getValuesVector() const { return __values; } // Return values vector
        /************************************************************/

        /* Overloaded operators dimension-wise (members) */
        Point &operator *=(double);
        Point &operator /=(double);
        /************************************************************/

        /* Overloaded arithmetic operators (members) */
        const Point operator *(double) const;
        const Point operator /(double) const;
        /************************************************************/

        /* Overloaded array operator (member) */
        double &operator [](unsigned int);
        /************************************************************/

        /* Overloaded insertion/extraction operators (friends) */
        friend std::ostream &operator <<(std::ostream &, const Point &);
        friend std::istream &operator >>(std::istream &, Point &);
        /************************************************************/

        /* Overloaded compound assignment operators (friends) */
        friend Point &operator +=(Point &, const Point &);
        friend Point &operator -=(Point &, const Point &);
        /************************************************************/

        /* Overloaded binary operators (friends) */
        friend const Point operator +(const Point &, const Point &);
        friend const Point operator -(const Point &, const Point &);
        /************************************************************/

        /* Overloaded comparison operators (friends) */
        friend bool operator ==(const Point &, const Point &);
        friend bool operator !=(const Point &, const Point &);
        friend bool operator >(const Point &, const Point &);
        friend bool operator <(const Point &, const Point &);
        friend bool operator >=(const Point &, const Point &);
        friend bool operator <=(const Point &, const Point &);
        /************************************************************/

//        /* Templatized Member functions */
//        T distanceTo(const Point<T, dim> &) const; // Calculates distance between two points
//        static void rewindIdGen() { __idGenerator--; } // Decrements __idGenerator
//        /************************************************************/
//
//        /* Setters */
//        void setValue(int, T); // Set value of Point
//        /************************************************************/
//
//        /* Getters */
//        unsigned int getID() const { return __id; }
//        unsigned long int getDim() const { return __dim; } // Return dimensions of Point
//        T getValue(unsigned int) const; // Return value in Point array
//        std::vector<T> getValuesVector() const { return __values; } // Return values vector
//        /************************************************************/
//
//        /* Overloaded operators dimension-wise (members) */
//        Point<T, dim> &operator *=(T);
//        Point<T, dim> &operator /=(T);
//        /************************************************************/
//
//        /* Overloaded arithmetic operators (members) */
//        const Point<T, dim> operator *(T) const;
//        const Point<T, dim> operator /(T) const;
//        /************************************************************/
//
//        /* Overloaded array operator (member) */
//        T &operator [](unsigned int);
//        /************************************************************/
//
//        /* Overloaded insertion/extraction operators (friends) */
//        friend std::ostream &operator <<(std::ostream &, const Point<T, dim> &);
//        friend std::istream &operator >>(std::istream &, Point<T, dim> &);
//        /************************************************************/
//
//        /* Overloaded compound assignment operators (friends) */
//        friend Point<T, dim> &operator +=(Point<T, dim> &, const Point<T, dim> &);
//        friend Point<T, dim> &operator -=(Point<T, dim> &, const Point<T, dim> &);
//        /************************************************************/
//
//        /* Overloaded binary operators (friends) */
//        friend const Point<T, dim> operator +(const Point<T, dim> &, const Point<T, dim> &);
//        friend const Point<T, dim> operator -(const Point<T, dim> &, const Point<T, dim> &);
//        /************************************************************/
//
//        /* Overloaded comparison operators (friends) */
//        friend bool operator ==(const Point<T, dim> &, const Point<T, dim> &);
//        friend bool operator !=(const Point<T, dim> &, const Point<T, dim> &);
//        friend bool operator >(const Point<T, dim> &, const Point<T, dim> &);
//        friend bool operator <(const Point<T, dim> &, const Point<T, dim> &);
//        friend bool operator >=(const Point<T, dim> &, const Point<T, dim> &);
//        friend bool operator <=(const Point<T, dim> &, const Point<T, dim> &);
//        /************************************************************/
    };
} // end Clustering namespace
#endif //CLUSTERING_POINT_H