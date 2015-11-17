// Programming Assignment 4 - KMeans Clustering

// Author:      Dylan Lang
// Date:        28 October 2015

// Cluster class implementation

#include "Cluster.h"
#include "Exceptions.h"

/* namespace wrap */
namespace Clustering
{
    /* Member variables */
    unsigned int Cluster::__idGenerator = 1; // Initialize Cluster ID value to 1
    const char Cluster::POINT_CLUSTER_ID_DELIM = ':'; // Set Cluster delimiter for output
    /************************************************************/

    /* Inner Move Class */
    // Move member functions
    void Cluster::Move::perform()
    {
        // TODO: Catch RemoveFromEmpty exception
        // Remove Point from Cluster and add to another Cluster
        try
        {
            __to->add(__from->remove(__p));
        }
        catch(RemoveFromEmptyEx e)
        {
            std::cerr << "In Move.perform method - " << e << std::endl;
        }
        catch (PointAlreadyExistsEx e)
        {
            std::cerr << "in Move.perform method - " << e << std::endl;
        }
    }
    /************************************************************/

    /* Overloaded assignment operator (Cluster) */
    Cluster &Cluster::operator =(const Cluster &right)
    {
        // Copy all values from right into left and return
        __id = right.getID();
        __size = right.getSize();

        // Copy __head
        __head.clear();
        __head = right.getHead();

        __numDimensions = right.getNumDimensions();
        __centroid = right.getCentroid();
        __validCentroid = right.getCentroidValidity();

        return *this;
    }
    /************************************************************/

    /* Setters */
    // Set the Centroid of a Cluster
    void Cluster::setCentroid(const Point &right)
    {
        // Set Cluster's Centroid equal to new Centroid
        __centroid = right;

        // Re-validate Centroid
        __validCentroid = true;
    }

    // Calculate distances between Points within Cluster and store in map
    void Cluster::setDistanceMap()
    {
        // Display message
        std::cout << "Calculating __distances map!" << std::endl;

        // Copy __head of Cluster
        std::forward_list<Point> list = this->getHead();

        // Loop through Points in Cluster forward_list
        for (auto it_1 = list.begin(); it_1 != list.end(); ++it_1)
        {
            auto it_2 = it_1;
            ++it_2; // Offset second iterator to avoid repeating Points

            for (it_2; it_2 != list.end(); ++it_2)
            {
                // Create a key
//                Key key(*it_1, *it_2); // TODO: Remove this
                Key key(it_1->getID(), it_2->getID());

                // Attempt to find key
                auto search = __distances.find(key);

                // If search reaches end of __distances map, add value to map
                if (search == __distances.end())
                    __distances[key] = it_1->distanceTo(*it_2);
            }
        }

        // Uncomment to display map
        std::cout << "__distances map:" << std::endl;

        for (auto pos = __distances.begin(); pos != __distances.end(); ++pos)
        {
            std::cout << "{{" << pos->first.__first << ", " << pos->first.__second
            << "}," << pos->second << "}" << std::endl;
        }
        std::cout << std::endl;
    }
    /************************************************************/

    /* Cluster member functions */
    // Add Point to Cluster
    void Cluster::add(const Point &right)
    {
        // Invalidate Centroid
        __validCentroid = false;

        // Add Point to empty forward list
        if (__head.empty())
        {
            __head.emplace_front(Point(right));
        }
        else if (this->contains(right))
        {
            // If Point is already in Cluster
            // Decrement __idGenerator
            right.rewindIdGen();

            throw PointAlreadyExistsEx(right);
        }
        else
        {
            // Place Point in list
            __head.emplace_front(Point(right));
        }

        // Increment size of Cluster
        __size++;

        // Sort forward_list
        this->sort();

        // Uncomment to display added Points
//        std::cout << "Point " << right.getID() << ": " << right
//        << " added to Cluster " << this->getID() << "!" << std::endl;
    }

