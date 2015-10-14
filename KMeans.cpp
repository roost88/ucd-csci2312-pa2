// Programming Assignment 3 - KMeans Clustering

// Author:      Dylan Lang
// Date:        6 October 2015

// KMeans class implementation

#include <array>

#include "KMeans.h"

namespace Clustering
{
    // Initialize SCORE_DIFF_THRESHOLD variable
    const double KMeans::SCORE_DIFF_THRESHOLD = 1;

    // Constructors
    KMeans::KMeans(int k, std::string const &inputFile, std::string const &outputFile)
    {
        /* Setup and Initialization */
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

        // Set Centroid of point_space to last Centroid in array
        point_space->setCentroid(*centroidArray[k-1]);
        std::cout << "point_space Centroid: " << point_space->getCentroid() << std::endl;

        // Create variables to hold Clustering score and scoreDiff
        double score, scoreDiff;
        scoreDiff = SCORE_DIFF_THRESHOLD + 1;

        /****************************************/

        /* Perform Clustering */

        // Copy point_space so we can loop through all Points
        Cluster universe(*point_space);

        // While loop iterates at least once
        while (scoreDiff > SCORE_DIFF_THRESHOLD)
        {
            for (int i = 0; i < (k - 1); i++)
            {
                // Copy head of universe
                ListNodePtr current = universe.getHead();

                // Loop through all Points in universe
                while (current != nullptr)
                {
                    // Variable for storing distance to point_space Centroid
                    double compDist = current->p->distanceTo(point_space->getCentroid());
                    std::cout << "compDist = " << compDist << std::endl;

                    // Store distance to other Cluster
                    std::cout << "current->p = " << *current->p << std::endl;
                    std::cout << "kCluster Centroid = " << kClusterArray[i].getCentroid() << std::endl;
                    double distance = current->p->distanceTo(kClusterArray[i].getCentroid());
                    std::cout << "distance = " << distance << std::endl;

                    if (compDist > distance)
                    {
                        // Move Point from point_space to current Cluster
                        Cluster::Move *m1 = new Cluster::Move(current->p, point_space, &kClusterArray[i]);
                        std::cout << "point_space = " << *point_space << std::endl;
                        std::cout << "kCluster = " << kClusterArray[i] << std::endl;
                        std::cout << "Break" << std::endl;
                        delete m1;
                        current = current->next;
                    }
                    else
                    {
                        current = current->next;
                    }
                }
            }

            // Loop through Clusters to re-calculate Centroids
            for (int i = 0; i < (k - 1); i++)
            {
                if (!kClusterArray[i].centroidValidity())
                {
                    kClusterArray[i].calcCentroid();
                }
            }

            // Recalculate Clustering score and set scoreDiff
            score = computeClusteringScore();
            score -= scoreDiff;
            scoreDiff = fabs(score);

            std::cout << "Running Clustering algorithm!" << std::endl;
        }
        /****************************************/

        /* Write results to file and self-destruct */

        // Delete Centroid array
        delete [] centroidArray;
        centroidArray = nullptr;

        /****************************************/
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
