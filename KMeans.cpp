// Programming Assignment 4 - KMeans Clustering

// Author:      Dylan Lang
// Date:        28 October 2015

// KMeans class implementation

#include <cfloat> // for DBL_MAX

#include "KMeans.h"
#include "Exceptions.h"

namespace Clustering
{
    // Initialize SCORE_DIFF_THRESHOLD variable
    const double KMeans::SCORE_DIFF_THRESHOLD = 0.3; // Must be less than 1.0 and greater than 0

    // Constructors
    KMeans::KMeans(unsigned long int numDims, int numClusters, std::string const &inputFile, std::string const &outputFile)
    {
        /* Setup and Initialization */

        // Create a new Cluster to hold all Points, set numDimensions = k
        __point_space = new Cluster(numDims);

        // Create a new input file stream
        std::ifstream inFile(inputFile);

        // Check if file opened
        if (inFile)
        {
            std::cout << "\nInput file opened!" << std::endl;
            std::cout << "Reading Points from input file into point_space..." << std::endl;

            // Read Points from file into point_space Cluster
            inFile >> *__point_space;

            // TODO: report how many Points were read in OK and how many failed due to Dimensionality Mismatch

            std::cout << "\n" << __point_space->getSize() << " Points read in from file!" << std::endl;

            // Close the file
            inFile.close();
            std::cout << "\npoint_space:\n" << *__point_space << std::endl;
        }
        else
        {
            // Display error message and exit
            std::cout << "Input file did not open!" << std::endl;
            exit(EXIT_FAILURE);
        }

        // Assign k; k cannot be greater than the number of Points read in
        if (numClusters <= __point_space->getSize())
        {
            __k = numClusters;
        }
        else
        {
            std::cout << "k cannot be greater than the number of Points read in!" << std::endl;
            exit(EXIT_FAILURE);
        }

        // Create empty array of Centroids
        Clustering::PointPtr *centroidArray = new Clustering::PointPtr[__k];

        // Pick Centroids from Cluster
        std::cout << "Picking Points to use as Centroids..." << std::endl;
        __point_space->pickPoints(__k, centroidArray);

        // Create dynamic array of k ClusterPtrs
        __kClusterArray = new ClusterPtr[__k];

        // Set point_space as first Cluster in array
        __kClusterArray[0] = new Cluster(*__point_space);

        for (int i = 1; i < __k; i++)
        {
            __kClusterArray[i] = new Cluster(numDims);
        }

        // Set Centroids and dimensions of dynamic Clusters
        for (int i = 0; i < __k; i++)
        {
            __kClusterArray[i]->setCentroid((*centroidArray[i]));
            std::cout << "Initial kCluster " << (i+1) << " Centroid: " << __kClusterArray[i]->getCentroid() << std::endl;
        }

        // Create variables to hold Clustering score and scoreDiff
        int iterations = 0; // Keep track of iterations
        double score, scoreDiff;
        scoreDiff = SCORE_DIFF_THRESHOLD + 1; // Ensures we iterate at least once

        /****************************************/

        /* Perform Clustering */
        std::cout << "\nRunning Clustering algorithm..." << std::endl << std::endl;
        // Loop until scoreDiff < SCORE_DIFF_THRESHOLD
        while(SCORE_DIFF_THRESHOLD < scoreDiff)
        {
            // Loop through all Clusters
            for (int i = 0; i < __k; i++)
            {
                // Current Cluster variable
                ClusterPtr current = __kClusterArray[i];
                ListNodePtr curr = __kClusterArray[i]->getHead();

                // Loop through all Points
                while (curr != nullptr)
                {
                    // Point variable
                    PointPtr pt = curr->p;

                    // Other Cluster variable
                    ClusterPtr other = nullptr;

                    // Find the smallest distance between current Point and a Centroid
                    double minDist = DBL_MAX;
                    Point currCentroid(numDims);

                    for (int j = 0; j < __k; j++)
                    {
                        // Calculate distance from current Point to each Centroid
                        double currDist = curr->p->distanceTo(__kClusterArray[j]->getCentroid());

                        if (minDist > currDist)
                        {
                            // Save the nearest Centroid
                            minDist = currDist;
                            currCentroid = __kClusterArray[j]->getCentroid();
                        }
                    }

                    if (currCentroid != current->getCentroid())
                    {
                        // Search for Cluster that has matching Centroid
                        for (int h = 0; h < __k; h++)
                        {
                            if (currCentroid == __kClusterArray[h]->getCentroid())
                            {
                                other = __kClusterArray[h];
                            }
                        }

                        // Perform move
                        Cluster::Move *m = new Cluster::Move(*pt, current, other);
                        delete m;
                    }
                    curr = curr->next;
                }
            }

            std::cout << std::endl;

            // If Centroids are invalid, recalculate Centroids for each Cluster
            std::cout << "Recalculating Centroids..." << std::endl;
            for (int i = 0; i < __k; i++)
            {
                if (!__kClusterArray[i]->getCentroidValidity())
                {
                    __kClusterArray[i]->calcCentroid();
                }
            }

            // Compute new clusteringScore
            score = computeClusteringScore(__kClusterArray);

            // Compute absolute difference and set scoreDiff
            scoreDiff = fabs(SCORE_DIFF_THRESHOLD - score);

            iterations++; // Increment iterations
        }
        /****************************************/

        /* Output results to console */
        std::cout << "\nClustering took " << iterations << " iterations to complete!" << std::endl;

        for (int i = 0; i < __k; i++)
        {
            std::cout << "\nkCluster " << i+1 << " (FINAL):\n"
            << "Centroid: " << __kClusterArray[i]->getCentroid() << "\n" << *__kClusterArray[i];
        }

        /* Write results to file */
        // Write out the Clustering results to a file
        std::ofstream outFile(outputFile); // Open output file

        if (outFile)
        {
            std::cout << "\nOutput file opened!" << std::endl;
            std::cout << "Writing data to output file..." << std::endl;

            // Loop through cluster array and output to file
            for (int i = 0; i < __k; i++)
            {
                outFile << *__kClusterArray[i] << std::endl;
            }

            std::cout << "Output successfully written to file!" << std::endl;
        }
        else
        {
            // Display error message and exit
            std::cout << "Output file did not open!" << std::endl;
            exit(EXIT_FAILURE);
        }

        /* Cleanup */
        // All Clusters and Points are destroyed by KMeans destructor
        // Destroy centroidArray
        std::cout << "\nPerforming cleanup..." << std::endl;

        for (int i = 0; i < __k; i++)
        {
            delete centroidArray[i];
        }

        delete [] centroidArray;

        std::cout << "Centroid array destroyed!" << std::endl;
        /****************************************/
    }

