// Programming Assignment 3 - KMeans Clustering

// Author:      Dylan Lang
// Date:        20 October 2015

// Cluster class header file

// include guard
#ifndef CLUSTERING_CLUSTER_H
#define CLUSTERING_CLUSTER_H

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
        unsigned int        __id; // Unique Cluster ID number
        static unsigned int __idGenerator; // Used to increment ID number
        int                 __size; // Keeps track of the amount of Points in the Cluster
        ListNodePtr         __head; // Points to the first node in the list
        int                 __numDimensions; // Number of dimensions of Points in Cluster
        Point               __centroid; // Mean center Point of Cluster
        bool                __validCentroid; // Checks if Centroid of Cluster is valid

    public:
        static const char POINT_CLUSTER_ID_DELIM; // Static Cluster delimiter value (for output)

        // Inner class Move - represents motion of a Point from one Cluster to another
        class Move
        {
        public:
            // Move constructor
            Move(const PointPtr &ptr, ClusterPtr from, ClusterPtr to);
            ~Move(){}

            // Move member functions
            void perform(const PointPtr &ptr, ClusterPtr from, ClusterPtr to); // Moves a Point from one Cluster to another
        };

        // Cluster constructors
        // Takes an int for the amount of dimensions in Points
        Cluster(int numDims) :
                __id(__idGenerator++),
                __size(0),
                __head(nullptr),
                __numDimensions(numDims),
                __centroid(__numDimensions),
                __validCentroid(false){}

        // Copy constructor
        Cluster(const Cluster &right) :
                __id(__idGenerator++),
                __size(right.__size),
                __head(deepCopy(right.__head)),
                __numDimensions(right.__numDimensions),
                __centroid(right.__centroid),
                __validCentroid(right.__validCentroid){}

        Cluster &operator =(const Cluster &); // Overloaded assignment operator
        ~Cluster(); // Destructor

        // Setters
        void setCentroid(const Point &); // Set Centroid of Cluster

        // Getters
        int getID() { return __id; } // Return Cluster ID
        int getSize() { return __size; } // Return Cluster size
        ListNodePtr getHead() const { return __head; } // Return Cluster linked-list head address
        int getNumDimensions() { return __numDimensions; } // Return number of dimensions of Points in Cluster
        const Point getCentroid() { return __centroid; } // Return Cluster Centroid
        bool getCentroidValidity() { return __validCentroid; } // Return if Centroid is valid or not

        // Cluster member functions
        ListNodePtr deepCopy(ListNodePtr); // Copy function
        void add(const PointPtr &); // Add a Point to a Cluster
        const PointPtr &remove(const PointPtr &); // Remove a Point from a Cluster

        // KMeans computeClusteringScore functions
        double intraClusterDistance() const; // Sum of distances between Points in Cluster
        friend double interClusterDistance(const Cluster &, const Cluster &); // Dist between Points between Clusters
        int getClusterEdges(); // Number of unique "edges" between Points in a Cluster
        friend int interClusterEdges(const Cluster &, const Cluster &); // Num of edges between Points between Clusters

        // Centroid specific functions
        void calcCentroid(); // Computes Centroid of Cluster
        void pickPoints(int, PointPtr *); // Pick k Points from Cluster to use as initial Centroids

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

        friend const Cluster operator +(const Cluster &, const PointPtr &);
        friend const Cluster operator -(const Cluster &, const PointPtr &);
    };
} // end Clustering namespace
#endif //CLUSTERING_CLUSTER_H
