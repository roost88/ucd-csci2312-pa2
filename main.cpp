// Programming Assignment 4 - KMeans Clustering

// Author:      Dylan Lang
// Date:        28 October 2015

#include <iostream>
#include <fstream>
#include "Point.h"
#include "Cluster.h"
#include "KMeans.h"
#include "Exceptions.h"

// TODO: Create Testing .h and .cpp files

// Function prototypes
void testKMeans();
void testPointBool();
void testPoint();

int main()
{
    testKMeans();
//    testPointBool();
//    testPoint();

    return 0;
}

// Function definitions
void testKMeans()
{
    unsigned long int numDims = 5;
    unsigned long int k = 4;
    std::string input = "input.csv";
    std::string output = "output.csv";

    Clustering::KMeans(numDims, k, input, output);
}

void testPointBool()
{
    Clustering::Point p1(2);
    p1.setValue(1, 2.0);
    p1.setValue(2, 5.0);

    Clustering::Point p2(2);
    p2.setValue(1, 6.0);
    p2.setValue(2, 90.0);

    Clustering::Cluster c1(2);

    c1.add(p1);

    std::cout << c1 << std::endl;

    std::vector<Clustering::Cluster> kClusterArray(3);

    kClusterArray.insert(kClusterArray.begin(), c1);

    std::cout << kClusterArray[0] << std::endl;

    kClusterArray[1].add(p1);
    kClusterArray[1].add(p2);

    std::cout << kClusterArray[1] << std::endl;

    kClusterArray[0].add(kClusterArray[1].remove(p2));

    std::cout << kClusterArray[0] << std::endl;
    std::cout << kClusterArray[1] << std::endl;
}

void testPoint()
{
    Clustering::Point p1(5);
    p1.setValue(1, 1);
    p1.setValue(2, 2);
    p1.setValue(3, 3);
    p1.setValue(4, 4);
    p1.setValue(5, 5);

    std::cout << p1 << std::endl;

    Clustering::Point p2(0);

    p2 = p1;

    std::cout << p2 << std::endl;
}

