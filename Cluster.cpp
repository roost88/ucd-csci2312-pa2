// Programming Assignment 3 - KMeans Clustering

// Author:      Dylan Lang
// Date:        6 October 2015

// Cluster class implementation

#include "Cluster.h"

// namespace wrap
namespace Clustering
{
    // Member variables
    unsigned int Cluster::__idGenerator = 0; // Initialize Cluster ID value to 1
    const char Cluster::POINT_CLUSTER_ID_DELIM = ':'; // Set Cluster delimiter for output

    // Cluster Constructors
    Cluster::Cluster()
    {
        __id = Cluster::__idGenerator++; // Increment ID with each new Cluster
        __size = 0; // Initialize size to 0 (empty Cluster)
        __head = nullptr; // head doesn't point to anything yet
        __numDimensions = 0; // There are no Points in the Cluster
        __centroid = nullptr; // The Cluster has no Centroid
        __validCentroid = false; // Invalid Centroid
    }

    Cluster::Cluster(int numDims)
    {
        __id = Cluster::__idGenerator++; // Increment ID with each new Cluster
        __size = 0; // Initialize size to 0 (empty Cluster)
        __head = nullptr; // head doesn't point to anything yet
        __numDimensions = numDims; // There are no Points in the Cluster
        __centroid = nullptr; // The Cluster has no Centroid
        __validCentroid = false; // Invalid Centroid
    }

    // Cluster copy constructor
    Cluster::Cluster(const Cluster &right)
    {
        // Copy all values from right into left Cluster
        __id = Cluster::__idGenerator++;;
        __size = right.__size;
        __head = deepCopy(right.__head);
        __numDimensions = right.__numDimensions;
        __centroid = right.__centroid;
        __validCentroid = right.__validCentroid;
    }

    // Overloaded assignment operator (Cluster)
    Cluster &Cluster::operator=(const Cluster &right)
    {
        // Copy all values from right into left and return
        __id = Cluster::__idGenerator++;;
        __size = right.__size;
        __head = deepCopy(right.__head);
        __numDimensions = right.__numDimensions;
        __centroid = right.__centroid;
        __validCentroid = right.__validCentroid;
        return *this;
    }

    // Cluster destructor
    Cluster::~Cluster()
    {
        int id = getID();

        if (__size != 0)
        {
            ListNodePtr current = __head;
            delete current;
        }
        __head = nullptr;
        __size = 0;
        std::cout << "Cluster " << id << " destroyed!" << std::endl;
    }
    // ******************************************

    // Move constructor
    Cluster::Move::Move(const PointPtr &ptr, Cluster *from, Cluster *to)
    {
        perform(ptr, from, to);
    }

    // Move member functions
    void Cluster::Move::perform(const PointPtr &ptr, Cluster *from, Cluster *to)
    {
        // Remove Point from Cluster and add to another Cluster
        to->add(from->remove(ptr));
        std::cout << "Performing move!" << std::endl;
    }

    // ******************************************

    // Cluster member functions
    // Copy function
    ListNodePtr Cluster::deepCopy(ListNodePtr hd)
    {
        // Set current equal to ListNodePtr passed in
        ListNodePtr current = hd;

        // Create two empty heads
        ListNodePtr newHd = nullptr;
        ListNodePtr previous = nullptr;

        // Loop through linked-list
        while (current != nullptr)
        {
            // 1st iteration
            if (newHd == nullptr)
            {
                // Create a new Node and copy in left hand values
                ListNodePtr newNode = new ListNode(current->p, newHd);

                // Set newHd to point to new Node
                newHd = newNode;

                // Copy newHd into previous pointer
                previous = newHd;
            }
            // Remaining iterations
            else
            {
                // Create new Node and copy in next left hand values
                ListNodePtr newNode = new ListNode(current->p, previous->next);

                // Set next Node equal to new Node
                previous->next = newNode;

                // Increment previous pointer
                previous = previous->next;
            }

            // Increment current pointer
            current = current->next;
        }
        return newHd;
    }

