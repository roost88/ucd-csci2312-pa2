// Programming Assignment 3 - KMeans Clustering

// Author:      Dylan Lang
// Date:        6 October 2015

// KMeans class implementation

#include <array>

#include "KMeans.h"

namespace Clustering
{
    // Initialize SCORE_DIFF_THRESHOLD variable
    const double KMeans::SCORE_DIFF_THRESHOLD = 10;

    // Constructors
    KMeans::KMeans(int numDims, int k, std::string const &inputFile, std::string const &outputFile)
    {
        /* Setup and Initialization */

        // Create a new Cluster to hold all Points, set numDimensions = k
        point_space = new Cluster;

        // Create a new input file stream
        std::ifstream inFile(inputFile);

        // Check if file opened
        if (inFile)
        {
            // Read Points from file into point_space Cluster
            inFile >> *point_space;

            // Close the file
            inFile.close();
            std::cout << "\npoint_space:\n" << *point_space << std::endl;
        }
        else
        {
            // Display error message and exit
            std::cout << "File did not open!" << std::endl;
            exit(EXIT_FAILURE);
        }

        // Create empty array of Centroids
        Clustering::PointPtr *centroidArray = new Clustering::PointPtr[k];

        // Pick Centroids from Cluster
        point_space->pickPoints(k, centroidArray);

        // Set point_space Centroid to first Centroid in array
        point_space->setCentroid(*centroidArray[0]);
        std::cout << "point_space Centroid: " << point_space->getCentroid() << std::endl;

        // Create dynamic array of k ClusterPtrs
        kClusterArray = new Cluster[k-1];

        // Set Centroids of dynamic Clusters
        for (int i = 0; i < (k-1); i++)
        {
            kClusterArray[i].setCentroid((*centroidArray[i+1]));
            std::cout << "kCluster " << (i+1) << " Centroid: " << kClusterArray[i].getCentroid() << std::endl;
        }

        // Create variables to hold Clustering score and scoreDiff
        double score, scoreDiff;
        scoreDiff = SCORE_DIFF_THRESHOLD + 1; // Ensures we iterate at least once

        /****************************************/

        /* Perform Clustering */

        // Loop until scoreDiff < SCORE_DIFF_THRESHOLD
        while(SCORE_DIFF_THRESHOLD < scoreDiff)
        {
            // Loop through all Clusters

                // Loop through all Points

                    // Find distance between Point and Centroid

                    // If Centroid not of current Cluster

                        // Perform Move

            // Loop through all Clusters

                // If Centroid is invalid

                    // Compute new Centroid

            // Compute new clusteringScore

            // Compute absolute difference and set scoreDiff
            scoreDiff--;
        }
        /****************************************/

        /* Write results to file and self-destruct */

        // Write out the Clustering results to a file

        // Delete everything
        std::cout << "****************" << std::endl;
        delete point_space;

        delete [] kClusterArray;
    }

    // Destructor
    KMeans::~KMeans()
    {

    }

    // Member functions
    double KMeans::computeClusteringScore()
    {
        // Implement Beta-CV criterion (coefficient of variation)
        // Ratio of mean intra-cluster distance and mean inter-cluster distance
        // The smaller, the better
        // Use:
//         intraClusterDistance();
//         interClusterDistance(const Cluster &c1, const Cluster &c2);
//         getClusterEdges();
    }
} // end namespace Clustering
