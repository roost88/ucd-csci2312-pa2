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

/* NON-TEMPLATE CLUSTER CLASS */
/* namespace wrap */
namespace Clustering
{
    /* Key for distances unordered_map */
    struct Key
    {
        unsigned int        __first; // First Point ID
        unsigned int        __second; // Second Point ID

        Key(unsigned int id_1, unsigned int id_2) : __first(id_1), __second(id_2) {}
    };

    // Key hash function
    struct KeyHash
    {
        std::size_t operator()(const Key& k) const
        {
            unsigned int u1 = k.__first;
            unsigned int u2 = k.__second;

            if (u1 > u2)
                std::swap(u1, u2);

            return std::hash<std::size_t>()((u1 + u2) * (u1 + u2 + 1) / 2 + u2);
        }
    };

    // Key equality struct
    struct KeyEqual
    {
        bool operator()(const Key &left, const Key &right) const
        {
            return (left.__first == right.__first && left.__second == right.__second)
                   || (left.__first == right.__second && left.__second == right.__first);
        }
    };
    /************************************************************/

    /* Cluster Class */
    class Cluster
    {
    private:
        unsigned int                                        __id;               // Unique Cluster ID number
        static unsigned int                                 __idGenerator;      // Used to increment ID number
        int                                                 __size;             // Keeps track of the amount of Points in the Cluster
        std::forward_list<Point>                            __head;             // Holds Points in Cluster
        unsigned long int                                   __numDimensions;    // Number of dimensions of Points in Cluster
        Point                                               __centroid;         // Mean center Point of Cluster
        bool                                                __validCentroid;    // Checks if Centroid of Cluster is valid
        std::unordered_map<Key, double, KeyHash, KeyEqual>  __distances;        // Holds distances between Points
        unsigned int                                        __ptsSuccess;       // Number of Points read into Cluster successfully
        unsigned int                                        __ptsFailed;        // Number of Points failed to read into Cluster

    public:
        static const char POINT_CLUSTER_ID_DELIM;   // Static Cluster delimiter value (for output)

        /* Inner class Move */
        // represents motion of a Point from one Cluster to another
        class Move
        {
        private:
            Point       __p;
            Cluster*    __from;
            Cluster*    __to;
        public:
            // Move constructor
            Move(const Point &p, Cluster *from, Cluster *to);
            ~Move(){}

            // Move member functions
            void perform(); // Moves a Point
        };
        /************************************************************/

        /* Cluster constructors */
        // Default
        Cluster() :
                __id(__idGenerator++),
                __size(0),
                __numDimensions(0),
                __centroid(__numDimensions),
                __validCentroid(false),
                __ptsSuccess(0),
                __ptsFailed(0)
        {}

        // Takes dimensions for use in Point constructors
        Cluster(unsigned long int numDims) :
                __id(__idGenerator++),
                __size(0),
                __numDimensions(numDims),
                __centroid(__numDimensions),
                __validCentroid(false),
                __ptsSuccess(0),
                __ptsFailed(0)
        {}

        // Copy constructor
        Cluster(const Cluster &right) :
                __id(right.getID()),
                __size(right.getSize()),
                __head(right.getHead()),
                __numDimensions(right.getNumDimensions()),
                __centroid(right.getCentroid()),
                __validCentroid(right.getCentroidValidity())
        {}

        Cluster &operator =(const Cluster &); // Overloaded assignment operator
        ~Cluster() { std::cout << "Cluster " << this << " destroyed!" << std::endl; } // Destructor
        /************************************************************/

        /* Setters */
        void setCentroid(const Point &); // Set Centroid of Cluster
        void setDistanceMap(); // Set __distances map
        /************************************************************/

        /* Getters */
        unsigned int getID() const { return __id; } // Return Cluster ID
        int getSize() const { return __size; } // Return Cluster size
        std::forward_list<Point> getHead() const { return __head; } // Return Cluster forward list head address
        unsigned long int getNumDimensions() const { return __numDimensions; } // Return number of dimensions of Points
        const Point &getCentroid() const { return __centroid; } // Return Cluster Centroid
        bool getCentroidValidity() const { return __validCentroid; } // Return if Centroid is valid or not
        const std::unordered_map<Key, double, KeyHash, KeyEqual> getMap() const { return __distances; } // Return __distances map
        /************************************************************/

