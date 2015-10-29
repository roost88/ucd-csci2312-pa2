##CSCI 2312: Programming Assignment 4

**KMeans Clustering**
* Author:     Dylan Lang
* Date:       28 October 2015

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
* KMeans.cpp    - KMeans implementation file
* KMeans.h      - KMeans function declaration/header file
* readme.md

####Purpose
The purpose of this program is use a KMeans Clustering algorithm to separate Points input from a file into several
Clusters.
Each Cluster will contain a Centroid (center Point which is the mean average of all the Points in the Cluster).
Points will be assigned to the Cluster whose Centroid is closest to it.

####Design
_Point Class -_
* Points can contain an arbitrary number of dimensions.
* Point dimensions are stored in an array call "values".
* Points are allowed full functionality of the program by overloading arithmetic, assignment, comparison, and insertion
operators that work with other Points, as well as integers (i.e. Points can be divided by 2, multiplied by 5, and
assigned to another Point)
* Points can be output using only the << operator and the name of the Point in the following format: x, y, z

_Cluster Class -_
* Clusters can contain an arbitrary number of Points, or even none at all.
* Points are stored in a Node that is placed in a Cluster using a Linked List.
* Each Cluster has a "head" that points to the first Node in the list.
* Each Node contains a pointer to a Point, as well as a "next" that points to the next Node in the list.
* Clusters are allowed full functionality by overloading arithmetic, assignment, comparison, and insertion operators
that work with Points, as well as other Clusters.
* Cluster arithmetic is not allowed with integers.
* Clusters can be output using the << operator and the name of the Cluster in the following format:
x, y, z : (id of Cluster)
* Added: Each Cluster contains a Centroid, which is a Point that is the center of the Cluster (mean of all Points in
Cluster).
* Added: Function to calculate Centroid of a Cluster (uses sum of all Points in Cluster divided by the size).
* Added: Function to set the Centroid of a Cluster
* Added: Method to pick k Points from a Cluster to be Centroids for Clustering algorithm
- This method divides the size of the Cluster by k, then picks the last Point in every k Points to be a Centroid.
- This assures that each Centroid will be distributed semi-equally throughout the Point space.
* Added: Functions to calculate sum of distances between each Point in a Cluster, each Point between two Clusters,
and the unique "edges" between each Point in a Cluster.

_KMeans Class -_
* KMeans constructor takes the following parameters (in order):
- An int for the number of dimensions of the Points being read in from file
- An int to represent k, which is the amount of Clusters you want in the output
- An input file name in a string
- An output file name in a string
* Contains private member variables for storing "k", all Points read in from file, and an array of Clusters used in
Clustering algorithm.
* Contains public static constant double member variable SCORE_DIFF_THRESHOLD that contains the initial double that
will be used to break the Clustering algorithm loop (currently set to 0.3).
* Contains method for computing Clustering score each time Clustering algorithm is run. This is used as an iterator for
the Clustering algorithm.

* Opens an input file and reads Points from file into a Cluster called "point_space"
* Picks k initial Centroids evenly from throughout point_space and stores them in a Centroid array
* Creates an array of k Clusters for use in Clustering algorithm. Each of these Clusters is assigned a unique Centroid
from the Centroid array.
* Runs the Clustering algorithm, then outputs the results to the output file.

_Clustering Algorithm in KMeans -_
* The Clustering algorithm in KMeans calculates the distance from a Point stored in point_space to each Centroid
stored in the k Clusters. The Point is then moved from its current Cluster to whichever Cluster has the closest
Centroid.
* With each iteration of the Clustering algorithm, the Centroids are re-calculated with whichever Points remain in the
Cluster.
* At the end of the Clustering algorithm, a new Clustering Score is calculated, which uses the BetaCV criterion used
in Data Mining statistics. This calculation requires the intraClusterDistance, interClusterDistance, and
getClusterEdges functions from Cluster.cpp.
* The new Clustering score is subtracted from the SCORE_DIFF_THRESHOLD, and the absolute value of the difference is
used to iterate the algorithm. Once this value is equal to or less than the SCORE_DIFF_THRESHOLD, the algorithm
terminates.

###Testing
All classes and functions have been tested in main.cpp

####Notes
The overloaded > operator for the Point class has been changed, as it was not reading Points into the Cluster in
lexicographic order.

Cluster constructor definitions have been moved from Cluster.cpp to Cluster.h

Cluster destructor fixed.

The numDims variable in the KMeans constructor should match the dimensions of the Points you intend to read in
from the input file.

The "k" value in the KMeans constructor should be greater than 0 and cannot be greater than the number of Points
being read in from file.

SCORE_DIFF_THRESHOLD in Cluster.cpp must be set to a double that is less than 1.0 and greater than 0.
Best value found so far is 0.3.