    // Compute the Centroid of a Cluster
    void Cluster::calcCentroid()
    {
        // Copy Cluster
        ClusterPtr c1 = new Cluster(*this);
        ListNodePtr current = c1->getHead();

        // Create a new Point
        Point newCent(__numDimensions);

        if (__size == 1)
        {
            newCent = *current->p;
            setCentroid(newCent);
        }
        else if (__size > 1)
        {
            while (current != nullptr)
            {
                newCent += *current->p;
                current = current->next;
            }

            // Divide the sum of all Points by the size of the Cluster
            newCent = newCent / getSize();

            // Set the Centroid
            setCentroid(newCent);
        }
    }

    // Set the Centroid of a Cluster
    void Cluster::setCentroid(const Point &right)
    {
        // Create a new Centroid
        PointPtr newCentroid = new Point(right);

        // Set Cluster's Centroid equal to new Centroid
        __centroid = newCentroid;

        // Re-validate Centroid
        __validCentroid = true;
    }

    // Set Point dimensions of Cluster
    void Cluster::setDimensions(int numDims)
    {
        __numDimensions = numDims;
    }


    // Add Point straight to Cluster in lexicographic order
    void Cluster::add(const PointPtr &right)
    {
        if (right != nullptr)
        {
            // Invalidate Centroid
            __validCentroid = false;

            // Create a new Node and copy right values
            ListNodePtr newNode = new ListNode(right, nullptr);

            // Case 1 - add Point to empty linked list
            if (__head == nullptr)
            {
                // head now points to the new List Node
                __head = newNode;
            }
            else {
                // Copy Cluster head and create NULL pointer
                ListNodePtr current = __head;
                ListNodePtr previous = nullptr;

                // Loop through linked-list to find insertion point
                while (current != nullptr)
                {
                    // Check Points - If current Point is greater than or equal to
                    if (*current->p > *newNode->p)
                    {
                        // Break out of while loop and go to next case
                        break;
                    }
                    else if (*current->p == *newNode->p)
                    {
                        return;
                    }
                    else
                    {
                        previous = current;
                        current = current->next;
                    }
                }

                // Case 2 - insert at head (linked-list not empty)
                if (current == __head)
                {
                    newNode->next = __head;
                    __head = newNode;
                }
                    // Case 3 - insert somewhere after the head (linked-list not empty)
                else
                {
                    newNode->next = current;
                    previous->next = newNode;
                }
            }
            // Increment size of Cluster
            __size++;
        }
    }

    // Remove Point from Cluster
    // Will return the removed Point so we can add it to another Cluster
    const PointPtr &Cluster::remove(const PointPtr &right)
    {
        // Invalidate Centroid
        __validCentroid = false;

        // Case 1 - remove Point from empty linked list
        if (__head == nullptr)
        {
            std::cout << "Point cannot be deleted from an empty Cluster!" << std::endl;
            return nullptr;
        }
        else
        {
            // Copy head into current
            ListNodePtr current = __head;
            ListNodePtr previous = nullptr;

            // Loop through linked-list to find Point
            while (current != nullptr)
            {
                // If Points are equal, break out of loop
                if (*current->p == *right)
                {
                    break;
                }
                else
                {
                    // Iterate while loop
                    previous = current;
                    current = current->next;
                }
            }

            // Case 2 - Point not found in Cluster linked list
            if (current == nullptr)
            {
                std::cout << "Point " << *right << " was not found in the Cluster!" << std::endl;
                return nullptr;
            }
            else
            {
                // Case 3 - delete the head node
                if (__head == current)
                {
                    // Isolate node to be deleted
                    __head = __head->next;
                }
                // Case 4 - delete from beyond head node
                else
                {
                    previous->next = current->next;
                }
                // delete Point from Cluster
                delete current;

                // Decrement size
                __size--;

                std::cout << "Point " << *right << " successfully removed!" << std::endl;
            }
        }
        return right;
    }

    double Cluster::intraClusterDistance() const
    {
        // Inside Cluster distance between Points

        double sum = 0; // Initialize sum

        // Double loop through linked-list of Cluster
        for (ListNodePtr curr = __head; curr != nullptr; curr = curr->next)
        {
            for (ListNodePtr nxt = __head; nxt != nullptr; nxt = nxt->next)
            {
                // Calculate distance between Points and add to sum
                sum += curr->p->distanceTo(*nxt->p);
            }
        }
        // Divide sum by two since we looped through twice and return
        sum /= 2.0;
        return sum;
    }

