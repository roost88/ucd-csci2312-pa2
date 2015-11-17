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
void testPoint();

int main()
{
    testKMeans();
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

void testPoint()
{
    Clustering::Point p1(1);

    p1.setValue(1, 4.3);

    Clustering::Point p2(1);
    p2.setValue(1, 6.9);

    double dist = p1.distanceTo(p2);

    std::cout << dist;


}

