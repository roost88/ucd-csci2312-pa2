// Programming Assignment 4 - KMeans Clustering

// Author:      Dylan Lang
// Date:        28 October 2015

// Cluster class header file

// include guard
#ifndef CLUSTERING_CLUSTER_H
#define CLUSTERING_CLUSTER_H

#include <forward_list>

#include "Point.h"

namespace Clustering
{
    typedef Point *PointPtr; // Point * alias
    typedef struct ListNode *ListNodePtr; // ListNode * alias
    typedef class Cluster *ClusterPtr;

    // Node structure supporting singly-linked list
    struct ListNode
    {
        PointPtr p; // Points to specific Point stored in the struct
        ListNodePtr next; // Points to next node in the list
        ListNode(PointPtr pt, ListNodePtr n) : p(pt), next(n) {} // node constructor
    };

    class Cluster
    {
    private:
        unsigned int                __id;               // Unique Cluster ID number
        static unsigned int         __idGenerator;      // Used to increment ID number
        int                         __size;             // Keeps track of the amount of Points in the Cluster
        // TODO: Reimplement __head as std::forward_list<Point>
//        std::forward_list<Point>    __head;
        ListNodePtr                 __head;             // Points to the first node in the list
        unsigned long int           __numDimensions;    // Number of dimensions of Points in Cluster
        Point                       __centroid;         // Mean center Point of Cluster
        bool                        __validCentroid;    // Checks if Centroid of Cluster is valid
        // TODO: Implement static std::unordered_map

    public:
        static const char POINT_CLUSTER_ID_DELIM;   // Static Cluster delimiter value (for output)

        // Inner class Move - represents motion of a Point from one Cluster to another
        class Move
        {
        public:
            // Move constructor
            Move(const Point &p, ClusterPtr from, ClusterPtr to);
            ~Move(){}

            // Move member functions
            void perform(const Point &p, ClusterPtr from, ClusterPtr to); // Moves a Point
        };

        // Cluster constructors
        // Takes an int for the amount of dimensions in Points
        Cluster(unsigned long int numDims) :
                __id(__idGenerator++),
                __size(0),
                __head(nullptr),
                __numDimensions(numDims),
                __centroid(__numDimensions),
                __validCentroid(false){}

        // Copy constructor
        Cluster(const Cluster &right) :
                __id(__idGenerator++),
                __size(right.getSize()),
                __head(deepCopy(right.getHead())),
                __numDimensions(right.getNumDimensions()),
                __centroid(right.getCentroid()),
                __validCentroid(right.getCentroidValidity()){}

        Cluster &operator =(const Cluster &); // Overloaded assignment operator
        ~Cluster(); // Destructor

        // Setters
        void setCentroid(const Point &); // Set Centroid of Cluster

        // Getters
        unsigned int getID() const { return __id; } // Return Cluster ID
        int getSize() const { return __size; } // Return Cluster size
        ListNodePtr getHead() const { return __head; } // Return Cluster linked-list head address
        unsigned long int getNumDimensions() const { return __numDimensions; } // Return number of dimensions of Points
        const Point getCentroid() const { return __centroid; } // Return Cluster Centroid
        bool getCentroidValidity() const { return __validCentroid; } // Return if Centroid is valid or not
        // TODO: implement bool contains(const Point &) method
//        bool contains(const Point &);
        // TODO: implement numberImported() and numberFailed() methods
//        unsigned int numberImported();
//        unsigned int numberFailed();

        // Cluster member functions
        ListNodePtr deepCopy(ListNodePtr); // Copy function
        // TODO: Reimplement add()/remove() to work with const Point &
//        void add(const Point &);
//        const Point &remove(const Point &);
        void add(const Point &); // Add a Point to a Cluster
        const Point &remove(const Point &); // Remove a Point from a Cluster

        // KMeans computeClusteringScore functions
        double intraClusterDistance() const; // Sum of distances between Points in Cluster
        friend double interClusterDistance(const Cluster &, const Cluster &); // Dist between Points between Clusters
        int getClusterEdges(); // Number of unique "edges" between Points in a Cluster
        friend int interClusterEdges(const Cluster &, const Cluster &); // Num of edges between Points between Clusters

        // Centroid specific functions
        void calcCentroid(); // Computes Centroid of Cluster
        void pickPoints(int, PointPtr *); // Pick k Points from Cluster to use as initial Centroids

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

        // TODO: Reimplement using const Point &
        friend const Cluster operator +(const Cluster &, const Point &);
        friend const Cluster operator -(const Cluster &, const Point &);
    };
} // end Clustering namespace
#endif //CLUSTERING_CLUSTER_H
