// Programming Assignment 4 - KMeans Clustering

// Author:      Dylan Lang
// Date:        28 October 2015

#include <iostream>
#include <fstream>
#include "Point.h"
#include "Cluster.h"
#include "KMeans.h"

// TODO: Create Testing .h and .cpp files

// Function prototypes
void testKMeans();
void testPoint();
void testCluster();

int main()
{
    testKMeans();
//    testPoint();
//    testCluster();

    return 0;
}

// Function definitions
void testKMeans()
{
//    unsigned long int numDims = 5;
//    unsigned long int k = 4;
//    Clustering::KMeans(k, numDims); // NON-TEMPLATE

    const int k = 3;
    const int dims = 5;
    Clustering::KMeans<k, dims> kmeans; // TEMPLATE
}

void testPoint()
{
    /* Test double */
    Clustering::Point<double, 10> p1; // Constructor
    for (int i = 0; i < p1.getDim(); i++)
    {
        p1.setValue(i+1, 4.4); // setValue
    }

    // Check exception - setValue
    try { p1.setValue(11, 4.4); }
    catch (Clustering::OutOfBoundsEx e) { std::cout << "In Point.setValue - " << e << std::endl; }

    // Check exception - getValue
    try { p1.getValue(11); }
    catch (Clustering::OutOfBoundsEx e) { std::cout << "In Point.getValue - " << e << std::endl; }

    std::cout << "Point p1 id: " << p1.getID() << ": " << p1 << std::endl;

    Clustering::Point<double, 10> p2(p1); // Copy constructor
    std::cout << "Point p2 after copy: " << p2 << std::endl;

    Clustering::Point<double, 10> p4;
    std::cout << "Point p4 id: " << p4.getID() << std::endl; // Check ID incrementer (should output 2)

    p4 = p2; // Assignment operator
    std::cout << "Point p4 after assignment operator: " << p4 << std::endl;

    Clustering::Point<double, 10> p5;

    for (int i = 0; i < p5.getDim(); i++)
        p5.setValue(i+1, 6.6);

    std::cout << "p4: " << p4 << "\np5: " << p5 << std::endl;
    std::cout << "p4 distance to p5: " << p4.distanceTo(p5) << std::endl; // Check distanceTo

    std::cout << "p5 value 1: " << p5.getValue(1) << std::endl; // Check getValue

    std::cout << "p5 *= 3.2: " << (p5 *= 3.2) << std::endl; // Check *=
    std::cout << "p5 /= 4.3: " << (p5 /= 4.3) << std::endl; // Check /=

    // Check exception - /= operator
    try { p5 /= 0; }
    catch (Clustering::DivideByZeroEx e) { std::cout << "In Point /= operator - " << e << std::endl; }

    std::cout << "p4 * 3.2: " << (p4 * 3.2) << std::endl; // Check * operator
    std::cout << "p4 / 4.4: " << (p4 / 4.4) << std::endl; // Check / operator

    // Check exception - / operator
    try { p4 / 0; }
    catch (Clustering::DivideByZeroEx e) { std::cout << "In Point / operator - " << e << std::endl; }

    std::cout << "p1: " << p1 << "\np2: " << p2 << std::endl;
    std::cout << "p1 += p2: " << (p1 += p2) << std::endl; // Check +=

    std::cout << "p1: " << p1 << "\np5: " << p5 << std::endl;
    std::cout << "p1 -= p5: " << (p1 -= p5) << std::endl; // Check -=

    std::cout << "p1: " << p1 << "\np5: " << p5 << std::endl;
    std::cout << "p1 + p5: " << (p1 + p5) << std::endl; // Check + operator

    std::cout << "p1: " << p1 << "\np4: " << p4 << std::endl;
    std::cout << "p1 - p4: " << (p1 - p4) << std::endl; // Check - operator

    std::cout << "p1: " << p1 << "\np4: " << p4 << std::endl;
    std::cout << "p1 == p4: " << (p1 == p4) << std::endl; // Check == (should be false)
    std::cout << "p1 != p4: " << (p1 != p4) << std::endl; // Check != (should be true)

    std::cout << "p2: " << p2 << "\np4: " << p4 << std::endl;
    std::cout << "p2 == p4: " << (p2 == p4) << std::endl; // Check == (should be true)
    std::cout << "p2 != p4: " << (p2 != p4) << std::endl; // Check != (should be false)

    std::cout << "p1 > p4: " << (p1 > p4) << std::endl; // Check > (should be false)
    std::cout << "p1 > p1: " << (p1 > p1) << std::endl; // (should be false)
    std::cout << "p1 < p4: " << (p1 < p4) << std::endl; // Check < (should be true)

    std::cout << "p1 >= p4: " << (p1 >= p4) << std::endl; // Check >= (should be false)
    std::cout << "p1 <= p4: " << (p1 <= p4) << std::endl; // Check <= (should be true)

    std::cout << "p2 >= p4: " << (p2 >= p4) << std::endl; // Check >= (should be true)
    std::cout << "p2 <= p4: " << (p2 <= p4) << std::endl; // Check <= (should be true)

    // Check extraction >> operator
    Clustering::Point<double, 5> p8;
    std::ifstream inFile("input.csv");
    inFile >> p8;
    std::cout << "p8: " << p8 << std::endl;

    // Check exception - extraction >> operator
    Clustering::Point<double, 3> p9;
    try { inFile >> p9; std::cout << "p9: " << p9 << std::endl; }
    catch (Clustering::DimensionalityMismatchEx e) { std::cout << "In Point >> operator - " << e << std::endl; }
    /* END TESTING */
    /**********************************************************************/

    /* Test float */
    Clustering::Point<float, 5> p30;
    for (int i = 0; i < p30.getDim(); i++)
    {
        p30.setValue(i+1, 7.735);
    }
    std::cout << "Point p30 (float): " << p30 << std::endl;
    /**********************************************************************/
}

