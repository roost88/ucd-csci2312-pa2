// Programming Assignment 2 - Three Dimensional Triangle

// Author:      Dylan Lang
// Date:        10 Sept 2015

// Cluster class implementation

#include <iostream>
#include "Cluster.h"

// namespace wrap
namespace Clustering
{
// Constructors
    // Default constructor - initializes size to 0 and "points" points to nothing
    Cluster::Cluster()
    {
        size = 0;
        head = nullptr;
    }

    // Copy constructor
    Cluster::Cluster(const Cluster &right)
    {
        size = right.size;
        head = deepCopy(right.head);
    }

    // Overloaded assignment operator
    Cluster &Cluster::operator =(const Cluster &right)
    {
        size = right.size;
        head = deepCopy(right.head);
    }

    // Destructor
    Cluster::~Cluster()
    {
        ListNodePtr ptr = head;
        ListNodePtr temp;

        while (ptr != nullptr)
        {
            temp = ptr->next;
            delete ptr;
            ptr = temp;
        }
    }
// ******************************************
// Member functions
    // Copy function
    ListNodePtr Cluster::deepCopy(ListNodePtr hd)
    {
        ListNodePtr current = hd;
        ListNodePtr newHd = nullptr;
        ListNodePtr previous = nullptr;

        while (current != nullptr)
        {
            if (newHd == nullptr)
            {
                ListNodePtr newNode = new ListNode(current->p, newHd);
                newHd = newNode;
                previous = newHd;
            }
            else
            {
                ListNodePtr newNode = new ListNode(current->p, previous->next);
                previous->next = newNode;
                previous = previous->next;
            }
            current = current->next;
        }

        ListNodePtr result = newHd;

        return result;
    }

// Add Point straight to Cluster in lexicographic order
    void Cluster::add(const PointPtr &right)
    {
        ListNodePtr newNode = new ListNode(right, nullptr);

        // Case 1 - add Point to empty linked list
        if (head == nullptr)
        {
            // head now points to the new List Node
            head = newNode;
        }
        else
        {
            ListNodePtr current = head;
            ListNodePtr previous = nullptr;

            // Traverse list to find insert location
            while (current != nullptr)
            {
                // If the first dereferenced p value in list is greater than the Point we are adding
                if (*(current->p) >= *(newNode->p))
                {
                    // Break out of while loop
                    break;
                }
                // If the first p value in list is less than the Point we are adding
                else
                {
                    previous = current;
                    current = current->next;
                }
            }

            // Case 2 - insert at head (not empty)
            if (current == head)
            {
                newNode->next = head;
                head = newNode;
            }
            else
            {
                // Case 3 - insert after the head (not empty)
                newNode->next = current;
                previous->next = newNode;
            }
        }
        // Increment size
        size++;
    }

// Remove Point from Cluster
// Will return the removed Point so we can add it to another Cluster
    const PointPtr &Cluster::remove(const PointPtr &pt)
    {
        // Case 1 - remove Point from empty linked list
        if (head == nullptr)
        {
            std::cout << "Point cannot be deleted from an empty Cluster!" << std::endl;
            return pt;
        }
        else
        {
            ListNodePtr current = head;
            ListNodePtr previous = nullptr;

            // Traverse list to find Point for deletion
            while (current != nullptr)
            {
                if (*(current->p) == *pt)
                {
                    break;
                }
                else
                {
                    previous = current;
                    current = current->next;
                }
            }

            // Case 2 - Point not found in Cluster linked list
            if (current == nullptr)
            {
                std::cout << "Point " << *pt << " was not found in the Cluster!" << std::endl;
                return pt;
            }
            else
            {
                // Case 3 - delete the head node
                if (head == current)
                {
                    // Isolate node to be deleted
                    head = head->next;
                }
                // Case 4 - delete from beyond head node
                else
                {
                    previous->next = current->next;
                }

                // delete Point from Cluster
                delete current;

                // Decrement size
                size--;

                // Return the deleted Point
                std::cout << "Point " << *pt << " successfully removed!" << std::endl;
                return pt;
            }
        }
    }
// ******************************************

// Overloaded iostream operators
// Allow us to output an entire Cluster
    std::ostream &operator <<(std::ostream &out, const Cluster &right)
    {
        out << "{";

        for (ListNodePtr current = right.head; current != nullptr; current = current->next)
        {
            PointPtr point = current->p;
            out << *point;
        }

        out << "}" << std::endl;
        return out;
    }

// Allow us to input an entire Cluster
    std::istream &operator >>(std::istream &in, Cluster &right)
    {
        // INSERT CODE
    }
// ******************************************

// Overloaded assignment operator (friend)
    bool operator ==(const Cluster &left, const Cluster &right)
    {
        // Check sizes and heads of Clusters first
        if (left.size != right.size || left.head != right.head)
        {
            return false;
        }
        else
        {
            ListNodePtr leftHead = left.head;
            ListNodePtr rightHead = right.head;

            // Traverse the Cluster linked list
            while (leftHead != nullptr && rightHead != nullptr)
            {
                // Check if Points are equal
                if (leftHead->p == rightHead->p)
                {
                    leftHead = leftHead->next;
                    rightHead = rightHead->next;
                    continue;
                }
                else
                {
                    return false;
                }
            }
            return true;
        }
    }

