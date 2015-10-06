// Programming Assignment 2 - Three Dimensional Triangle

// Author:      Dylan Lang
// Date:        10 Sept 2015

// Cluster class definition

// include guard
#ifndef CLUSTERING_CLUSTER_H
#define CLUSTERING_CLUSTER_H

#include "Point.h"

namespace Clustering
{
    // Alias for Point *
    typedef Point *PointPtr;

    // Alias for Node *
    typedef struct ListNode *ListNodePtr;

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
        int size; // Keeps track of the amount of Points in the Cluster
        ListNodePtr head; // Points to the first node in the list

    public:
        // Constructors
        // Default constructor
        Cluster();

        Cluster(const Cluster &); // Copy Constructor
        Cluster &operator=(const Cluster &); // Overloaded assignment operator
        ~Cluster(); // Destructor

        // Member functions
        ListNodePtr deepCopy(ListNodePtr);

        // Add or remove Points from Cluster
        void add(const PointPtr &);
        const PointPtr &remove(const PointPtr &);

        // Getters for testing
        int getSize() { return size; }
        ListNodePtr getHead() const { return head; };
        ListNodePtr getNext() const { return head->next; };

        // Overloaded operator functions
        // Overloaded iostream operators
        // Allow us to output an entire Cluster
        friend std::ostream &operator <<(std::ostream &, const Cluster &);

        // Allow us to input an entire Cluster
        friend std::istream &operator >>(std::istream &, Cluster &);

        // Overloaded comparison operators (friend)
        friend bool operator ==(const Cluster &, const Cluster &);
        friend bool operator !=(const Cluster &, const Cluster &);

        // Overloaded compound assignment operators (members)
        // Combines two Clusters into one (union)
        Cluster &operator +=(const Cluster &);

        // Subtracts one Cluster from referenced Cluster
        Cluster &operator -=(const Cluster &);

        // Add a Point to referenced Cluster
        Cluster &operator +=(const Point &);

        // Remove a Point from referenced Cluster
        Cluster &operator -=(const Point &);

        // Overloaded binary arithmetic operators (friends)
        // Add two Clusters together
        friend const Cluster operator +(const Cluster &, const Cluster &);

        // Subtract one Cluster from another
        friend const Cluster operator -(const Cluster &, const Cluster &);

        // Add a Point to a Cluster
        friend const Cluster operator +(const Cluster &, const PointPtr &);

        // Subtract a Point from a Cluster
        friend const Cluster operator -(const Cluster &, const PointPtr &);
    };
} // end Clustering namespace
#endif //CLUSTERING_CLUSTER_H
