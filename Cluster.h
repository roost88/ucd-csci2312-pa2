// Programming Assignment 4 - KMeans Clustering

// Author:      Dylan Lang
// Date:        28 October 2015

// Cluster class header file

// include guard
#ifndef CLUSTERING_CLUSTER_H
#define CLUSTERING_CLUSTER_H

#include "Point.h"

#include <forward_list>
#include <unordered_map>
/************************************************************/

/* TEMPLATE CLUSTER CLASS */
/* namespace wrap */
namespace Clustering
{
    /* Key for distances unordered_map */
    struct Key
    {
        unsigned int __first; // First Point ID
        unsigned int __second; // Second Point ID

        Key(unsigned int id_1, unsigned int id_2) : __first(id_1), __second(id_2) { }
    };

    // Key hash function
    struct KeyHash
    {
        std::size_t operator()(const Key &k) const
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

    /* Template declarations */
    template<typename T, int dim> class Cluster;
    template<typename T, int dim> double interClusterDistance(const Cluster<T, dim> &, const Cluster<T, dim> &,
                                const std::unordered_map<Key, double, KeyHash, KeyEqual> &);
    template<typename T, int dim> int interClusterEdges(const Cluster<T, dim> &, const Cluster<T, dim> &);
    template<typename T, int dim> std::ostream &operator<<(std::ostream &, const Cluster<T, dim> &);
    template<typename T, int dim> std::istream &operator>>(std::istream &, Cluster<T, dim> &);
    template<typename T, int dim> bool operator==(const Cluster<T, dim> &, const Cluster<T, dim> &);
    template<typename T, int dim> bool operator!=(const Cluster<T, dim> &, const Cluster<T, dim> &);
    template<typename T, int dim> const Cluster<T, dim> operator+(const Cluster<T, dim> &, const Cluster<T, dim> &);
    template<typename T, int dim> const Cluster<T, dim> operator-(const Cluster<T, dim> &, const Cluster<T, dim> &);
    template<typename T, int dim> const Cluster<T, dim> operator+(const Cluster<T, dim> &, const T &);
    template<typename T, int dim> const Cluster<T, dim> operator-(const Cluster<T, dim> &, const T &);
    /************************************************************/

    /* Cluster Class */
    template<typename T, int dim>
    class Cluster
    {
    private:
        unsigned int                                        __id;               // Unique Cluster ID number
        static unsigned int                                 __idGenerator;      // Used to increment ID number
        int                                                 __size;             // # of Points in the Cluster
        std::forward_list<T>                                __head;             // Holds Points in Cluster
        int                                                 __numDimensions;    // Dimensions of Points in Cluster
        T                                                   __centroid;         // Mean center Point of Cluster
        bool                                                __validCentroid;    // Checks Centroid validity
        std::unordered_map<Key, double, KeyHash, KeyEqual>  __distances;        // Holds distances between Points
        unsigned int                                        __ptsSuccess;       // # of Points read successfully
        unsigned int                                        __ptsFailed;        // # of Points failed to read

    public:
        static const char POINT_CLUSTER_ID_DELIM;   // Static Cluster delimiter value (for output)

        /* Inner class Move */
        // represents motion of a Point from one Cluster to another
        class Move
        {
        private:
            T                   __p;
            Cluster<T, dim> *   __from;
            Cluster<T, dim> *   __to;
        public:
            // Move constructor
            Move(const T &p, Cluster<T, dim> *from, Cluster<T, dim> *to) :
                    __p(p),
                    __from(from),
                    __to(to) { perform(); }

            ~Move() { }

            // Move member functions
            void perform(); // Moves a Point
        };
        /************************************************************/

        /* Cluster constructors */
        // Default
        Cluster() :
                __id(__idGenerator++),
                __size(0),
                __numDimensions(dim),
                __centroid(),
                __validCentroid(false),
                __distances(),
                __ptsSuccess(0),
                __ptsFailed(0) { }