    // Destructor
    KMeans::~KMeans()
    {
        // Destroy point_space Cluster and all Points within
        ListNodePtr pSpace = __point_space->getHead();
        while (pSpace != nullptr)
        {
            delete pSpace->p;
            pSpace = pSpace->next;
        }
        delete __point_space;

        // Delete kClusterArray and all Points within
        for (int i = 0; i < __k; i++)
        {
            delete __kClusterArray[i];
        }
    }
    // ******************************************

    /* Member functions */
    // Implement Beta-CV criterion (coefficient of variation)
    double KMeans::computeClusteringScore(ClusterPtr *clusterArray)
    {
        double W_in = 0;
        double W_out = 0;
        double N_in = 0;
        double N_out = 0;
        double result = 0;

        // Calculate W_in: sum of intraCluster distances
        for (int i = 0; i < __k; i++)
        {
            W_in += clusterArray[i]->intraClusterDistance();
        }

        // Calculate W_out: sum of interCluster distances
        for (int i = 0; i < (__k-1); i++)
        {
            for (int j = i+1; j < __k; j++)
            {
                W_out += interClusterDistance(*clusterArray[i], *clusterArray[j]);
            }
        }

        // Calculate N_in: number of distinct intraCluster edges
        for (int i = 0; i < __k; i++)
        {
            N_in += clusterArray[i]->getClusterEdges();
        }

        // Calculate N_out: number of distinct interCluster edges
        for (int i = 0; i < (__k-1); i++)
        {
            for (int j = i+1; j < __k; j++)
            {
                N_out += interClusterEdges(*__kClusterArray[i], *__kClusterArray[j]);
            }
        }

        result = (W_in / N_in) / (W_out / N_out);

        return result;
    }
} // end namespace Clustering