    double interClusterDistance(const Cluster &c1, const Cluster &c2)
    {
        // Between Clusters distance between Points

        double sum = 0; // Initialize sum

        // Loop through linked-lists of both Clusters
        for (ListNodePtr right = c1.__head; right != nullptr; right = right->next)
        {
            for (ListNodePtr left = c2.__head; left != nullptr; left = left->next)
            {
                // Calculate distance between Points and add to sum
                sum += right->p->distanceTo(*left->p);
            }
        }
        // Divide sum by 2 since we looped through both lists twice and return
        sum /= 2.0;
        return sum;
    }

    int Cluster::getClusterEdges()
    {
        // Returns the number of distinct edges in a Cluster
        // Every two distinct Points has an imaginary edge between them
        // It's length is the distance between the two Points
        int clusterSize = getSize();
        int numEdges = clusterSize * (clusterSize - 1) / 2;
        return numEdges;
    }

    void Cluster::pickPoints(int k, PointPtr *pointArray)
    {
        // Pick k Points from a Cluster to use as initial Centroids for Clustering
        // Store k Points into an array

        // Divide Cluster size by how many Centroids we want
        int div = getSize() / k; // This is what we'll increment count by
        int count = 0;

        // Iterate k times to get k Centroids
        for (int i = 0; i < k; i++)
        {
            // Set current to the beginning of the lis
            ListNodePtr current = __head;

            // Use count to iterate through the list to find the Point we want
            for (int j = 0; j < count; j++)
            {
                // Iterate through list
                current = current->next;
            }
            // Copy current Point
            PointPtr pt = new Point(*current->p);

            // Write the Point we chose into the Centroid array
            pointArray[i] = pt;

            // Increment count by the value of div
            count += div;
        }
    }
    // ******************************************

    // Overloaded iostream operators
    // Allow us to output an entire Cluster
    std::ostream &operator<<(std::ostream &out, const Cluster &right)
    {
        // Output will look like: x, y, z : [Cluster ID]

        // Loop through linked-list
        for (ListNodePtr current = right.__head; current != nullptr; current = current->next)
        {
            // Set point equal to current Point
            PointPtr point = current->p;

            // Output results
            out << *point << " " << Cluster::POINT_CLUSTER_ID_DELIM << " " << right.__id << std::endl;
        }
        return out;
    }

    // Allow us to input an entire Cluster
    std::istream &operator>>(std::istream &input, Cluster &right)
    {
        // Create a new string to read into
        std::string line;

        // While we are able to read from input into string
        while (std::getline(input, line, '\n'))
        {
            // Count number of commas in the line
            int num_com = (std::count(line.begin(), line.end(), Clustering::Point::POINT_VALUE_DELIM));

            // Add one to number of commas to use as Point dimensions
            num_com += 1;

            // Check each line of input for proper dimensions
            if (num_com == right.__numDimensions)
            {
                // Create a new Point with dimensions equal to num_com
                Clustering::PointPtr pt = new Clustering::Point(num_com);

                // Convert the string line into a stringstream
                std::stringstream lineStr(line);

                // Read values into new Point (uses Point extraction operator)
                lineStr >> *pt;

                // Add new Point to the Cluster
                right.add(pt);
            }
        }
        return input;
    }
    // ******************************************

    // Overloaded assignment operator (friend)
    bool operator==(const Cluster &left, const Cluster &right)
    {
        // Check sizes and heads of Clusters first
        if (left.__size != right.__size || left.__head != right.__head)
        {
            return false;
        }
        else
        {
            // Copy head pointers
            ListNodePtr leftHead = left.__head;
            ListNodePtr rightHead = right.__head;

            // Loop through linked-lists of both Clusters
            while (leftHead != nullptr && rightHead != nullptr)
            {
                // Check if Points are equal
                if (leftHead->p == rightHead->p)
                {
                    // Increment both Clusters
                    leftHead = leftHead->next;
                    rightHead = rightHead->next;
                }
                else
                {
                    return false;
                }
            }
            // If while loop terminates without returning false, return true
            return true;
        }
    }

