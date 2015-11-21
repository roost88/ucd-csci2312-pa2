##CSCI 2312: Programming Assignment 4

**KMeans Clustering**
* Author:     Dylan Lang
* Date:       28 October 2015 - 21 November 2015

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
* main.cpp              - initializes program
* Point.cpp             - Point implementation file
* Point.h               - Point function declaration/header file
* Cluster.cpp           - Cluster implementation file
* Cluster.h             - Cluster function declaration/header file
* KMeans.cpp            - KMeans implementation file
* KMeans.h              - KMeans function declaration/header file
* ClusteringTests.cpp   - Testing functions for Point, Cluster, and KMeans implementation file
* ClusteringTests.h     - Testing functions declaration/header file
* ErrorContext.cpp      - Testing suite implementation file
* ErrorContext.h        - Testing suite declaration/header file
* readme.md

####Purpose
The purpose of this program is use a KMeans Clustering algorithm to separate Points input from a file into several
Clusters.
Each Cluster will contain a Centroid (center Point which is the mean average of all the Points in the Cluster).
Points will be assigned to the Cluster whose Centroid is closest to it.

####Design
_Point Class -_
* Points can contain an arbitrary number of dimensions.
* Point dimensions are stored in a vector called "values".
* Points are allowed full functionality of the program by overloading arithmetic, assignment, comparison, and insertion
operators that work with other Points, as well as integers (i.e. Points can be divided by 2, multiplied by 5, and
assigned to another Point, etc.)
* Entire Points can be output using only the << operator and the name of the Point in the following format: x, y, z
* ADDED: All Point class methods have been moved from Point.cpp to Point.h for template use.
* ADDED: Templated to except any integer or floating-point types (except char), and dimensions
* ADDED: Exceptions in Point methods
* ADDED: Each Point has a unique ID number that corresponds ONLY to that Point
* ADDED: The Point member variable "__values" is now a vector

_Cluster Class -_
* Clusters can contain an arbitrary number of Points, or none at all.
* Points are stored in a forward_list, represented by the Cluster variable "__head."
* Clusters are allowed full functionality by overloading arithmetic, assignment, comparison, and insertion operators
that work with Points, as well as other Clusters.
* Cluster arithmetic is not allowed with integers.
* Entire Clusters can be output using the << operator and the name of the Cluster
* Each Cluster contains a Centroid, which is a Point that is the center of the Cluster (mean of all Points in
Cluster).
* ADDED: All Cluster class methods have been moved from Cluster.cpp to Cluster.h for template use.
* ADDED: Templated to accept Point as a typename, as well as the dimensions of the Points within the Cluster
* ADDED: Exceptions in Cluster methods, as well as Catch clauses to catch Point exceptions
* ADDED: All Cluster methods have been changed to work with Points instead of Point pointers
* ADDED: "contains" method, which checks if a Point already exists in a Cluster
* ADDED: Distances between Points are stored in an unordered_map called "__distances."
* ADDED: Structures for "Key", "KeyHash", and "KeyEquals" to create keys for the unordered_map
* ADDED: "numberImported" and "numberFailed" methods to track Points that were successful or failed to import in.
* REMOVED: Node structure and all linked-list methods and variables

_KMeans Class -_
* Creates a Cluster that will hold all Points we'll use in the program (__point_space).
* Opens a data file and reads all VALID Points into the Cluster.
* Uses Cluster's "pickPoints" method to pick Points from the Cluster to use as Centroids
- Uses the size of the Cluster to incrementally choose Points separated evenly throughout the Cluster
* Creates k-1 empty Clusters that will be used to sort the data

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
* ADDED: All KMeans class methods have been moved from KMeans.cpp to KMeans.h for template use.
* ADDED: Templated to accept any integer or floating point type (except char), an integer for k, and an integer
for the number of dimensions to be used throughout the program.
* ADDED: Catch clauses to catch exceptions from the Cluster class
* ADDED: The array that holds the k Clusters is now a vector
* ADDED: Now reports the number of Points successfully imported (numberImported) and failed to import (numberFailed).

###Testing
Testing methods have been created in ClusteringTests.cpp

####Notes
The number of dimensions in the KMeans constructor should match the majority of the dimensions of the Points
you intend to read in from the input file.

SCORE_DIFF_THRESHOLD in Cluster.h must be set to a double that is less than 1.0 and greater than 0.
The value changes depending on the amount of Clusters (k) you want to output.
The higher the value of "k", the lower the SCORE_DIFF_THRESHOLD can be.

The computerClusteringScore function in KMeans has been fixed.