        // Copy constructor
        Cluster(const Cluster<T, dim> &right) :
                __id(right.getID()),
                __size(right.getSize()),
                __head(right.getHead()),
                __numDimensions(right.getNumDimensions()),
                __centroid(right.getCentroid()),
                __validCentroid(right.getCentroidValidity()) { }

        Cluster<T, dim> &operator=(const Cluster<T, dim> &); // Overloaded assignment operator
        ~Cluster() { std::cout << "Cluster " << this->getID() << " @ " << this << " destroyed!" << std::endl; }
        /************************************************************/

        /* Setters */
        void setCentroid(const T &); // Set Centroid of Cluster
        void setDistanceMap(); // Set __distances map
        /************************************************************/

        /* Getters */
        unsigned int getID() const { return __id; } // Return Cluster ID
        int getSize() const { return __size; } // Return Cluster size
        std::forward_list<T> getHead() const { return __head; } // Return Cluster forward list head address
        int getNumDimensions() const { return __numDimensions; } // Return number of dimensions of Points
        const T &getCentroid() const { return __centroid; } // Return Cluster Centroid
        bool getCentroidValidity() const { return __validCentroid; } // Return if Centroid is valid or not
        const std::unordered_map<Key, double, KeyHash, KeyEqual> getMap() const { return __distances; } // Return map
        /************************************************************/

        /* Cluster member functions */
        void add(const T &); // Add a Point to a Cluster
        const T &remove(const T &); // Remove a Point from a Cluster
        void sort(); // Sort Points within Cluster
        bool contains(const T &); // Check if Cluster contains a particular Point
        unsigned int numberImported() { return __ptsSuccess; } // Returns # of Points imported successfully
        unsigned int numberFailed() { return __ptsFailed; } // Returns # of Points failed to import
        /************************************************************/

        /* KMeans computeClusteringScore functions */
        double intraClusterDistance() const; // Sum of distances between Points in Cluster

        // Sum of distances between Points between Clusters
        friend double interClusterDistance <T>(const Cluster<T, dim> &, const Cluster<T, dim> &,
                                              const std::unordered_map<Key, double, KeyHash, KeyEqual> &);

        int getClusterEdges(); // Number of unique "edges" between Points in a Cluster

        // Number of unique "edges" between Points between Clusters
        friend int interClusterEdges <T>(const Cluster<T, dim> &, const Cluster<T, dim> &);
        /************************************************************/

        /* Centroid specific functions */
        void calcCentroid(); // Computes Centroid of Cluster
        void pickPoints(int, int, T **); // Pick k Points from Cluster
        /************************************************************/

        /* Overloaded [] operator */
        // TODO: Implement this
        T &operator[](unsigned int);
        /************************************************************/

        /* Overloaded iostream operators (friends) */
        friend std::ostream &operator << <T>(std::ostream &, const Cluster<T, dim> &);
        friend std::istream &operator >> <T>(std::istream &, Cluster<T, dim> &);
        /************************************************************/

        /* Overloaded comparison operators (friends) */
        friend bool operator == <T>(const Cluster<T, dim> &, const Cluster<T, dim> &);
        friend bool operator != <T>(const Cluster<T, dim> &, const Cluster<T, dim> &);
        /************************************************************/

        /* Overloaded compound assignment operators (members) */
        Cluster<T, dim> &operator +=(const Cluster<T, dim> &);
        Cluster<T, dim> &operator -=(const Cluster<T, dim> &);
        Cluster<T, dim> &operator +=(const T &);
        Cluster<T, dim> &operator -=(const T &);
        /************************************************************/

        /* Overloaded binary arithmetic operators (friends) */
        friend const Cluster operator + <T>(const Cluster<T, dim> &, const Cluster<T, dim> &);
        friend const Cluster operator - <T>(const Cluster<T, dim> &, const Cluster<T, dim> &);
        friend const Cluster operator + <T>(const Cluster<T, dim> &, const T &);
        friend const Cluster operator - <T>(const Cluster<T, dim> &, const T &);
        /************************************************************/
    };