    // Remove Point from Cluster; returns removed Point
    const Point &Cluster::remove(const Point &right)
    {
        // Invalidate Centroid
        __validCentroid = false;

        // Case 1 - remove Point from empty forward list
        // TODO: Throw RemoveFromEmpty exception
        if (__head.empty())
        {
            throw RemoveFromEmptyEx(right.getID(), this->getID());
        }

        // Case 2 - if Point exists, remove it
        else if (this->contains(right))
        {
            __head.remove(right);
            __size--;
        }
        else
        {
            // TODO: Throw PointNotFoundEx?
            std::cout << "Point not found!" << std::endl;
        }

        // Uncomment to display remove message
//        std::cout << "Point " << right.getID() << ": " << right
//        << " removed from Cluster " << this->getID() << std::endl;
        return right;
    }

    // Sort Cluster forward_list
    void Cluster::sort()
    {
        // Uses std::forward_list function sort()
        __head.sort();
    }

    // Check if Cluster already contains Point
    bool Cluster::contains(const Point &p)
    {
        // Copy forward_list
        std::forward_list<Point> list = this->getHead();

        // Create iterator
        std::forward_list<Point>::iterator pos = list.begin();

        // Loop through all Points in Cluster
        for (pos; pos != list.end(); pos++)
        {
            try
            {
                if (*pos == p)
                {
                    return true;
                }
            }
            catch (DimensionalityMismatchEx e)
            {
                std::cerr << "In contains method - " << e << std::endl;
            }
        }

        // If loop terminates without returning true
        return false;
    }
    /************************************************************/

    /* KMeans computeClusteringScore functions */
    // Distance between Points within a single Cluster
    double Cluster::intraClusterDistance(const std::unordered_map<Key, double, KeyHash, KeyEqual>& distances) const
    {
        // Initialize sum
        double sum = 0;

        // Copy forward list
        std::forward_list<Point> list = this->getHead();

        // List iterators
        std::forward_list<Point>::iterator pos = list.begin();
        std::forward_list<Point>::iterator nxt = list.begin();

        // Double loop through linked-list of Cluster
        for (pos; pos != list.end(); pos++)
        {
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
                    auto search1 = distances.find(*key1);
                    auto search2 = distances.find(*key2);

                    // If it does, add distance to sum
                    if (search1 != distances.end())
                        sum += distances.at(*key1);

                    else if (search2 != distances.end())
                        sum += distances.at(*key2);

                    else
                        sum += pos->distanceTo(*nxt);

                    delete key1;
                    delete key2;
                }
            }
        }
        // Divide sum by two since we looped through twice
        sum /= 2.0;

        // Uncomment to display sum
//        std::cout << "Cluster " << this->getID() << " intraClusterDistance: " << sum << std::endl;
        return sum;
    }

    // Returns sum of distance between Points between all Clusters
    double interClusterDistance(const Cluster &c1, const Cluster &c2, const std::unordered_map<Key, double, KeyHash, KeyEqual>& distances)
    {
        // Check if Clusters equal each other
        if (c1 == c2)
            return 0;

        // Initialize sum
        double sum = 0;

        // Copy forward lists
        std::forward_list<Point> list1 = c1.getHead();
        std::forward_list<Point> list2 = c2.getHead();

        // Create iterators
        std::forward_list<Point>::iterator pos1 = list1.begin();
        std::forward_list<Point>::iterator pos2 = list2.begin();

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
                        sum += distances.at(*key1);

                    else if (search2 != distances.end())
                        sum += distances.at(*key2);

                    else
                        sum += pos1->distanceTo(*pos2);

                    delete key1;
                    delete key2;
                }
            }
        }

        // Divide sum by 2 since we looped through both lists twice
        sum /= 2.0;

        // Uncomment to display sum
