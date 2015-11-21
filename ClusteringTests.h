// Programming Assignment 4 - KMeans Clustering

// Author:      Dylan Lang
// Date:        28 October 2015 - 21 November 2015

#ifndef CLUSTERINGTESTS_H
#define CLUSTERINGTESTS_H

#include <iostream>
#include <fstream>
#include "KMeans.h"
#include "ErrorContext.h"

using namespace Testing;

// My tests
void testKMeans();
void testPoint();
void testCluster();

// - - - - - - - - - Tests: class Point - - - - - - - - - -
// From Dr. Georgiev

// Smoketest: constructor, copy constructor, destructor
void test_point_smoketest(ErrorContext &ec);

// setValue, getValue, operator[] (incl. exceptions)
void test_point_getsetelem(ErrorContext &ec, unsigned int numRuns);

// Copy constructor
void test_point_copying(ErrorContext &ec, unsigned int numRuns);

// operator= (incl. exceptions)
void test_point_assignment(ErrorContext &ec, unsigned int numRuns);

// operator==, operator!=
void test_point_equality(ErrorContext &ec, unsigned int numRuns);

// operator<, operator<=, operator>, operator>= (incl. exceptions)
// (ascending pseudo-lexicographic order)
void test_point_comparison(ErrorContext &ec, unsigned int numRuns);

// operator+=, operator-= (incl. exceptions), operator*=, operator/=
void test_point_CAO(ErrorContext &ec, unsigned int numRuns);

// operator+, operator- (incl. exceptions), operator*, operator/
void test_point_SAO(ErrorContext &ec, unsigned int numRuns);

// distanceTo
void test_point_distance(ErrorContext &ec, unsigned int numRuns);

// operator>>, operator<< (incl. exceptions)
void test_point_IO(ErrorContext &ec, unsigned int numRuns);



// - - - - - - - - - Tests: class Cluster - - - - - - - - - -

// Smoketest: constructor, copy constructor, destructor
void test_cluster_smoketest(ErrorContext &ec);

// add, remove, operator[], check elements are in order (incl. exceptions)
void test_cluster_addremove(ErrorContext &ec, unsigned int numRuns);

// Inner class Move
void test_cluster_move(ErrorContext &ec, unsigned int numRuns);

// Copy constructor
void test_cluster_copying(ErrorContext &ec, unsigned int numRuns);

// operator=
void test_cluster_assignment(ErrorContext &ec, unsigned int numRuns);

// operator==, operator!=
void test_cluster_equality(ErrorContext &ec, unsigned int numRuns);

// operator+=, operator-=, different rhs
void test_cluster_CAO(ErrorContext &ec, unsigned int numRuns);

// operator+, operator-, different rhs
void test_cluster_SAO(ErrorContext &ec, unsigned int numRuns);

// Centroid
void test_cluster_centroid(ErrorContext &ec, unsigned int numRuns);

// Init element selection ("pickPoints")
void test_cluster_initselection(ErrorContext &ec, unsigned int numRuns);

// Scoring functions
void test_cluster_scoring(ErrorContext &ec, unsigned int numRuns);

// operator>>, operator<<
void test_cluster_IO(ErrorContext &ec, unsigned int numRuns);



// - - - - - - - - - Tests: class KMeans - - - - - - - - - -

// Smoketest: constructor, copy constructor, destructor
void test_kmeans_smoketest(ErrorContext &ec);

// operator>>, operator<<
void test_kmeans_IO(ErrorContext &ec, unsigned int numRuns);

// Clustering score
void test_kmeans_score(ErrorContext &ec, unsigned int numRuns);

// K larger than number of points
void test_kmeans_toofewpoints(ErrorContext &ec, unsigned int numRums);

// Check scoring doesn't overflow with large points
void test_kmeans_largepoints(ErrorContext &ec, unsigned int numRums);

// Large k, less than number of points
void test_kmeans_toomanyclusters(ErrorContext &ec, unsigned int numRums);

#endif //CLUSTERINGTESTS_H