    /* Member variables */
    template<typename T, int dim>
    unsigned int Cluster<T, dim>::__idGenerator = 1; // Initialize Cluster ID value to 1

    template<typename T, int dim>
    const char Cluster<T, dim>::POINT_CLUSTER_ID_DELIM = ':'; // Set Cluster delimiter for output
    /************************************************************/

    /* Inner Move Class */
    // Move member functions
    template<typename T, int dim>
    void Cluster<T, dim>::Move::perform()
    {
        // Remove Point from Cluster and add to another Cluster
        try { __to->add(__from->remove(__p)); }

        catch (RemoveFromEmptyEx e) { std::cout << "In Move.perform method - " << e << std::endl; }

        catch (PointAlreadyExistsEx e) { std::cout << "in Move.perform method - " << e << std::endl; }
    }
    /************************************************************/

    /* Overloaded assignment operator (Cluster) */
    template<typename T, int dim>
    Cluster<T, dim> &Cluster<T, dim>::operator =(const Cluster<T, dim> &right)
    {
        // Copy all values from right into left and return
        __id = right.getID();
        __size = right.getSize();
        __head.clear(); // Clear forward_list
        __head = right.getHead();
        __numDimensions = right.getNumDimensions();
        __centroid = right.getCentroid();
        __validCentroid = right.getCentroidValidity();
        return *this;
    }
    /************************************************************/

    /* Setters */
    // Set the Centroid of a Cluster
    template<typename T, int dim>
    void Cluster<T, dim>::setCentroid(const T &right)
    {
        __centroid = right; // Set Cluster's Centroid equal to new Centroid
        __validCentroid = true; // Re-validate Centroid
    }

    // Calculate distances between Points within Cluster and store in map
    template<typename T, int dim>
    void Cluster<T, dim>::setDistanceMap()
    {
        std::cout << "Calculating __distances map!" << std::endl; // Display message

        std::forward_list<T> list = this->getHead(); // Copy __head of Cluster

        // Loop through Points in Cluster forward_list
        for (auto it_1 = list.begin(); it_1 != list.end(); ++it_1)
        {
            auto it_2 = it_1;
            ++it_2; // Offset second iterator to avoid repeating Points

            for (it_2; it_2 != list.end(); ++it_2)
            {
                Key key(it_1->getID(), it_2->getID()); // Create a key

                auto search = __distances.find(key); // Attempt to find key

                // If search reaches end of __distances map, add value to map
                if (search == __distances.end())
                    __distances[key] = it_1->distanceTo(*it_2);
            }
        }

        // Uncomment to display map
//        std::cout << "__distances map:" << std::endl;
//
//        for (auto pos = __distances.begin(); pos != __distances.end(); ++pos)
//        {
//            std::cout << "{{" << pos->first.__first << ", " << pos->first.__second
//            << "}," << pos->second << "}" << std::endl;
//        }
//        std::cout << std::endl;
    }
    /************************************************************/

    /* Cluster member functions */
    // Add Point to Cluster
    template<typename T, int dim>
    void Cluster<T, dim>::add(const T &right)
    {
        // TODO: Must add in lexicographic order
        // Check if Point is already in Cluster
        if (this->contains(right))
        {
            // If Point is already in Cluster
            right.rewindIdGen(); // Decrement __idGenerator
            throw PointAlreadyExistsEx(right.getID()); // Throw exception
        }
        else
        {
            __head.emplace_front(right); // Original
        }

        __size++; // Increment size of Cluster
        __validCentroid = false; // Invalidate Centroid

        // Uncomment to display added Points
//        std::cout << "Point " << right.getID() << ": " << right
//        << " added to Cluster " << this->getID() << "!" << std::endl;
    }

