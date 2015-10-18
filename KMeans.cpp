// Programming Assignment 3 - KMeans Clustering

// Author:      Dylan Lang
// Date:        6 October 2015

// KMeans class implementation

#include <array>
#include <cfloat>

#include "KMeans.h"

namespace Clustering
{
    // Initialize SCORE_DIFF_THRESHOLD variable
    const double KMeans::SCORE_DIFF_THRESHOLD = 10;

    // Constructors
    KMeans::KMeans(int numDims, int numClusters, std::string const &inputFile, std::string const &outputFile)
    {
        /* Setup and Initialization */

        // Assign k
        k = numClusters;

        // Create a new Cluster to hold all Points, set numDimensions = k
        point_space = new Cluster(numDims);

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

        // Create dynamic array of k ClusterPtrs
        kClusterArray = new ClusterPtr[k];
        for (int i = 0; i < k; i++)
        {
            kClusterArray[i] = new Cluster(numDims);
        }

        // Set point_space as first Cluster in array
        *kClusterArray[0] = *point_space;

        // Set Centroids and dimensions of dynamic Clusters
        for (int i = 0; i < k; i++)
        {
            kClusterArray[i]->setCentroid((*centroidArray[i]));
            std::cout << "kCluster " << (i+1) << " Centroid: " << kClusterArray[i]->getCentroid() << std::endl;
        }

        // Create variables to hold Clustering score and scoreDiff
        double score, scoreDiff;
        scoreDiff = SCORE_DIFF_THRESHOLD + 8; // Ensures we iterate at least once

        /****************************************/

        /* Perform Clustering */

        // Copy point_space to get a list of all Points
        ListNodePtr universe = point_space->getHead();

        // Loop until scoreDiff < SCORE_DIFF_THRESHOLD
        while(SCORE_DIFF_THRESHOLD < scoreDiff)
        {
            // Loop through all Clusters
            for (int i = 0; i < k; i++)
            {
                // Current Cluster variable
                ClusterPtr current = kClusterArray[i];
                ListNodePtr curr = kClusterArray[i]->getHead();

                // Loop through all Points
                while (curr != nullptr)
                {
                    // Point variable
                    PointPtr pt = curr->p;

                    // Other Cluster variable
                    ClusterPtr other;

                    // Find the smallest distance between current Point and a Centroid
                    double minDist = DBL_MAX;
                    PointPtr currCentroid;

                    for (int j = 0; j < k; j++)
                    {
                        // Calculate distance from current Point to each Centroid
                        double currDist = curr->p->distanceTo(*centroidArray[j]);

                        if (minDist > currDist)
                        {
                            // Save the nearest Centroid
                            minDist = currDist;
                            currCentroid = centroidArray[j];
                        }
                    }

                    if (*currCentroid != current->getCentroid())
                    {
                        // Search for Cluster that has matching Centroid
                        for (int h = 0; h < k; h++)
                        {
                            if (*currCentroid == kClusterArray[h]->getCentroid())
                            {
                                other = kClusterArray[h];
                            }
                        }

                        // Perform move
                        Cluster::Move *m = new Cluster::Move(pt, current, other);
                        delete m;
                    }
                    curr = curr->next;
                }
            }

            // If Centroids are invalid, recalculate Centroids for each Cluster
//            for (int i = 0; i < k; i++)
//            {
//                if (!kClusterArray[i]->centroidValidity())
//                {
//                    kClusterArray[i]->calcCentroid();
//                    *centroidArray[i] = kClusterArray[i]->getCentroid();
//                    std::cout << "*" << kClusterArray[i]->getCentroid() << std::endl;
//                }
//            }

            // Compute new clusteringScore

            // Compute absolute difference and set scoreDiff
            scoreDiff--;
        }
        /****************************************/

        /* Write results to file and self-destruct */

        // Write out the Clustering results to a file
//        std::cout << "point_space(AFTER):\n" << *point_space << std::endl;

        for (int i = 0; i < k; i++)
        {
            std::cout << "kCluster " << i+1 << " (AFTER):\n" << *kClusterArray[i] << std::endl;
        }

        // Delete everything
        std::cout << "****************" << std::endl;

    }

    // Destructor
    KMeans::~KMeans()
    {
        // Destroy point_space Cluster and all Points within
        ListNodePtr pSpace = point_space->getHead();
        while (pSpace != nullptr)
        {
            delete pSpace->p;
            pSpace = pSpace->next;
        }
        delete point_space;

        // Delete kClusterArray and all Points within
        for (int i = 0; i < k; i++)
        {
            delete kClusterArray[i];
        }
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
