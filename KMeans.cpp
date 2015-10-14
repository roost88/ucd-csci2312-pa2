// Programming Assignment 3 - KMeans Clustering

// Author:      Dylan Lang
// Date:        6 October 2015

// KMeans class implementation

#include "KMeans.h"

namespace Clustering
{
    // Initialize SCORE_DIFF_THRESHOLD variable
    const double KMeans::SCORE_DIFF_THRESHOLD = 1;

    // Constructors
    KMeans::KMeans(int k, std::string const &inputFile, std::string const &outputFile)
    {
        // Create a new Cluster to hold all Points
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
            // Display error message
            std::cout << "File did not open!" << std::endl;
        }

        // Create empty array of Centroids
        Clustering::PointPtr *centroidArray = new Clustering::PointPtr[k];

        // Pick Centroids from Cluster
        point_space->pickPoints(k, centroidArray);

        // Display Centroids
        for (int i = 0; i < k; i++)
        {
            std::cout << "Centroid " << (i+1) << ": " << *centroidArray[i] << std::endl;
        }

        // Create dynamic array of ClusterPtrs
        kClusterArray = new Cluster [k-1];

        // Set Centroids of dynamic Clusters
        for (int i = 0; i < (k-1); i++)
        {
            kClusterArray[i].setCentroid((*centroidArray[i]));
            std::cout << "Cluster " << (i+1) << " Centroid: " << kClusterArray[i].getCentroid() << std::endl;
        }

        // Set Centroid of point_space
        point_space->setCentroid(*centroidArray[k-1]);
        std::cout << "point_space Centroid: " << point_space->getCentroid() << std::endl;

        // Delete Centroid array
        delete [] centroidArray;
        centroidArray = nullptr;

        // Create variables to hold Clustering score and scoreDiff
        double score, scoreDiff;
        scoreDiff = SCORE_DIFF_THRESHOLD + 1;

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