//        std::cout << "Clusters " << c1.getID() << " and " << c2.getID() << " interClusterDistance: " << sum << std::endl;
        return sum;
    }

    // Returns the number of distinct edges in a Cluster
    int Cluster::getClusterEdges()
    {
        // Every two distinct Points has an imaginary edge between them
        int clusterSize = getSize();
        int result = clusterSize * (clusterSize - 1) / 2;

        // Uncomment to display result
//        std::cout << "Cluster " << this->getID() << " intraClusterEdges: " << result << std::endl;
        return result;
    }

    // Returns the number of distinct edges between Clusters
    int interClusterEdges(const Cluster &c1, const Cluster &c2)
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
    void Cluster::calcCentroid()
    {
        // Copy forward list
        std::forward_list<Point> list = this->getHead();

        // Create iterator
        std::forward_list<Point>::iterator first = list.begin();
        std::forward_list<Point>::iterator pos = list.begin();

        // Create new Point
        Point newCent(this->getNumDimensions());

        // Check if list is empty
        // TODO: Throw RemoveFromEmptyEx
        if (__head.empty() && this->getSize() <= 0)
        {
            this->setCentroid(newCent);
            throw RemoveFromEmptyEx(0, this->getID());
        }
        else if (this->getSize() == 1)
        {
            this->setCentroid(*first);
        }
        else
        {
            // Loop through Points in list and add to newCent
            for (pos; pos != list.end(); pos++)
            {
                newCent += *pos;
            }

            // Divide sum of all Points in Cluster by size of Cluster
            newCent /= this->getSize();

            // Set the Centroid
            this->setCentroid(newCent);
        }
    }

    // Pick k Points from a Cluster to use as initial Centroids for Clustering
    void Cluster::pickPoints(unsigned long int k, unsigned long int dims, Point **pointArray)
    {
        // Display message
        std::cout << "Picking Points to use as Centroids..." << std::endl;

        // Copy k
        unsigned long int kCopy = k;

        // Check if kCopy is greater than the amount of Points in the Cluster
        if (kCopy > this->getSize())
            kCopy = (unsigned long int) this->getSize();

        // Divide Cluster size by how many Centroids we want
        unsigned long int div = this->getSize() / kCopy; // This is what we'll increment count by
        int count = 0; // Used to increment list position

        // Copy forward list
        std::forward_list<Point> list = this->getHead();

        // Iterate kCopy times to get kCopy Centroids
        for (int i = 0; i < k; i++)
        {
            if (i < this->getSize())
            {
                // Set iterator to the beginning of the list
                std::forward_list<Point>::iterator pos = list.begin();

                // Use count to iterate through the list to find the Point we want
                for (int j = 0; j < count; j++)
                {
                    // Iterate through list
                    pos++;
                }

                // Copy current Point
                Point *p1 = new Point(*pos);

                // Put the chosen Point into the Centroid array
                pointArray[i] = p1;

                // Increment count by the value of div
                count += div;
            }
            else
            {
                // Create new Point
                Point *p2 = new Point(dims);

                // Put empty Point into Centroid array
                pointArray[i] = p2;
            }
        }

        std::cout << "Centroids picked!" << std::endl;
    }
    /************************************************************/

    /* Overloaded [] operator */
    Point &Cluster::operator[](unsigned int index)
    {
        // TODO: Implement this
        // TODO: Throw OutOfBoundsEx
    }
    /************************************************************/

    /* Overloaded iostream operators (friends) */
    // Allow us to output an entire Cluster
    std::ostream &operator <<(std::ostream &out, const Cluster &right)
    {
        // Output will look like: x, y, z : [Cluster ID]

        // Copy forward list
        std::forward_list<Point> list = right.getHead();

        // Create iterator
        std::forward_list<Point>::iterator pos = list.begin();

        // Loop through linked-list
        for (pos; pos != list.end(); pos++)
        {
            // Output results
            out << *pos << " " << Cluster::POINT_CLUSTER_ID_DELIM << " " << right.getID() << std::endl;
        }

        return out;
    }

    // Allow us to input an entire Cluster
    std::istream &operator >>(std::istream &input, Cluster &right)
    {
        // TODO: check for proper input formatting (x,y,z,,)
        // Create a new string to read into
        std::string line;
        unsigned long int numDims = right.getNumDimensions();

        // While we are able to read from input into string
        while (std::getline(input, line, '\n'))
        {
            // Create new Point
            Point pt(numDims);

            // Convert the string line into a stringstream
            std::stringstream lineStr(line);

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
                // Increment __ptsFailed
                right.__ptsFailed++;

                // Display the error
                std::cerr << "In Cluster insertion operator - " << e << std::endl;
            }
            catch (PointAlreadyExistsEx e)
            {
                // Increment __ptsFailed
                right.__ptsFailed++;

                // Display the error
                std::cerr << "In Cluster insertion operator - " << e << std::endl;
            }
        }

        return input;
    }
    /************************************************************/

    /* Overloaded comparison operators (friends) */
    // Overloaded equality operator (friend)
    bool operator ==(const Cluster &left, const Cluster &right)
    {
        // Check sizes and heads of Clusters first
        if (left.getSize() != right.getSize() || left.getHead() != right.getHead())
        {
            return false;
        }
        else {
            // Copy forward lists
            std::forward_list<Point> list1 = left.getHead();
            std::forward_list<Point> list2 = right.getHead();

            // Create iterators
            std::forward_list<Point>::iterator pos1 = list1.begin();
            std::forward_list<Point>::iterator pos2 = list2.begin();

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
                    {
                        return false;
                    }
                }
                catch (DimensionalityMismatchEx e)
                {
                    std::cerr << "In Cluster == operator - " << e << std::endl;
                }
            }

            // If while loop terminates without returning false
            return true;
        }
    }

    // Overloaded inequality operator
    bool operator!=(const Cluster &left, const Cluster &right)
    {
        return !(left == right);
    }
    /************************************************************/

    /* Overloaded compound assignment operators (members) */
    // Combines two Clusters into one (union)
    Cluster &Cluster::operator +=(const Cluster &right)
    {
        // Invalidate Centroid
        __validCentroid = false;

        // Add right Cluster to left Cluster and return
        *this = *this + right;
        return *this;
    }

    // Subtracts one Cluster from referenced Cluster
    Cluster &Cluster::operator -=(const Cluster &right)
    {
        // Invalidate Centroid
        __validCentroid = false;

        // Subtract right Cluster from left Cluster and return
        *this = *this - right;
        return *this;
    }

    // Add a Point to referenced Cluster
    Cluster &Cluster::operator +=(const Point &right)
    {
        try
        {
            this->add(right);
        }
        catch (PointAlreadyExistsEx e)
        {
            std::cerr << "In Cluster += operator - " << e << std::endl;
        }
        return *this;
    }

    // Remove a Point from referenced Cluster
    Cluster &Cluster::operator -=(const Point &right)
    {
        try
        {
            this->remove(right);
        }
        catch(RemoveFromEmptyEx e)
        {
            std::cout << e << std::endl;
        }

        return *this;
    }
    /************************************************************/

    /* Overloaded binary arithmetic operators (friends) */
    // Add two Clusters together
    const Cluster operator +(const Cluster &left, const Cluster &right)
    {
        // Create new Cluster equal to left-hand-side
        Cluster c(left);

        // Copy right-hand-side forward list
        std::forward_list<Point> list = right.getHead();

        // Create iterator
        std::forward_list<Point>::iterator pos = list.begin();

        // Loop through list and add Points to new Cluster
        for (pos; pos != list.end(); pos++)
        {
            c += *pos;
        }

        return c;
    }

    // Subtract one Cluster from another
    const Cluster operator -(const Cluster &left, const Cluster &right)
    {
        // Create new Cluster equal to left-hand-side
        Cluster c(left);

        // Copy right-hand-side forward list
        std::forward_list<Point> list = right.getHead();

        // Create iterator
        std::forward_list<Point>::iterator pos = list.begin();

        // Loop through list and remove Points from new Cluster
        for (pos; pos != list.end(); pos++)
        {
            c -= *pos;
        }

        return c;
    }

    // Add a Point to a Cluster
    const Cluster operator +(const Cluster &left, const Point &right)
    {
        // Copy left-hand-side
        Cluster c(left);

        // Add Point to Cluster
        c += right;

        return c;
    }

    // Subtract a Point from a Cluster
    const Cluster operator -(const Cluster &left, const Point &right)
    {
        // Copy left-hand-side
        Cluster c(left);

        // Remove Point from Cluster
        c -= right;

        return c;
    }
    /************************************************************/
} // end namespace Clustering