    // Remove Point from Cluster; returns removed Point
    template<typename T, int dim>
    const T &Cluster<T, dim>::remove(const T &right)
    {
        __validCentroid = false; // Invalidate Centroid

        // Case 1 - remove Point from empty forward list
        if (__head.empty())
            throw RemoveFromEmptyEx(right.getID(), this->getID());

        else if (this->contains(right))
        {
            // If Point exists in Cluster, remove it and decrement __size
            __head.remove(right);
            __size--;
        }
        else
            std::cout << "Point " << right.getID() << " not found in Cluster!" << std::endl;

        // Uncomment to display remove message
//        std::cout << "Point " << right.getID() << ": " << right
//        << " removed from Cluster " << this->getID() << std::endl;
        return right;
    }

    // Sort Cluster forward_list
    template<typename T, int dim>
    void Cluster<T, dim>::sort()
    {
        __head.sort(); // Uses std::forward_list function sort()
    }

    // Check if Cluster already contains Point
    template<typename T, int dim>
    bool Cluster<T, dim>::contains(const T &right)
    {
        std::forward_list<T> list = this->getHead(); // Copy forward_list
        auto pos = list.begin(); // Create iterator

        // Loop through all Points in Cluster
        for (pos; pos != list.end(); pos++)
        {
            try
            {
                if (*pos == right)
                    return true;
            }
            catch (DimensionalityMismatchEx e) { std::cout << "In Cluster.contains method - " << e << std::endl; }
        }

        // If loop terminates without returning true
        return false;
    }
    /************************************************************/

    /* KMeans computeClusteringScore functions */
    // Distance between Points within a single Cluster
    template<typename T, int dim>
    double Cluster<T, dim>::intraClusterDistance() const
    {
        double sum = 0; // Initialize sum

        std::forward_list<T> list = this->getHead(); // Copy forward list
        auto pos = list.begin();

        // Double loop through linked-list of Cluster
        for (pos; pos != list.end(); pos++)
        {
            auto nxt = pos;
            ++nxt; // Increment so we count each distance once

            for (nxt; nxt != list.end(); nxt++)
            {
                // If Points are equal, add 0 to sum
                if (*pos == *nxt)
                    sum += 0;

                else
                {
                    // Create keys using Points to find distance in map
                    Key *key1 = new Key(pos->getID(), nxt->getID());
                    Key *key2 = new Key(nxt->getID(), pos->getID());

                    // See if keys exist in map
                    auto search1 = __distances.find(*key1);
                    auto search2 = __distances.find(*key2);

                    // If it does, add distance to sum
                    if (search1 != __distances.end())
                        sum += (__distances.at(*key1));

                    else if (search2 != __distances.end())
                        sum += (__distances.at(*key2));

                    else
                        sum += (pos->distanceTo(*nxt));

                    delete key1;
                    delete key2;
                }
            }
        }

        // Uncomment to display sum
//        std::cout << "Cluster " << this->getID() << " intraClusterDistance: " << sum << std::endl;
        return sum;
    }

    // Returns sum of distance between Points between all Clusters
    template<typename T, int dim>
    double interClusterDistance(const Cluster<T, dim> &c1, const Cluster<T, dim> &c2,
                           const std::unordered_map<Key, double, KeyHash, KeyEqual> &distances)
    {
        // Check if Clusters equal each other
        if (c1 == c2)
            return 0;

        // Initialize sum
        double sum = 0;

        // Copy forward lists
        std::forward_list<T> list1 = c1.getHead();
        std::forward_list<T> list2 = c2.getHead();

        // Create iterators
        auto pos1 = list1.begin();
        auto pos2 = list2.begin();

        // Loop through linked-lists of both Clusters
        for (pos1; pos1 != list1.end(); pos1++)
        {
            for (pos2; pos2 != list2.end(); pos2++)
            {
                // If Points are equal, add 0 to sum
                if (*pos1 == *pos2)
                    sum += 0;

                else
                {
                    // Create keys using Points to find distance in map
                    Key *key1 = new Key(pos1->getID(), pos2->getID());
                    Key *key2 = new Key(pos2->getID(), pos1->getID());

                    // Search for key
                    auto search1 = distances.find(*key1);
                    auto search2 = distances.find(*key2);

                    // If found, add distance to sum
                    if (search1 != distances.end())
                        sum += (distances.at(*key1));

                    else if (search2 != distances.end())
                        sum += (distances.at(*key2));

                    else
                        sum += (pos1->distanceTo(*pos2));

                    delete key1;
                    delete key2;
                }
            }
        }

        // Uncomment to display sum
//        std::cout << "Clusters " << c1.getID() << " and " << c2.getID() << " interClusterDistance: " << sum << std::endl;
        return sum;
    }