        /* Cluster member functions */
        void add(const Point &); // Add a Point to a Cluster
        const Point &remove(const Point &); // Remove a Point from a Cluster
        void sort(); // Sort Points within Cluster
        // TODO: implement bool contains(const Point &) method
        bool contains(const Point &);
        // TODO: implement numberImported() and numberFailed() methods
        unsigned int numberImported() { return __ptsSuccess; }
        unsigned int numberFailed() { return __ptsFailed; }
        /************************************************************/

        /* KMeans computeClusteringScore functions */
        double intraClusterDistance(const std::unordered_map<Key, double, KeyHash, KeyEqual>&) const; // Sum of distances between Points in Cluster
        friend double interClusterDistance(const Cluster &, const Cluster &, const std::unordered_map<Key, double, KeyHash, KeyEqual>&);
        int getClusterEdges(); // Number of unique "edges" between Points in a Cluster
        friend int interClusterEdges(const Cluster &, const Cluster &); // Num of edges between Points between Clusters
        /************************************************************/

        /* Centroid specific functions */
        void calcCentroid(); // Computes Centroid of Cluster
        void pickPoints(unsigned long int, unsigned long int, Point **); // Pick k Points from Cluster
        /************************************************************/

        /* Overloaded [] operator */
        // TODO: Implement this
        Point &operator [](unsigned int);
        /************************************************************/

        /* Overloaded iostream operators (friends) */
        friend std::ostream &operator <<(std::ostream &, const Cluster &);
        friend std::istream &operator >>(std::istream &, Cluster &);
        /************************************************************/

        /* Overloaded comparison operators (friends) */
        friend bool operator ==(const Cluster &, const Cluster &);
        friend bool operator !=(const Cluster &, const Cluster &);
        /************************************************************/

        /* Overloaded compound assignment operators (members) */
        Cluster &operator +=(const Cluster &);
        Cluster &operator -=(const Cluster &);

        Cluster &operator +=(const Point &);
        Cluster &operator -=(const Point &);
        /************************************************************/

        /* Overloaded binary arithmetic operators (friends) */
        friend const Cluster operator +(const Cluster &, const Cluster &);
        friend const Cluster operator -(const Cluster &, const Cluster &);

        friend const Cluster operator +(const Cluster &, const Point &);
        friend const Cluster operator -(const Cluster &, const Point &);
        /************************************************************/
    };
} // end Clustering namespace
#endif //CLUSTERING_CLUSTER_H

/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/