    bool operator !=(const Cluster &left, const Cluster &right)
    {
        return !(left == right);
    }
// ******************************************

// Overloaded compound assignment operators (members)
// Combines two Clusters into one (union)
    Cluster &Cluster::operator +=(const Cluster &right)
    {
        *this = *this + right;
        return *this;
    }

// Subtracts one Cluster from referenced Cluster
    Cluster &Cluster::operator -=(const Cluster &right)
    {
        *this = *this - right;
        return *this;
    }

// Add a Point to referenced Cluster
    Cluster &Cluster::operator +=(const Point &right)
    {
        // Check if Point already exists in Cluster
        // If not, add the Point to the Cluster

        ListNodePtr leftHead = head;

        // Create a dynamic Point using right
        PointPtr pt = new Point(right);

        // Create a new ListNode using pt
        ListNodePtr newNode = new ListNode(pt, nullptr);

        // Traverse linked list
        while (leftHead != nullptr)
        {
            if (*(leftHead->p) != right)
            {
                leftHead = leftHead->next;
            }
            else
            {
                return *this;
            }
        }

        (*this).add(newNode->p);
        delete newNode;
        return *this;
    }

// Remove a Point from referenced Cluster
    Cluster &Cluster::operator -=(const Point &right)
    {
        // Check if Point exists in Cluster
        // If so, remove the Point from the Cluster

        ListNodePtr leftHead = head;

        // Create a dynamic Point using right
        PointPtr pt = new Point(right);

        // Create a new ListNode using pt
        ListNodePtr newNode = new ListNode(pt, nullptr);

        // Traverse linked list
        while (leftHead != nullptr)
        {
            if (*(leftHead->p) == *newNode->p)
            {
                break;
            }
            else
            {
                leftHead = leftHead->next;
            }
        }
        (*this).remove(newNode->p);

        delete pt;
        delete newNode;
        return *this;
    }
// ******************************************

// Overloaded binary arithmetic operators (friends)
// Add two Clusters together
    const Cluster operator +(const Cluster &left, const Cluster &right)
    {
        // Create a new Cluster that is equal to left-hand Cluster
        Cluster *newLeft = new Cluster(left);

        ListNodePtr rightHead = right.head;

        for (; rightHead != nullptr; rightHead = rightHead->next)
        {
            (*newLeft) += *rightHead->p;
        }

        // Copy result
        Cluster result(*newLeft);

        delete newLeft;

        // Return new Cluster
        return result;
    }

// Subtract one Cluster from another
    const Cluster operator -(const Cluster &left, const Cluster &right)
    {
        // Create a new Cluster that is equal to left-hand Cluster
        Cluster *newLeft = new Cluster(left);
        Cluster *newRight = new Cluster(right);

        ListNodePtr rightHead = (*newRight).head;

        for (; rightHead != nullptr; rightHead = rightHead->next)
        {
            (*newLeft).remove(rightHead->p);
        }

        // Copy result
        Cluster result(*newLeft);

        delete newLeft;
        delete newRight;

        // Return new Cluster
        return result;
    }

// Add a Point to a Cluster
    const Cluster operator +(const Cluster &left, const PointPtr &right)
    {
        // Copy Cluster
        Cluster *newCluster = new Cluster(left);

        // Add the Point
        (*newCluster).add(right);

        // Copy the result
        Cluster result(*newCluster);

        delete newCluster;

        // Return the new Cluster
        return result;
    }

// Subtract a Point from a Cluster
    const Cluster operator -(const Cluster &left, const PointPtr &right)
    {
        // Copy Cluster
        Cluster *newCluster = new Cluster(left);

        // Remove the Point
        (*newCluster) -= *right;

        // Copy result
        Cluster result(*newCluster);

        delete newCluster;

        // Return the new Cluster
        return result;
    }
} // end namespace Clustering
