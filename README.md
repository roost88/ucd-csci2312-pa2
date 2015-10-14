##CSCI 2312: Programming Assignment 3

**Point Cluster Program**
* Author:     Dylan Lang
* Date:       6 October 2015

**System Info -**
* Operating System:   Windows 8.1 64-bit
* Processor:          x64-based

**Toolchain -**
* IDE:            CLion 1.1
* Compiler:       GCC/G++
* Terminal:       Cygwin64
* Build Manager:  CMake 3.3, make
* Debugger:       GDB 7.8

**Included -**
* main.cpp      - holds code snippets for testing
* Point.cpp     - Point implementation file
* Point.h       - Point function declaration/header file
* Cluster.cpp   - Cluster implementation file
* Cluster.h     - Cluster function declaration/header file
* readme.md

####Purpose
The purpose of this program is use a KMeans Clustering algorithm to separate Points input from a file into several Clusters.
Each Cluster will contain a Centroid (center Point which is the mean average of all the Points in the Cluster).
Points will be assigned to the Cluster whose Centroid is within the closes distance to it.

####Design
_Point Class -_
* Points can contain an arbitrary number of dimensions (i.e. Point p4 can have dimensions 1, 2, and 3, while Point p6 can have dimensions 4, 5, 6, 7, and 8, and so on).
* Point dimensions are stored in an array call "values".
* Points are allowed full functionality of the program by overloading arithmetic, assignment, comparison, and insertion operators that work with other Points, as well as integers (i.e. Points can be divided by 2, multiplied by 5, and assigned to another Point)
* Points can be output using only the << operator and the name of the Point in the following format: x, y, z

_Cluster Class -_
* Clusters can contain an arbitrary number of Points, or even none at all.
* Points are stored in a Node that is placed in a Cluster using a Linked List.
* Each Cluster has a "head" that points to the first Node in the list.
* Each Node contains a pointer to a Point, as well as a "next" that points to the next Node in the list.
* Each Cluster also has a "size" variable that tracks how many Points (Nodes) are in the Cluster.
* Clusters are allowed full functionality by overloading arithmetic, assignment, comparison, and insertion operators that work with Points, as well as other Clusters.
* Cluster arithmetic is not allowed with integers.
* Clusters can be output using only the << operator and the name of the Cluster in the following format: x, y, z : (id of Cluster)
* Added: Each Cluster contains a Centroid, which is a Point that is the center of the Cluster (mean of all Points in Cluster).
* Added: The Centroid will change with each Point that is added to or removed from the Cluster
* Added: Method to pick k (arbitrary integer value) Points from a Cluster to be Centroids for Clustering algorithm
- This method divides the size of the Cluster by k, then picks the last Point in every k Points to be a Centroid.
- This assures that each Centroid will be distributed semi-equally throughout the Point space.

_KMeans Class -_

###Testing
I've created two functions, testPoint() and testCluster(), which use snippets of code to test all of each class's functions.

####Notes
The overloaded > operator for the Point class has been changed, as it was not reading Points into the Cluster in lexicographic order.