    // Returns the number of distinct edges in a Cluster
    template<typename T, int dim>
    int Cluster<T, dim>::getClusterEdges()
    {
        // Every two distinct Points has an imaginary edge between them
        int clusterSize = getSize();
        int result = clusterSize * (clusterSize - 1) / 2;

        // Uncomment to display result
//        std::cout << "Cluster " << this->getID() << " intraClusterEdges: " << result << std::endl;
        return result;
    }

    // Returns the number of distinct edges between Clusters
    template<typename T, int dim>
    int interClusterEdges(const Cluster<T, dim> &c1, const Cluster<T, dim> &c2)
    {
        // If Clusters are equal, return 0
        if (c1 == c2)
            return 0;

        int size1 = c1.getSize();
        int size2 = c2.getSize();
        int result = size1 * size2;

        // Uncomment to display result
//        std::cout << "Clusters " << c1.getID() << " and " << c2.getID() << " intraClusterEdges: " << result << std::endl;
        return result;
    }
    /************************************************************/

    /* Centroid specific functions */
    // Compute the Centroid of a Cluster
    template<typename T, int dim>
    void Cluster<T, dim>::calcCentroid()
    {
        std::forward_list<T> list = this->getHead(); // Copy forward list
        auto first = list.begin();
        auto pos = list.begin();

        T newCent; // Create new Point

        // Check if list is empty
        if (__head.empty() && this->getSize() <= 0)
        {
            this->setCentroid(newCent);
            throw RemoveFromEmptyEx(newCent.getID(), this->getID());
        }
        else if (this->getSize() == 1)
        {
            this->setCentroid(*first);
        }
        else
        {
            // Loop through Points in list and add to newCent
            for (pos; pos != list.end(); pos++)
                newCent += *pos;

            // Divide sum of all Points in Cluster by size of Cluster
            newCent /= this->getSize();

            // Set the Centroid
            this->setCentroid(newCent);
        }
    }

    // Pick k Points from a Cluster to use as initial Centroids for Clustering
    template<typename T, int dim>
    void Cluster<T, dim>::pickPoints(int k, int dims, T **pointArray)
    {
        std::cout << "Picking Points to use as Centroids..." << std::endl; // Display message

        int kCopy = k; // Copy k

        // Check if kCopy is greater than the amount of Points in the Cluster
        if (kCopy > this->getSize())
            kCopy = this->getSize();

        // Divide Cluster size by how many Centroids we want
        int div = this->getSize() / kCopy; // This is what we'll increment count by
        int count = 0; // Used to increment list position

        std::forward_list<T> list = this->getHead(); // Copy forward list

        // Iterate kCopy times to get kCopy Centroids
        for (int i = 0; i < k; i++)
        {
            if (i < this->getSize())
            {
                auto pos = list.begin(); // Set iterator to the beginning of the list

                // Use count to iterate through the list to find the Point we want
                for (int j = 0; j < count; j++)
                    pos++; // Iterate through list

                T *p1 = new T(*pos); // Copy current Point

                pointArray[i] = p1; // Put the chosen Point into the Centroid array

                count += div; // Increment count by the value of div
            }
            else
            {
                T *p2 = new T; // Create new Point

                pointArray[i] = p2; // Put empty Point into Centroid array
            }
        }

        std::cout << "Centroids picked!" << std::endl;
    }
    /************************************************************/

