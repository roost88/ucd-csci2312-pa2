// Programming Assignment 2 - Three Dimensional Triangle

// Author:      Dylan Lang
// Date:        10 Sept 2015

// Point class definition

// include guard
#ifndef CLUSTERING_POINT_H
#define CLUSTERING_POINT_H

// Clustering namespace wrap
namespace Clustering
{
    class Point
    {
    private:
        int dim; // private Dimensions variable
        double *values; // Point dimension values

    public:
        // Constructors
        Point(int);

        Point(const Point &); // Copy constructor
        Point &operator=(const Point &); // Overloaded assignment operator
        ~Point(); // Destructor

        // Member functions
        // Mutator methods
        void setValue(int, double) const;

        // Accessor methods
        int getDim() const { return dim; };
        double getValue(int) const;

        double distanceTo(const Point &) const; // Calculates distance between two points

        // Overloaded operators dimension-wise (members)
        Point &operator *=(double);

        Point &operator /=(double);

        const Point operator *(double) const;

        const Point operator /(double) const;

        // Overloaded array operator
        double &operator[](int index) { return values[index - 1]; }

        // friend functions
        // Overloaded insertion operator
        friend std::ostream &operator <<(std::ostream &, const Point &);

        // Overloaded compound assignment operators (friends)
        friend Point &operator +=(Point &, const Point &);

        friend Point &operator -=(Point &, const Point &);

        // Overloaded binary operators (friends)
        friend const Point operator +(const Point &, const Point &);

        friend const Point operator -(const Point &, const Point &);

        // Overloaded comparison operators (friends)
        friend bool operator ==(const Point &, const Point &);

        friend bool operator !=(const Point &, const Point &);

        friend bool operator >(const Point &, const Point &);

        friend bool operator <(const Point &, const Point &);

        friend bool operator >=(const Point &, const Point &);

        friend bool operator <=(const Point &, const Point &);

    }; // end Point class
} // end Clustering namespace

#endif // end CLUSTERING_POINT_H