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
//    testKMeans();
//    testPoint();
    testCluster();

    return 0;
}

// Function definitions
void testKMeans()
{
//    unsigned long int numDims = 5;
//    unsigned long int k = 4;
//    Clustering::KMeans(k, numDims); // NON-TEMPLATE

//    const int dims = 5;
//    const int k = 4;
//    using namespace Clustering;
//    KMeans<Cluster<Point<double, dims>>, k, dims>; // TEMPLATE
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

}