///* TEMPLATE CLUSTER CLASS */
///* namespace wrap */
//namespace Clustering
//{
//    /* Key for distances unordered_map */
//    struct Key
//    {
//        unsigned int        __first; // First Point ID
//        unsigned int        __second; // Second Point ID
//
//        Key(unsigned int id_1, unsigned int id_2) : __first(id_1), __second(id_2) {}
//    };
//
//    // Key hash function
//    struct KeyHash
//    {
//        std::size_t operator()(const Key& k) const
//        {
//            unsigned int u1 = k.__first;
//            unsigned int u2 = k.__second;
//
//            if (u1 > u2)
//                std::swap(u1, u2);
//
//            return std::hash<std::size_t>()((u1 + u2) * (u1 + u2 + 1) / 2 + u2);
//        }
//    };
//
//    // Key equality struct
//    struct KeyEqual
//    {
//        bool operator()(const Key &left, const Key &right) const
//        {
//            return (left.__first == right.__first && left.__second == right.__second)
//                   || (left.__first == right.__second && left.__second == right.__first);
//        }
//    };
//    /************************************************************/
//
//    /* Cluster Class */
//    class Cluster
//    {
//    private:
//        unsigned int                                        __id;               // Unique Cluster ID number
//        static unsigned int                                 __idGenerator;      // Used to increment ID number
//        int                                                 __size;             // Keeps track of the amount of Points in the Cluster
//        std::forward_list<Point>                            __head;             // Holds Points in Cluster
//        unsigned long int                                   __numDimensions;    // Number of dimensions of Points in Cluster
//        Point                                               __centroid;         // Mean center Point of Cluster
//        bool                                                __validCentroid;    // Checks if Centroid of Cluster is valid
//        std::unordered_map<Key, double, KeyHash, KeyEqual>  __distances;        // Holds distances between Points
//        unsigned int                                        __ptsSuccess;       // Number of Points read into Cluster successfully
//        unsigned int                                        __ptsFailed;        // Number of Points failed to read into Cluster
//
//    public:
//        static const char POINT_CLUSTER_ID_DELIM;   // Static Cluster delimiter value (for output)
//
//        /* Inner class Move */
//        // represents motion of a Point from one Cluster to another
//        class Move
//        {
//        private:
//            Point       __p;
//            Cluster*    __from;
//            Cluster*    __to;
//        public:
//            // Move constructor
//            Move(const Point &p, Cluster *from, Cluster *to);
//            ~Move(){}
//
//            // Move member functions
//            void perform(); // Moves a Point
//        };
//        /************************************************************/
//
//        /* Cluster constructors */
//        // Default
//        Cluster() :
//                __id(__idGenerator++),
//                __size(0),
//                __numDimensions(0),
//                __centroid(__numDimensions),
//                __validCentroid(false),
//                __ptsSuccess(0),
//                __ptsFailed(0)
//        {}
//
//        // Takes dimensions for use in Point constructors
//        Cluster(unsigned long int numDims) :
//                __id(__idGenerator++),
//                __size(0),
//                __numDimensions(numDims),
//                __centroid(__numDimensions),
//                __validCentroid(false),
//                __ptsSuccess(0),
//                __ptsFailed(0)
//        {}
//
//        // Copy constructor
//        Cluster(const Cluster &right) :
//                __id(right.getID()),
//                __size(right.getSize()),
//                __head(right.getHead()),
//                __numDimensions(right.getNumDimensions()),
//                __centroid(right.getCentroid()),
//                __validCentroid(right.getCentroidValidity())
//        {}
//
//        Cluster &operator =(const Cluster &); // Overloaded assignment operator
//        ~Cluster() { std::cout << "Cluster " << this << " destroyed!" << std::endl; } // Destructor
//        /************************************************************/
//
//        /* Setters */
//        void setCentroid(const Point &); // Set Centroid of Cluster
//        void setDistanceMap(); // Set __distances map
//        /************************************************************/
//
//        /* Getters */
//        unsigned int getID() const { return __id; } // Return Cluster ID
//        int getSize() const { return __size; } // Return Cluster size
//        std::forward_list<Point> getHead() const { return __head; } // Return Cluster forward list head address
//        unsigned long int getNumDimensions() const { return __numDimensions; } // Return number of dimensions of Points
//        const Point &getCentroid() const { return __centroid; } // Return Cluster Centroid
//        bool getCentroidValidity() const { return __validCentroid; } // Return if Centroid is valid or not
//        const std::unordered_map<Key, double, KeyHash, KeyEqual> getMap() const { return __distances; } // Return __distances map
//        /************************************************************/
//
//        /* Cluster member functions */
//        void add(const Point &); // Add a Point to a Cluster
//        const Point &remove(const Point &); // Remove a Point from a Cluster
//        void sort(); // Sort Points within Cluster
//        // TODO: implement bool contains(const Point &) method
//        bool contains(const Point &);
//        // TODO: implement numberImported() and numberFailed() methods
//        unsigned int numberImported() { return __ptsSuccess; }
//        unsigned int numberFailed() { return __ptsFailed; }
//        /************************************************************/
//
//        /* KMeans computeClusteringScore functions */
//        double intraClusterDistance(const std::unordered_map<Key, double, KeyHash, KeyEqual>&) const; // Sum of distances between Points in Cluster
//        friend double interClusterDistance(const Cluster &, const Cluster &, const std::unordered_map<Key, double, KeyHash, KeyEqual>&);
//        int getClusterEdges(); // Number of unique "edges" between Points in a Cluster
//        friend int interClusterEdges(const Cluster &, const Cluster &); // Num of edges between Points between Clusters
//        /************************************************************/
//
//        /* Centroid specific functions */
//        void calcCentroid(); // Computes Centroid of Cluster
//        void pickPoints(unsigned long int, unsigned long int, Point **); // Pick k Points from Cluster
//        /************************************************************/
//
//        /* Overloaded [] operator */
//        // TODO: Implement this
//        Point &operator [](unsigned int);
//        /************************************************************/
//
//        /* Overloaded iostream operators (friends) */
//        friend std::ostream &operator <<(std::ostream &, const Cluster &);
//        friend std::istream &operator >>(std::istream &, Cluster &);
//        /************************************************************/
//
//        /* Overloaded comparison operators (friends) */
//        friend bool operator ==(const Cluster &, const Cluster &);
//        friend bool operator !=(const Cluster &, const Cluster &);
//        /************************************************************/
//
//        /* Overloaded compound assignment operators (members) */
//        Cluster &operator +=(const Cluster &);
//        Cluster &operator -=(const Cluster &);
//
//        Cluster &operator +=(const Point &);
//        Cluster &operator -=(const Point &);
//        /************************************************************/
//
//        /* Overloaded binary arithmetic operators (friends) */
//        friend const Cluster operator +(const Cluster &, const Cluster &);
//        friend const Cluster operator -(const Cluster &, const Cluster &);
//
//        friend const Cluster operator +(const Cluster &, const Point &);
//        friend const Cluster operator -(const Cluster &, const Point &);
//        /************************************************************/
//    };
//
///* Member variables */
//unsigned int Cluster::__idGenerator = 1; // Initialize Cluster ID value to 1
//const char Cluster::POINT_CLUSTER_ID_DELIM = ':'; // Set Cluster delimiter for output
///************************************************************/
//
///* Inner Move Class */
//// Move constructor
//Cluster::Move::Move(const Point &p, Cluster *from, Cluster *to)
//{
//    __p = p;
//    __from = from;
//    __to = to;
//
//    perform();
//}
//
//// Move member functions
//void Cluster::Move::perform()
//{
//    // TODO: Catch RemoveFromEmpty exception
//    // Remove Point from Cluster and add to another Cluster
//    try
//    {
//        __to->add(__from->remove(__p));
//    }
//    catch(RemoveFromEmptyEx e)
//    {
//        std::cerr << "In Move.perform method - " << e << std::endl;
//    }
//    catch (PointAlreadyExistsEx e)
//    {
//        std::cerr << "in Move.perform method - " << e << std::endl;
//    }
//}
///************************************************************/
//
///* Overloaded assignment operator (Cluster) */
//Cluster &Cluster::operator =(const Cluster &right)
//{
//    // Copy all values from right into left and return
//    __id = right.getID();
//    __size = right.getSize();
//
//    // Copy __head
//    __head.clear();
//    __head = right.getHead();
//
//    __numDimensions = right.getNumDimensions();
//    __centroid = right.getCentroid();
//    __validCentroid = right.getCentroidValidity();
//
//    return *this;
//}
///************************************************************/
//
///* Setters */
//// Set the Centroid of a Cluster
//void Cluster::setCentroid(const Point &right)
//{
//    // Set Cluster's Centroid equal to new Centroid
//    __centroid = right;
//
//    // Re-validate Centroid
//    __validCentroid = true;
//}
//
//// Calculate distances between Points within Cluster and store in map
//void Cluster::setDistanceMap()
//{
//    // Display message
//    std::cout << "Calculating __distances map!" << std::endl;
//
//    // Copy __head of Cluster
//    std::forward_list<Point> list = this->getHead();
//
//    // Loop through Points in Cluster forward_list
//    for (auto it_1 = list.begin(); it_1 != list.end(); ++it_1)
//    {
//        auto it_2 = it_1;
//        ++it_2; // Offset second iterator to avoid repeating Points
//
//        for (it_2; it_2 != list.end(); ++it_2)
//        {
//            // Create a key
////                Key key(*it_1, *it_2); // TODO: Remove this
//            Key key(it_1->getID(), it_2->getID());
//
//            // Attempt to find key
//            auto search = __distances.find(key);
//
//            // If search reaches end of __distances map, add value to map
//            if (search == __distances.end())
//                __distances[key] = it_1->distanceTo(*it_2);
//        }
//    }
//
//    // Uncomment to display map
//    std::cout << "__distances map:" << std::endl;
//
//    for (auto pos = __distances.begin(); pos != __distances.end(); ++pos)
//    {
//        std::cout << "{{" << pos->first.__first << ", " << pos->first.__second
//        << "}," << pos->second << "}" << std::endl;
//    }
//    std::cout << std::endl;
//}
///************************************************************/
//
///* Cluster member functions */
//// Add Point to Cluster
//void Cluster::add(const Point &right)
//{
//    // Invalidate Centroid
//    __validCentroid = false;
//
//    // Add Point to empty forward list
//    if (__head.empty())
//    {
//        __head.emplace_front(Point(right));
//    }
//    else if (this->contains(right))
//    {
//        // If Point is already in Cluster
//        // Decrement __idGenerator
//        right.rewindIdGen();
//
//        throw PointAlreadyExistsEx(right);
//    }
//    else
//    {
//        // Place Point in list
//        __head.emplace_front(Point(right));
//    }
//
//    // Increment size of Cluster
//    __size++;
//
//    // Sort forward_list
//    this->sort();
//
//    // Uncomment to display added Points
////        std::cout << "Point " << right.getID() << ": " << right
////        << " added to Cluster " << this->getID() << "!" << std::endl;
//}
//
//// Remove Point from Cluster; returns removed Point
//const Point &Cluster::remove(const Point &right)
//{
//    // Invalidate Centroid
//    __validCentroid = false;
//
//    // Case 1 - remove Point from empty forward list
//    // TODO: Throw RemoveFromEmpty exception
//    if (__head.empty())
//    {
//        throw RemoveFromEmptyEx(right.getID(), this->getID());
//    }
//
//        // Case 2 - if Point exists, remove it
//    else if (this->contains(right))
//    {
//        __head.remove(right);
//        __size--;
//    }
//    else
//    {
//        // TODO: Throw PointNotFoundEx?
//        std::cout << "Point not found!" << std::endl;
//    }
//
//    // Uncomment to display remove message
////        std::cout << "Point " << right.getID() << ": " << right
////        << " removed from Cluster " << this->getID() << std::endl;
//    return right;
//}
//
//// Sort Cluster forward_list
//void Cluster::sort()
//{
//    // Uses std::forward_list function sort()
//    __head.sort();
//}
//
//// Check if Cluster already contains Point
//bool Cluster::contains(const Point &p)
//{
//    // Copy forward_list
//    std::forward_list<Point> list = this->getHead();
//
//    // Create iterator
//    std::forward_list<Point>::iterator pos = list.begin();
//
//    // Loop through all Points in Cluster
//    for (pos; pos != list.end(); pos++)
//    {
//        try
//        {
//            if (*pos == p)
//            {
//                return true;
//            }
//        }
//        catch (DimensionalityMismatchEx e)
//        {
//            std::cerr << "In contains method - " << e << std::endl;
//        }
//    }
//
//    // If loop terminates without returning true
//    return false;
//}
///************************************************************/
//
///* KMeans computeClusteringScore functions */
//// Distance between Points within a single Cluster
//double Cluster::intraClusterDistance(const std::unordered_map<Key, double, KeyHash, KeyEqual>& distances) const
//{
//    // Initialize sum
//    double sum = 0;
//
//    // Copy forward list
//    std::forward_list<Point> list = this->getHead();
//
//    // List iterators
//    std::forward_list<Point>::iterator pos = list.begin();
//    std::forward_list<Point>::iterator nxt = list.begin();
//
//    // Double loop through linked-list of Cluster
//    for (pos; pos != list.end(); pos++)
//    {
//        for (nxt; nxt != list.end(); nxt++)
//        {
//            // If Points are equal, add 0 to sum
//            if (*pos == *nxt)
//                sum += 0;
//
//            else
//            {
//                // Create keys using Points to find distance in map
//                Key *key1 = new Key(pos->getID(), nxt->getID());
//                Key *key2 = new Key(nxt->getID(), pos->getID());
//
//                // See if keys exist in map
//                auto search1 = distances.find(*key1);
//                auto search2 = distances.find(*key2);
//
//                // If it does, add distance to sum
//                if (search1 != distances.end())
//                    sum += distances.at(*key1);
//
//                else if (search2 != distances.end())
//                    sum += distances.at(*key2);
//
//                else
//                    sum += pos->distanceTo(*nxt);
//
//                delete key1;
//                delete key2;
//            }
//        }
//    }
//    // Divide sum by two since we looped through twice
//    sum /= 2.0;
//
//    // Uncomment to display sum
////        std::cout << "Cluster " << this->getID() << " intraClusterDistance: " << sum << std::endl;
//    return sum;
//}
//
//// Returns sum of distance between Points between all Clusters
//double interClusterDistance(const Cluster &c1, const Cluster &c2, const std::unordered_map<Key, double, KeyHash, KeyEqual>& distances)
//{
//    // Check if Clusters equal each other
//    if (c1 == c2)
//        return 0;
//
//    // Initialize sum
//    double sum = 0;
//
//    // Copy forward lists
//    std::forward_list<Point> list1 = c1.getHead();
//    std::forward_list<Point> list2 = c2.getHead();
//
//    // Create iterators
//    std::forward_list<Point>::iterator pos1 = list1.begin();
//    std::forward_list<Point>::iterator pos2 = list2.begin();
//
//    // Loop through linked-lists of both Clusters
//    for (pos1; pos1 != list1.end(); pos1++)
//    {
//        for (pos2; pos2 != list2.end(); pos2++)
//        {
//            // If Points are equal, add 0 to sum
//            if (*pos1 == *pos2)
//                sum += 0;
//
//            else
//            {
//                // Create keys using Points to find distance in map
//                Key *key1 = new Key(pos1->getID(), pos2->getID());
//                Key *key2 = new Key(pos2->getID(), pos1->getID());
//
//                // Search for key
//                auto search1 = distances.find(*key1);
//                auto search2 = distances.find(*key2);
//
//                // If found, add distance to sum
//                if (search1 != distances.end())
//                    sum += distances.at(*key1);
//
//                else if (search2 != distances.end())
//                    sum += distances.at(*key2);
//
//                else
//                    sum += pos1->distanceTo(*pos2);
//
//                delete key1;
//                delete key2;
//            }
//        }
//    }
//
//    // Divide sum by 2 since we looped through both lists twice
//    sum /= 2.0;
//
//    // Uncomment to display sum
////        std::cout << "Clusters " << c1.getID() << " and " << c2.getID() << " interClusterDistance: " << sum << std::endl;
//    return sum;
//}
//
//// Returns the number of distinct edges in a Cluster
//int Cluster::getClusterEdges()
//{
//    // Every two distinct Points has an imaginary edge between them
//    int clusterSize = getSize();
//    int result = clusterSize * (clusterSize - 1) / 2;
//
//    // Uncomment to display result
////        std::cout << "Cluster " << this->getID() << " intraClusterEdges: " << result << std::endl;
//    return result;
//}
//
//// Returns the number of distinct edges between Clusters
//int interClusterEdges(const Cluster &c1, const Cluster &c2)
//{
//    // If Clusters are equal, return 0
//    if (c1 == c2)
//        return 0;
//
//    int size1 = c1.getSize();
//    int size2 = c2.getSize();
//    int result = size1 * size2;
//
//    // Uncomment to display result
////        std::cout << "Clusters " << c1.getID() << " and " << c2.getID() << " intraClusterEdges: " << result << std::endl;
//    return result;
//}
///************************************************************/
//
///* Centroid specific functions */
//// Compute the Centroid of a Cluster
//void Cluster::calcCentroid()
//{
//    // Copy forward list
//    std::forward_list<Point> list = this->getHead();
//
//    // Create iterator
//    std::forward_list<Point>::iterator first = list.begin();
//    std::forward_list<Point>::iterator pos = list.begin();
//
//    // Create new Point
//    Point newCent(this->getNumDimensions());
//
//    // Check if list is empty
//    // TODO: Throw RemoveFromEmptyEx
//    if (__head.empty() && this->getSize() <= 0)
//    {
//        this->setCentroid(newCent);
//        throw RemoveFromEmptyEx(0, this->getID());
//    }
//    else if (this->getSize() == 1)
//    {
//        this->setCentroid(*first);
//    }
//    else
//    {
//        // Loop through Points in list and add to newCent
//        for (pos; pos != list.end(); pos++)
//        {
//            newCent += *pos;
//        }
//
//        // Divide sum of all Points in Cluster by size of Cluster
//        newCent /= this->getSize();
//
//        // Set the Centroid
//        this->setCentroid(newCent);
//    }
//}
//
//// Pick k Points from a Cluster to use as initial Centroids for Clustering
//void Cluster::pickPoints(unsigned long int k, unsigned long int dims, Point **pointArray)
//{
//    // Display message
//    std::cout << "Picking Points to use as Centroids..." << std::endl;
//
//    // Copy k
//    unsigned long int kCopy = k;
//
//    // Check if kCopy is greater than the amount of Points in the Cluster
//    if (kCopy > this->getSize())
//        kCopy = (unsigned long int) this->getSize();
//
//    // Divide Cluster size by how many Centroids we want
//    unsigned long int div = this->getSize() / kCopy; // This is what we'll increment count by
//    int count = 0; // Used to increment list position
//
//    // Copy forward list
//    std::forward_list<Point> list = this->getHead();
//
//    // Iterate kCopy times to get kCopy Centroids
//    for (int i = 0; i < k; i++)
//    {
//        if (i < this->getSize())
//        {
//            // Set iterator to the beginning of the list
//            std::forward_list<Point>::iterator pos = list.begin();
//
//            // Use count to iterate through the list to find the Point we want
//            for (int j = 0; j < count; j++)
//            {
//                // Iterate through list
//                pos++;
//            }
//
//            // Copy current Point
//            Point *p1 = new Point(*pos);
//
//            // Put the chosen Point into the Centroid array
//            pointArray[i] = p1;
//
//            // Increment count by the value of div
//            count += div;
//        }
//        else
//        {
//            // Create new Point
//            Point *p2 = new Point(dims);
//
//            // Put empty Point into Centroid array
//            pointArray[i] = p2;
//        }
//    }
//
//    std::cout << "Centroids picked!" << std::endl;
//}
///************************************************************/
//
///* Overloaded [] operator */
//Point &Cluster::operator[](unsigned int index)
//{
//    // TODO: Implement this
//    // TODO: Throw OutOfBoundsEx
//}
///************************************************************/
//
///* Overloaded iostream operators (friends) */
//// Allow us to output an entire Cluster
//std::ostream &operator <<(std::ostream &out, const Cluster &right)
//{
//    // Output will look like: x, y, z : [Cluster ID]
//
//    // Copy forward list
//    std::forward_list<Point> list = right.getHead();
//
//    // Create iterator
//    std::forward_list<Point>::iterator pos = list.begin();
//
//    // Loop through linked-list
//    for (pos; pos != list.end(); pos++)
//    {
//        // Output results
//        out << *pos << " " << Cluster::POINT_CLUSTER_ID_DELIM << " " << right.getID() << std::endl;
//    }
//
//    return out;
//}
//
//// Allow us to input an entire Cluster
//std::istream &operator >>(std::istream &input, Cluster &right)
//{
//    // TODO: check for proper input formatting (x,y,z,,)
//    // Create a new string to read into
//    std::string line;
//    unsigned long int numDims = right.getNumDimensions();
//
//    // While we are able to read from input into string
//    while (std::getline(input, line, '\n'))
//    {
//        // Create new Point
//        Point pt(numDims);
//
//        // Convert the string line into a stringstream
//        std::stringstream lineStr(line);
//
//        try
//        {
//            // Read values into new Point (uses Point extraction operator)
//            lineStr >> pt;
//
//            // Add new Point to the Cluster
//            right.add(pt);
//
//            // Increment __ptsSuccess
//            right.__ptsSuccess++;
//        }
//        catch (DimensionalityMismatchEx e)
//        {
//            // Increment __ptsFailed
//            right.__ptsFailed++;
//
//            // Display the error
//            std::cerr << "In Cluster insertion operator - " << e << std::endl;
//        }
//        catch (PointAlreadyExistsEx e)
//        {
//            // Increment __ptsFailed
//            right.__ptsFailed++;
//
//            // Display the error
//            std::cerr << "In Cluster insertion operator - " << e << std::endl;
//        }
//    }
//
//    return input;
//}
///************************************************************/
//
///* Overloaded comparison operators (friends) */
//// Overloaded equality operator (friend)
//bool operator ==(const Cluster &left, const Cluster &right)
//{
//    // Check sizes and heads of Clusters first
//    if (left.getSize() != right.getSize() || left.getHead() != right.getHead())
//    {
//        return false;
//    }
//    else {
//        // Copy forward lists
//        std::forward_list<Point> list1 = left.getHead();
//        std::forward_list<Point> list2 = right.getHead();
//
//        // Create iterators
//        std::forward_list<Point>::iterator pos1 = list1.begin();
//        std::forward_list<Point>::iterator pos2 = list2.begin();
//
//        // Loop through lists of both Clusters
//        while (pos1 != list1.end() && pos2 != list2.end())
//        {
//            // Check if Points are equal
//            try
//            {
//                if (*pos1 == *pos2)
//                {
//                    pos1++;
//                    pos2++;
//                }
//                else
//                {
//                    return false;
//                }
//            }
//            catch (DimensionalityMismatchEx e)
//            {
//                std::cerr << "In Cluster == operator - " << e << std::endl;
//            }
//        }
//
//        // If while loop terminates without returning false
//        return true;
//    }
//}
//
//// Overloaded inequality operator
//bool operator!=(const Cluster &left, const Cluster &right)
//{
//    return !(left == right);
//}
///************************************************************/
//
///* Overloaded compound assignment operators (members) */
//// Combines two Clusters into one (union)
//Cluster &Cluster::operator +=(const Cluster &right)
//{
//    // Invalidate Centroid
//    __validCentroid = false;
//
//    // Add right Cluster to left Cluster and return
//    *this = *this + right;
//    return *this;
//}
//
//// Subtracts one Cluster from referenced Cluster
//Cluster &Cluster::operator -=(const Cluster &right)
//{
//    // Invalidate Centroid
//    __validCentroid = false;
//
//    // Subtract right Cluster from left Cluster and return
//    *this = *this - right;
//    return *this;
//}
//
//// Add a Point to referenced Cluster
//Cluster &Cluster::operator +=(const Point &right)
//{
//    try
//    {
//        this->add(right);
//    }
//    catch (PointAlreadyExistsEx e)
//    {
//        std::cerr << "In Cluster += operator - " << e << std::endl;
//    }
//    return *this;
//}
//
//// Remove a Point from referenced Cluster
//Cluster &Cluster::operator -=(const Point &right)
//{
//    try
//    {
//        this->remove(right);
//    }
//    catch(RemoveFromEmptyEx e)
//    {
//        std::cout << e << std::endl;
//    }
//
//    return *this;
//}
///************************************************************/
//
///* Overloaded binary arithmetic operators (friends) */
//// Add two Clusters together
//const Cluster operator +(const Cluster &left, const Cluster &right)
//{
//    // Create new Cluster equal to left-hand-side
//    Cluster c(left);
//
//    // Copy right-hand-side forward list
//    std::forward_list<Point> list = right.getHead();
//
//    // Create iterator
//    std::forward_list<Point>::iterator pos = list.begin();
//
//    // Loop through list and add Points to new Cluster
//    for (pos; pos != list.end(); pos++)
//    {
//        c += *pos;
//    }
//
//    return c;
//}
//
//// Subtract one Cluster from another
//const Cluster operator -(const Cluster &left, const Cluster &right)
//{
//    // Create new Cluster equal to left-hand-side
//    Cluster c(left);
//
//    // Copy right-hand-side forward list
//    std::forward_list<Point> list = right.getHead();
//
//    // Create iterator
//    std::forward_list<Point>::iterator pos = list.begin();
//
//    // Loop through list and remove Points from new Cluster
//    for (pos; pos != list.end(); pos++)
//    {
//        c -= *pos;
//    }
//
//    return c;
//}
//
//// Add a Point to a Cluster
//const Cluster operator +(const Cluster &left, const Point &right)
//{
//    // Copy left-hand-side
//    Cluster c(left);
//
//    // Add Point to Cluster
//    c += right;
//
//    return c;
//}
//
//// Subtract a Point from a Cluster
//const Cluster operator -(const Cluster &left, const Point &right)
//{
//    // Copy left-hand-side
//    Cluster c(left);
//
//    // Remove Point from Cluster
//    c -= right;
//
//    return c;
//}
///************************************************************/
//} // end Clustering namespace
//#endif //CLUSTERING_CLUSTER_H