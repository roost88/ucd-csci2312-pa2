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

int main()
{
    testKMeans();
//    testPointBool();

    return 0;
}

// Function definitions
void testKMeans()
{
    unsigned long int numDims = 5;
    int k = 4;
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
    c1 += p2;

    std::cout << c1 << std::endl;

    c1 -= p1;

    std::cout << c1 << std::endl;

    std::cout << (c1 + p1) << std::endl;

    std::cout << (c1 - p2) << std::endl;

}

