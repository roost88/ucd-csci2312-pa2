##CSCI 2312: Programming Assignment 2

**Point Cluster Program**
* Author:     Dylan Lang
* Date:       10 Sept 2015

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
The purpose of this program is to allow the programmer full functionality of the Point class and Cluster class.

####Design
_Point Class -_
* Points can contain an arbitrary number of dimensions (i.e. Point p4 can have dimensions 1, 2, and 3, while Point p6 can have dimensions 4, 5, 6, 7, and 8, and so on).
* Point dimensions are stored in an array call "values".
* Points are allowed full functionality of the program by overloading arithmetic, assignment, comparison, and insertion operators that work with other Points, as well as integers (i.e. Points can be divided by 2, multiplied by 5, and assigned to another Point)
* Points can be output using only the << operator and the name of the Point in the following format: (x,y,z)

_Cluster Class -_
* Clusters can contain an arbitrary number of Points, or even none at all.
* Points are stored in Node that is placed in a Cluster using a Linked List.
* Each Cluster has a "head" that points to the first Node in the list.
* Each Node contains a pointer to a Point, as well as a "next" that points to the next Node in the list.
* Each Cluster also has a "size" variable that tracks how many Points (Nodes) are in the Cluster.
* Clusters are allowed full functionality by overloading arithmetic, assignment, comparison, and insertion operators that work with Points, as well as other Clusters.
* Cluster arithmetic is not allowed with integers.
* Clusters can be output using only the << operator and the name of the Cluster in the following format: {(x,y,z)(x,y,z)}

###Testing
I've created two functions, testPoint() and testCluster(), which use snippets of code to test all of each class's functions.

####Notes
I did not overload the istream >> operator, as it was unnecessary for PA2.