    bool operator!=(const Cluster &left, const Cluster &right)
    {
        return !(left == right);
    }
    // ******************************************

    // Overloaded compound assignment operators (members)
    // Combines two Clusters into one (union)
    Cluster &Cluster::operator+=(const Cluster &right)
    {
        // Invalidate Centroid
        __validCentroid = false;

        // Add right Cluster to left Cluster and return
        *this = *this + right;
        return *this;
    }

    // Subtracts one Cluster from referenced Cluster
    Cluster &Cluster::operator-=(const Cluster &right)
    {
        // Invalidate Centroid
        __validCentroid = false;

        // Subtract right Cluster from left Cluster and return
        *this = *this - right;
        return *this;
    }

    // Add a Point to referenced Cluster
    Cluster &Cluster::operator+=(const Point &right)
    {
        // Invalidate Centroid
        __validCentroid = false;

        // Copy head pointer
        ListNodePtr leftHead = __head;

        // Create a dynamic Point using right
        PointPtr pt = new Point(right);

        // Create a new ListNode using pt
        ListNodePtr newNode = new ListNode(pt, nullptr);

        // Look through linked-list
        while (leftHead != nullptr)
        {
            if (*leftHead->p != right)
            {
                leftHead = leftHead->next;
            }
            else
            {
                // Display error message and return
                std::cout << "Cluster already contains Point " << right << " !" << std::endl;
                return *this;
            }
        }

        // If while loop terminates without returning, add Point to Cluster and return
        add(newNode->p);
        delete newNode;
        return *this;
    }

    // Remove a Point from referenced Cluster
    Cluster &Cluster::operator-=(const Point &right)
    {
        // Invalidate Centroid
        __validCentroid = false;

        // Copy head pointer
        ListNodePtr leftHead = __head;

        // Create a dynamic Point using right
        PointPtr pt = new Point(right);

        // Create a new ListNode using pt
        ListNodePtr newNode = new ListNode(pt, nullptr);

        // Loop through linked-list
        while (leftHead != nullptr)
        {
            // If Point is found in Cluster
            if (*leftHead->p == *newNode->p)
            {
                remove(newNode->p);
                break;
            }
            else
            {
                leftHead = leftHead->next;
            }
        }

        // Delete dynamic objects and return
        delete pt;
        delete newNode;
        return *this;
    }
    // ******************************************

    // Overloaded binary arithmetic operators (friends)
    // Add two Clusters together
    const Cluster operator+(const Cluster &left, const Cluster &right)
    {
        // Create a new Cluster that is equal to left-hand Cluster
        Cluster *newLeft = new Cluster(left);

        ListNodePtr rightHead = right.__head;

        for (; rightHead != nullptr; rightHead = rightHead->next)
        {
            *newLeft += *rightHead->p;
        }

        // Copy result
        Cluster result(*newLeft);

        delete newLeft;

        // Return new Cluster
        return result;
    }

    // Subtract one Cluster from another
    const Cluster operator-(const Cluster &left, const Cluster &right)
    {
        // Create a new Cluster that is equal to left-hand Cluster
        Cluster *newLeft = new Cluster(left);
        Cluster *newRight = new Cluster(right);

        ListNodePtr rightHead = newRight->__head;

        for (; rightHead != nullptr; rightHead = rightHead->next)
        {
            newLeft->remove(rightHead->p);
        }

        // Copy result
        Cluster result(*newLeft);

        delete newLeft;
        delete newRight;

        // Return new Cluster
        return result;
    }

    // Add a Point to a Cluster
    const Cluster operator+(const Cluster &left, const PointPtr &right)
    {
        // Copy Cluster
        Cluster *newCluster = new Cluster(left);

        // Add the Point
        newCluster->add(right);

        // Copy the result
        Cluster result(*newCluster);

        delete newCluster;

        // Return the new Cluster
        return result;
    }

    // Subtract a Point from a Cluster
    const Cluster operator-(const Cluster &left, const PointPtr &right)
    {
        // Copy Cluster
        Cluster *newCluster = new Cluster(left);

        // Remove the Point
        *newCluster -= *right;

        // Copy result
        Cluster result(*newCluster);

        delete newCluster;

        // Return the new Cluster
        return result;
    }
} // end namespace Clustering