    /* Overloaded [] operator */
    template<typename T, int dim>
    T &Cluster<T, dim>::operator[](unsigned int index)
    {
        // TODO: Implement this
        // TODO: Throw OutOfBoundsEx
        // Use forward_list
    }
    /************************************************************/

    /* Overloaded iostream operators (friends) */
    // Allow us to output an entire Cluster
    template<typename T, int dim>
    std::ostream &operator<<(std::ostream &out, const Cluster<T, dim> &right)
    {
        // Output will look like: x, y, z : [Cluster ID]
        std::forward_list<T> list = right.getHead(); // Copy forward list
        auto pos = list.begin();

        // Loop through linked-list
        for (pos; pos != list.end(); pos++)
            out << *pos << " " << Cluster<T, dim>::POINT_CLUSTER_ID_DELIM << " " << right.getID() << std::endl;

        return out;
    }

    // Allow us to input an entire Cluster
    template<typename T, int dim>
    std::istream &operator>>(std::istream &input, Cluster<T, dim> &right)
    {
        std::string line; // Create a new string to read into

        // While we are able to read from input into string
        while (std::getline(input, line, '\n'))
        {
            T pt; // Create new Point

            std::stringstream lineStr(line); // Convert the string line into a stringstream

            try
            {
                // Read values into new Point (uses Point extraction operator)
                lineStr >> pt;

                // Add new Point to the Cluster
                right.add(pt);

                // Increment __ptsSuccess
                right.__ptsSuccess++;
            }
            catch (DimensionalityMismatchEx e)
            {
                right.__ptsFailed++; // Increment __ptsFailed
                std::cout << "In Cluster extraction operator - " << e << std::endl;
            }
            catch (PointAlreadyExistsEx e)
            {
                right.__ptsFailed++; // Increment __ptsFailed
                std::cout << "In Cluster extraction operator - " << e << std::endl;
            }
        }

        return input;
    }
    /************************************************************/

    /* Overloaded comparison operators (friends) */
    // Overloaded equality operator (friend)
    template<typename T, int dim>
    bool operator ==(const Cluster<T, dim> &left, const Cluster<T, dim> &right)
    {
        // Check sizes and heads of Clusters first
        if (left.getSize() != right.getSize() || left.getHead() != right.getHead())
        {
            return false;
        }
        else
        {
            // Copy forward lists
            std::forward_list<T> list1 = left.getHead();
            std::forward_list<T> list2 = right.getHead();
            auto pos1 = list1.begin();
            auto pos2 = list2.begin();

            // Loop through lists of both Clusters
            while (pos1 != list1.end() && pos2 != list2.end())
            {
                // Check if Points are equal
                try
                {
                    if (*pos1 == *pos2)
                    {
                        pos1++;
                        pos2++;
                    }
                    else
                        return false;
                }
                catch (DimensionalityMismatchEx e) { std::cout << "In Cluster == operator - " << e << std::endl; }
            }

            return true; // If while loop terminates without returning false
        }
    }

    // Overloaded inequality operator
    template<typename T, int dim>
    bool operator !=(const Cluster<T, dim> &left, const Cluster<T, dim> &right)
    {
        return !(left == right);
    }
    /************************************************************/

    /* Overloaded compound assignment operators (members) */
    // Combines two Clusters into one (union)
    template<typename T, int dim>
    Cluster<T, dim> &Cluster<T, dim>::operator +=(const Cluster<T, dim> &right)
    {
        __validCentroid = false; // Invalidate Centroid
        *this = *this + right; // Add right Cluster to left Cluster
        return *this;
    }

    // Subtracts one Cluster from referenced Cluster
    template<typename T, int dim>
    Cluster<T, dim> &Cluster<T, dim>::operator -=(const Cluster<T, dim> &right)
    {
        __validCentroid = false; // Invalidate Centroid
        *this = *this - right; // Subtract right Cluster from left Cluster
        return *this;
    }

