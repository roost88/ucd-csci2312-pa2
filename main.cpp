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

    Clustering::KMeans(k, numDims);
}

void testPoint()
{

}

