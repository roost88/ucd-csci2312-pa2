// Programming Assignment 4 - KMeans Clustering

// Author:      Dylan Lang
// Date:        28 October 2015

// Cluster class header file

// include guard
#ifndef CLUSTERING_CLUSTER_H
#define CLUSTERING_CLUSTER_H

#include <forward_list>
#include <unordered_map>

#include "Point.h"

namespace Clustering
{
    typedef class Point *PointPtr; // Point * alias
    typedef class Cluster *ClusterPtr; // Cluster * alias
    typedef std::forward_list<Point> fList; // Forward List alias

    struct Key
    {
        unsigned int        __first; // First Point ID
        unsigned int        __second; // Second Point ID
    };

    typedef std::unordered_map<Key, double> hashMap; // Hashmap alias

    class Cluster
    {
    private:
        unsigned int        __id;               // Unique Cluster ID number
        static unsigned int __idGenerator;      // Used to increment ID number
        int                 __size;             // Keeps track of the amount of Points in the Cluster
        fList               __head;             // Holds Points in Cluster
        unsigned long int   __numDimensions;    // Number of dimensions of Points in Cluster
        Point               __centroid;         // Mean center Point of Cluster
        bool                __validCentroid;    // Checks if Centroid of Cluster is valid
        static hashMap      __distances;        // Holds distances between Points

    public:
        static const char POINT_CLUSTER_ID_DELIM;   // Static Cluster delimiter value (for output)

        // Inner class Move - represents motion of a Point from one Cluster to another
        class Move
        {
        private:
            Point       __p;
            ClusterPtr  __from;
            ClusterPtr  __to;
        public:
            // Move constructor
            Move(const Point &p, ClusterPtr from, ClusterPtr to);
            ~Move(){}

            // Move member functions
            void perform(); // Moves a Point
        };

        // Cluster constructors
        Cluster() :
                __id(__idGenerator++),
                __size(0),
                __numDimensions(0),
                __centroid(__numDimensions, true),
                __validCentroid(false) {}

        // Takes an int for the amount of dimensions in Points
        Cluster(unsigned long int numDims) :
                __id(__idGenerator++),
                __size(0),
                __numDimensions(numDims),
                __centroid(__numDimensions, true),
                __validCentroid(false) {}

        // Copy constructor
        Cluster(const Cluster &right) :
                __id(right.getID()),
                __size(right.getSize()),
                __head(right.getHead()),
                __numDimensions(right.getNumDimensions()),
                __centroid(right.getCentroid()),
                __validCentroid(right.getCentroidValidity()){}

        Cluster &operator =(const Cluster &); // Overloaded assignment operator
        ~Cluster(); // Destructor

        // Setters
        void setCentroid(const Point &); // Set Centroid of Cluster
        void setDistanceMap(const Point &, const Point &); // Set __distances map

        // Getters
        unsigned int getID() const { return __id; } // Return Cluster ID
        int getSize() const { return __size; } // Return Cluster size
        fList getHead() const { return __head; } // Return Cluster forward list head address
        unsigned long int getNumDimensions() const { return __numDimensions; } // Return number of dimensions of Points
        const Point getCentroid() const { return __centroid; } // Return Cluster Centroid
        bool getCentroidValidity() const { return __validCentroid; } // Return if Centroid is valid or not

        // Cluster member functions
        void add(const Point &); // Add a Point to a Cluster
        const Point &remove(const Point &); // Remove a Point from a Cluster
        void sort(); // Sort Points within Cluster
        // TODO: implement bool contains(const Point &) method
        bool contains(const Point &);
        // TODO: implement numberImported() and numberFailed() methods
//        unsigned int numberImported();
//        unsigned int numberFailed();

        // KMeans computeClusteringScore functions
        double intraClusterDistance() const; // Sum of distances between Points in Cluster
        friend double interClusterDistance(const Cluster &, const Cluster &); // Dist between Points between Clusters
        int getClusterEdges(); // Number of unique "edges" between Points in a Cluster
        friend int interClusterEdges(const Cluster &, const Cluster &); // Num of edges between Points between Clusters

        // Centroid specific functions
        void calcCentroid(); // Computes Centroid of Cluster
        void pickPoints(unsigned long int, PointPtr *); // Pick k Points from Cluster to use as initial Centroids

        // Overloaded [] operator
        // TODO: Implement this
        Point &operator [](unsigned int);

        // Overloaded iostream operators (friends)
        friend std::ostream &operator <<(std::ostream &, const Cluster &);
        friend std::istream &operator >>(std::istream &, Cluster &);

        // Overloaded comparison operators (friends)
        friend bool operator ==(const Cluster &, const Cluster &);
        friend bool operator !=(const Cluster &, const Cluster &);

        // Overloaded compound assignment operators (members)
        Cluster &operator +=(const Cluster &);
        Cluster &operator -=(const Cluster &);

        Cluster &operator +=(const Point &);
        Cluster &operator -=(const Point &);

        // Overloaded binary arithmetic operators (friends)
        friend const Cluster operator +(const Cluster &, const Cluster &);
        friend const Cluster operator -(const Cluster &, const Cluster &);

        friend const Cluster operator +(const Cluster &, const Point &);
        friend const Cluster operator -(const Cluster &, const Point &);
    };
} // end Clustering namespace
#endif //CLUSTERING_CLUSTER_H
