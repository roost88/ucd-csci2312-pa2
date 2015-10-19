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
    const double KMeans::SCORE_DIFF_THRESHOLD = 20;

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

        // Set point_space as first Cluster in array
        kClusterArray[0] = new Cluster(*point_space);

        for (int i = 1; i < k; i++)
        {
            kClusterArray[i] = new Cluster(numDims);
        }

        // Set Centroids and dimensions of dynamic Clusters
        for (int i = 0; i < k; i++)
        {
            kClusterArray[i]->setCentroid((*centroidArray[i]));
            std::cout << "kCluster " << (i+1) << " Centroid: " << kClusterArray[i]->getCentroid() << std::endl;
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
                    Point currCentroid(numDims);

                    for (int j = 0; j < k; j++)
                    {
                        // Calculate distance from current Point to each Centroid
                        double currDist = curr->p->distanceTo(kClusterArray[j]->getCentroid());

                        if (minDist > currDist)
                        {
                            // Save the nearest Centroid
                            minDist = currDist;
                            currCentroid = kClusterArray[j]->getCentroid();
                        }
                    }

                    if (currCentroid != current->getCentroid())
                    {
                        // Search for Cluster that has matching Centroid
                        for (int h = 0; h < k; h++)
                        {
                            if (currCentroid == kClusterArray[h]->getCentroid())
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

                // If Centroids are invalid, recalculate Centroids for each Cluster
                for (int i = 0; i < k; i++)
                {
                    if (!kClusterArray[i]->centroidValidity())
                    {
                        kClusterArray[i]->calcCentroid();
                        std::cout << "*" << kClusterArray[i]->getCentroid() << std::endl;
                    }
                }
            }

            // Compute new clusteringScore
            score = computeClusteringScore(kClusterArray);
            std::cout << "Clustering Score = " << score << std::endl;

            // Compute absolute difference and set scoreDiff
            scoreDiff = fabs(scoreDiff - score);
//            scoreDiff--;
        }
        /****************************************/

        /* Write results to file and self-destruct */

        // Write out the Clustering results to a file
        for (int i = 0; i < k; i++)
        {
            std::cout << "\nkCluster " << i+1 << " (AFTER):\n" << "Size: " << kClusterArray[i]->getSize() << "\nCentroid: " << kClusterArray[i]->getCentroid() << "\n" << *kClusterArray[i];
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
    double KMeans::computeClusteringScore(ClusterPtr *clusterArray)
    {
        // Implement Beta-CV criterion (coefficient of variation)
        // Ratio of mean intra-cluster distance and mean inter-cluster distance
        // The smaller, the better
        // Use:
//         intraClusterDistance();
//         interClusterDistance(const Cluster &c1, const Cluster &c2);
//         getClusterEdges();

        double numer = 0;
        double denom = 0;
        double temp, result;

        // Calculate intraCluster distance for each Cluster and add to numer
        for (int i = 0; i < k; i++)
        {
            numer += clusterArray[i]->intraClusterDistance();
            std::cout << "numer+= " << numer << std::endl;
            temp = clusterArray[i]->getClusterEdges();
            std::cout << "temp = " << temp << std::endl;

            if (temp > 0)
            {
                numer /= temp;
                std::cout << "numer /= temp: " << numer << std::endl;
            }
        }
        std::cout << "numer final: " << numer << std::endl;

        // Calculate interCluster distance between each Cluster and add to denom
        for (int i = 0; i < k; i++)
        {
            for (int j = 0; j < k; j++)
            {
                denom += interClusterDistance(*clusterArray[i], *clusterArray[j]);
                std::cout << "denom += " << denom << std::endl;
            }
        }

        // Divide denom by 2 since we calculated it twice
        denom /= 2.0;
        std::cout << "denom /= 2: " << denom << std::endl;

        // Divide denom by number of k Clusters to get mean
        denom /= k;
        std::cout << "denom /= k: " << denom << std::endl;

        result = numer / denom;

        return result;
    }
} // end namespace Clustering
