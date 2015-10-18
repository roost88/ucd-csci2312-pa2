// Programming Assignment 3 - KMeans Clustering

// Author:      Dylan Lang
// Date:        6 October 2015

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
        PointPtr            __centroid; // Pointer to mean Point in Cluster
        bool                __validCentroid; // Checks if Centroid of Cluster is valid

    public:
        static const char POINT_CLUSTER_ID_DELIM; // Static Cluster delimiter value (for output)

        // Inner class Move - represents motion of a Point from one Cluster to another
        class Move
        {
        private:
            // Move members
            PointPtr ptr; // Point that will be moved
            Cluster  *from; // Cluster that Point will be moved from
            Cluster *to; // Cluster that Point will be moved to

        public:
            // Move constructor
            Move(const PointPtr &ptr, Cluster *from, Cluster *to);
            ~Move() { std::cout << "Move destroyed!" << std::endl; };

            // Move member functions
            void perform(const PointPtr &ptr, Cluster *from, Cluster *to); // Moves a Point from one Cluster to another
        };

        // Cluster constructors
        Cluster(); // Default
        Cluster(int); // Takes an int for the amount of dimensions in Points
        Cluster(const Cluster &);  // Copy Constructor
        Cluster &operator=(const Cluster &); // Overloaded assignment operator
        ~Cluster(); // Destructor

        // Cluster member functions
        ListNodePtr deepCopy(ListNodePtr); // Copy function

        void add(const PointPtr &); // Add a Point to a Cluster
        const PointPtr &remove(const PointPtr &); // Remove a Point from a Cluster

        double intraClusterDistance() const; // Sum of distances between Points in Cluster
        friend double interClusterDistance(const Cluster &, const Cluster &);
        int getClusterEdges();

        // Setters
        void setDimensions(int); // Set Point dimensions of Cluster
        void setCentroid(const Point &); // Set Centroid of Cluster

        // Getters
        int getID() { return __id; } // Return Cluster ID
        int getSize() { return __size; } // Return Cluster size
        ListNodePtr getHead() const { return __head; } // Return Cluster linked-list head address
        ListNodePtr getNext() const { return __head->next; } // Return Cluster linked-list next address
        int getNumDimensions() { return __numDimensions; } // Return number of dimensions of Points in Cluster

        // Centroid specific functions
        void calcCentroid(); // Computes Centroid of Cluster
        void pickPoints(int, PointPtr *); // Pick k Points from Cluster to use as initial Centroids
        const Point getCentroid() { return *__centroid; } // Return Cluster Centroid
        bool centroidValidity() { return __validCentroid; }

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