    // Add a Point to referenced Cluster
    template<typename T, int dim>
    Cluster<T, dim> &Cluster<T, dim>::operator +=(const T &right)
    {
        try { this->add(right); }
        catch (PointAlreadyExistsEx e) { std::cout << "In Cluster += operator - " << e << std::endl; }
        return *this;
    }

    // Remove a Point from referenced Cluster
    template<typename T, int dim>
    Cluster<T, dim> &Cluster<T, dim>::operator -=(const T &right)
    {
        try { this->remove(right); }
        catch (RemoveFromEmptyEx e) { std::cout << e << std::endl; }
        return *this;
    }
    /************************************************************/

    /* Overloaded binary arithmetic operators (friends) */
    // Add two Clusters together
    template<typename T, int dim>
    const Cluster<T, dim> operator +(const Cluster<T, dim> &left, const Cluster<T, dim> &right)
    {
        Cluster<T, dim> c(left); // Copy left Cluster

        std::forward_list<T> list = right.getHead(); // Copy right Cluster forward_list
        auto pos = list.begin();

        // Loop through list and add Points to new Cluster
        for (pos; pos != list.end(); pos++)
            c += *pos;

        return c;
    }

    // Subtract one Cluster from another
    template<typename T, int dim>
    const Cluster<T, dim> operator -(const Cluster<T, dim> &left, const Cluster<T, dim> &right)
    {
        Cluster<T, dim> c(left); // Copy left Cluster

        std::forward_list<T> list = right.getHead(); // Copy right Cluster forward_list
        auto pos = list.begin();

        // Loop through list and remove Points from new Cluster
        for (pos; pos != list.end(); pos++)
            c -= *pos;

        return c;
    }

    // Add a Point to a Cluster
    template<typename T, int dim>
    const Cluster<T, dim> operator +(const Cluster<T, dim> &left, const T &right)
    {
        Cluster<T, dim> c(left); // Copy left Cluster

        c += right; // Add Point to Cluster

        return c;
    }

    // Subtract a Point from a Cluster
    template<typename T, int dim>
    const Cluster<T, dim> operator -(const Cluster<T, dim> &left, const T &right)
    {
        Cluster<T, dim> c(left); // Copy left Cluster

        c -= right; // Remove Point from Cluster

        return c;
    }
    /************************************************************/

} // end Clustering namespace
#endif //CLUSTERING_CLUSTER_H


/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/


///* NON-TEMPLATE CLUSTER CLASS */
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
//            Move(const Point &p, Cluster *from, Cluster *to) :
//                    __p(p),
//                    __from(from),
//                    __to(to) { perform(); }
//
//            ~Move() { }
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
//                __ptsFailed(0) { }
//
//        // Takes dimensions for use in Point constructors
//        Cluster(unsigned long int numDims) :
//                __id(__idGenerator++),
//                __size(0),
//                __numDimensions(numDims),
//                __centroid(__numDimensions),
//                __validCentroid(false),
//                __ptsSuccess(0),
//                __ptsFailed(0) { }
//
//        // Copy constructor
//        Cluster(const Cluster &right) :
//                __id(right.getID()),
//                __size(right.getSize()),
//                __head(right.getHead()),
//                __numDimensions(right.getNumDimensions()),
//                __centroid(right.getCentroid()),
//                __validCentroid(right.getCentroidValidity()) { }
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
//        bool contains(const Point &);
//        unsigned int numberImported() { return __ptsSuccess; }
//        unsigned int numberFailed() { return __ptsFailed; }
//        /************************************************************/
//
//        /* KMeans computeClusteringScore functions */
//        double intraClusterDistance() const; // Sum of distances between Points in Cluster
//        friend double interClusterDistance(const Cluster &, const Cluster &, const std::unordered_map<Key, double, KeyHash, KeyEqual>);
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
//} // end Clustering namespace
//#endif //CLUSTERING_CLUSTER_H