void testCluster()
{
    /* TEST DOUBLE */
    Clustering::Cluster<Clustering::Point<double, 5>, 5> c1;

    // Check extraction >> operator
    // Also tests add() and sort()
    std::ifstream inFile("input.csv");
    inFile >> c1;
    std::cout << "c1:\n" << c1 << std::endl;

    // Check constructors
    Clustering::Cluster<Clustering::Point<double, 5>, 5> c2(c1); // Check copy constructor
    std::cout << "c2 (copy):\n" << c2 << std::endl;

    Clustering::Cluster<Clustering::Point<double, 5>, 5> c3;
    c3 = c2; // Check = operator
    std::cout << "c3 (copy): \n" << c3 << std::endl;

    Clustering::Point<double, 5> p1;
    for (int i = 0; i < p1.getDim(); i++)
        p1.setValue(i+1, 5.5);

    // Member functions
    c1.setCentroid(p1); // Check setCentroid
    std::cout << "c1 Centroid: " << c1.getCentroid() << std::endl;

    c1.setDistanceMap(); // Check setDistanceMap

    std::cout << "c1.size: " << c1.getSize() << std::endl; // Check getSize
    std::cout << "c1 ID: " << c1.getID() << std::endl; // Check getID
    std::cout << "c1 dimensions: " << c1.getNumDimensions() << std::endl; // check getNumDimensions
    std::cout << "c1 Centroid validity: " << c1.getCentroidValidity() << std::endl; // check getCentroidValidity (true)

    std::forward_list<Clustering::Point<double, 5>> head = c1.getHead(); // Check getHead
    auto pos = head.begin();
    std::cout << "c1 list begin: " << *pos << std::endl;

    c1.add(p1);
    std::cout << "c1 (added p1):\n" << c1 << std::endl;
    std::cout << "c1 new Centroid validity: " << c1.getCentroidValidity() << std::endl; // Should be false

    // Check add exception
    try { c1.add(p1); }
    catch(Clustering::PointAlreadyExistsEx e) { std::cout << "In Cluster.add - " << e << std::endl; }

    // Check getMap
    std::unordered_map<Clustering::Key, double, Clustering::KeyHash, Clustering::KeyEqual> map = c1.getMap();
    Clustering::Key key(1, 2);
    auto search = map.find(key);
    std::cout << "Distance at key: " << (map.at(key)) << std::endl;

    Clustering::Point<double, 5> p2;
    for (int i = 0; i < p2.getDim(); i++)
        p2.setValue(i+1, 6.6);

    Clustering::Cluster<Clustering::Point<double, 5>, 5> c4; // Empty cluster

    // Check remove exception
    try { c4.remove(p2); }
    catch (Clustering::RemoveFromEmptyEx e) { std::cout << "In Cluster.remove - " << e << std::endl; }

    c1.remove(p2); // Check remove if Point doesn't exist

    std::cout << "Point removed: " << c1.remove(p1) << std::endl; // Check remove if Point does exist
    std::cout << "c1 after remove:\n" << c1 << std::endl;

    Clustering::Point<double, 5> p01;
    for (int i = 0; i < p01.getDim(); i++)
        p01.setValue(i+1, 1.0);

    Clustering::Point<double, 5> p02;
    for (int i = 0; i < p02.getDim(); i++)
        p02.setValue(i+1, 2.0);

    Clustering::Cluster<Clustering::Point<double, 5>, 5> c01;
    c01.add(p01);
    c01.add(p02);
    c01.setDistanceMap();

    std::cout << "c01 intraCluster distance: " << c01.intraClusterDistance() << std::endl; // Check intraClusterDistance

    Clustering::Cluster<Clustering::Point<double, 5>, 5> c02;
    c02.add(c01.remove(p02)); // Test add(remove());
    std::cout << "c01:\n" << c01 << std::endl;
    std::cout << "c02:\n" << c02 << std::endl;

    // Check interClusterDistance - should be equal to intraClusterDistance above
    std::cout << "c01 and c02 interCluster distance: "
    << Clustering::interClusterDistance(c01, c02, c01.getMap()) << std::endl;

    std::cout << "c01 cluster edges: " << c01.getClusterEdges() << std::endl; // Check getClusterEdges

    // Check interClusterEdges
    std::cout << "c01 and c02 cluster edges: " << Clustering::interClusterEdges(c01, c02) << std::endl;

    c01.calcCentroid(); // Check calcCentroid
    std::cout << "c01 Centroid: " << c01.getCentroid() << std::endl;

    c01.add(c02.remove(p02));
    std::cout << "c01:\n" << c01 << std::endl;
    c01.calcCentroid(); // Check calcCentroid
    std::cout << "c01 new Centroid: " << c01.getCentroid() << std::endl;

    std::cout << "c01 == c02: " << (c01 == c02) << std::endl; // Check == (false)
    std::cout << "c01 != c02: " << (c01 != c02) << std::endl; // Check != (true)

    c02.add(c01.remove(p02));

    std::cout << "c01 += c02:\n" << (c01 += c02) << std::endl; // Check += (Clusters)
    std::cout << "c01 -= c02:\n" << (c01 -= c02) << std::endl; // Check -= (Clusters)

    std::cout << "c01 += p02:\n" << (c01 += p02) << std::endl; // Check += (Point)
    std::cout << "c01 -= p01:\n" << (c01 -= p01) << std::endl; // Check -= (Point)

    c01.add(p01);
    std::cout << "c01:\n" << c01 << std::endl;
    std::cout << "c02:\n" << c02 << std::endl;

    Clustering::Cluster<Clustering::Point<double, 5>, 5>::Move(p01, &c01, &c02); // Check Move
    std::cout << "c01 (moved):\n" << c01 << std::endl;
    std::cout << "c02 (moved):\n" << c02 << std::endl;
}

