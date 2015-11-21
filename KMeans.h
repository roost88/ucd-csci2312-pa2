// Programming Assignment 4 - KMeans Clustering

// Author:      Dylan Lang
// Date:        28 October 2015 - 21 November 2015

// KMeans Class header file

// include guard
#ifndef CLUSTERING_KMEANS_H
#define CLUSTERING_KMEANS_H

#include "Cluster.h"

#include <cfloat> // For DBL_MAX
/************************************************************/

/* TEMPLATE KMEANS CLASS */
/* namespace wrap */
namespace Clustering
{
    /* KMeans Class */
    template <typename T, int k, int dim>
    class KMeans
    {
    private:
        int                                                                 __k;                // # of Clusters
        Cluster<Point<T, dim>, dim>*                                        __point_space;      // Holds all Points
        std::vector<Clustering::Cluster<Clustering::Point<T, dim>, dim>>    __kClusterArray;    // Holds k Clusters
        std::unordered_map<Key, double, KeyHash, KeyEqual>                  __distanceMap;      // Holds distances

    public:
        /* Member variables */
        static const double SCORE_DIFF_THRESHOLD;
        /************************************************************/

        /* Constructors */
        KMeans();                                               // Default
        ~KMeans() { delete __point_space; }                     // Destructor
        /************************************************************/

        /* Member functions */
        void readFromFile(std::string);                         // Read Points from a file
        void writeToFile(std::string);                          // Write Points to file
        void performClustering();                               // Run clustering algorithm
        double computeClusteringScore();                        // Calculate clustering score using BetaCV criterion
        /************************************************************/
    };

    /* Member variables */
    template <typename T, int k, int dim>
    const double KMeans<T, k, dim>::SCORE_DIFF_THRESHOLD = 0.6; // Must be less than 1.0 and greater than 0
    /************************************************************/

    /* Constructors */
    template <typename T, int k, int dim>
    KMeans<T, k, dim>::KMeans()
    {
        /* Setup and Initialization */

        std::string inputFile = "input.csv";                    // Insert input file string name here
        std::string outputFile = "output.csv";                  // Insert output file string name here

        __k = k;                                                // Initialize k

        // Check if k is less than or equal to 0
        if (__k <= 0)
        {
            std::cerr << "__k cannot be less than or equal to zero!\n" << "Exiting program!";
            exit(0);
        }

        __point_space = new Cluster<Point<T, dim>, dim>;            // Create a new Cluster to hold all Points

        this->readFromFile(inputFile);                              // Read Points from inputFile into __point_space

        std::cout << std::endl << "Number of Points SUCCESSFULLY read in from file: "
        << __point_space->numberImported() << std::endl;            // Display imported Points

        // Display number of Points failed to import
        std::cout << "Number of Points that FAILED to read in from file: "
        << __point_space->numberFailed() << std::endl;              // Display failed Points

        // Check number of Points imported
        if (__point_space->numberImported() <= 0)
        {
            std::cout << "No Points were read in successfully!" << std::endl;
            std::cout << "Exiting program!";
            exit(0);                                                // If no Points read in successfully, exit program
        }

        __point_space->sort();                                      // Sort __point_space

        __point_space->setDistanceMap();                            // Initialize distances map for __point_space

        __distanceMap = __point_space->getMap();                    // Initialize __distance map for KMeans

        Point<T, dim> **centroidArray = new Point<T, dim>*[__k];    // Create Centroid array
        __point_space->pickPoints(__k, dim, centroidArray);         // Pick Points for Centroids

        /* Initialize __kClusterArray */
        unsigned long int res = (unsigned long int) __k;            // Variable for reserve memory
        __kClusterArray.reserve(res);                               // Reserve memory
        __kClusterArray.push_back(*__point_space);                  // Add __point_space to kClusterArray

        for (int i = 0; i < (__k-1); i++)
            __kClusterArray.emplace_back(Cluster<Point<T, dim>, dim>());   // Create k-1 empty clusters

        for (int i = 0; i < __k; i++)
        {
            __kClusterArray[i].setCentroid(*centroidArray[i]);             // Set Centroids of Clusters

            // Uncomment to display initial Centroids
//            std::cout << "Initial kCluster " << __kClusterArray[i].getID()
//                << " Centroid: " << __kClusterArray[i].getCentroid() << std::endl;
        }

        /************************************************************/

        /* Run clustering algorithm */
        performClustering();

        // Uncomment to display kClusters to console
//        for (int i = 0; i < __k; i++)
//        {
//            std::cout << "\nkCluster " << __kClusterArray[i].getID() << " (FINAL):" << std::endl;
//            std::cout << "Centroid: " << __kClusterArray[i].getCentroid() << "\n" << __kClusterArray[i];
//        }

        /************************************************************/

        /* Write results to file */
        this->writeToFile(outputFile);

        /************************************************************/

        /* Cleanup */
        std::cout << "\nPerforming cleanup..." << std::endl;

        for (int i = 0; i < __k; i++)
            delete centroidArray[i];        // Delete Points in Centroid array

        delete [] centroidArray;            // Destroy Centroid array

        std::cout << "Centroid array destroyed!" << std::endl;

    } // End KMeans constructor
    /******************************************************************************************************************/

    /* Member functions */
    // METHOD - Read Points from a file into __point_space
    template <typename T, int k, int dim>
    void KMeans<T, k, dim>::readFromFile(std::string input)
    {
        std::ifstream inFile(input);                                // Open input file

        // Check if file opened
        if (inFile)
        {
            std::cout << "\nInput file opened!" << std::endl;       // Display confirmation message
            std::cout << "Reading Points from input file into point_space..." << std::endl;

            inFile >> *__point_space;                               // Read Points from file into point_space Cluster
            inFile.close();                                         // Close input file file
        }
        else
        {
            // If file doesn't open
            std::cout << "Input file did not open!" << std::endl;   // Display error message and exit
            exit(EXIT_FAILURE);
        }
    } // End readFromFile


    // METHOD - Write output to file
    template <typename T, int k, int dim>
    void KMeans<T, k, dim>::writeToFile(std::string output)
    {
        std::ofstream outFile(output);                              // Open output file

        // Check if file opened
        if (outFile)
        {
            std::cout << "\nOutput file opened!" << std::endl;      // Display confirmation message
            std::cout << "Writing data to output file..." << std::endl;

            // Loop through cluster array and output to file
            for (int i = 0; i < __k; i++)
                outFile << __kClusterArray[i] << std::endl;         // Output Clusters to file

            std::cout << "Output successfully written to file!" << std::endl;
        }
        else
        {
            // If file doesn't open
            std::cout << "Output file did not open!" << std::endl;  // Display error message and exit
            exit(EXIT_FAILURE);
        }
    } // End writeToFile


    // METHOD - Run clustering algorithm
    template <typename T, int k, int dim>
    void KMeans<T, k, dim>::performClustering()
    {
        int iterations = 0;                     // Keep track of iterations
        double score, scoreDiff;                // Create variables
        scoreDiff = SCORE_DIFF_THRESHOLD + 1;   // Ensures we iterate at least once

        std::cout << "\nRunning Clustering algorithm..." << std::endl << std::endl;

        // STEP 1 - Loop until scoreDiff < SCORE_DIFF_THRESHOLD
        while(SCORE_DIFF_THRESHOLD < scoreDiff)
        {
            // STEP 2 - Loop through all Clusters
            for (int i = 0; i < __k; i++)
            {

                auto list = __kClusterArray[i].getHead();   // Copy forward list of current Cluster[i]
                auto pos = list.begin();                    // Iterator set to first Point in list

                // STEP 3 - Loop through all Points in current Cluster[i]
                while (pos != list.end())
                {
                    double minDist = DBL_MAX;               // Stores distance from Point to Centroid

                    int centCounter = 0;                    // Stores index of closest Centroid

                    // Loop through all Clusters (again)
                    for (int j = 0; j < __k; j++)
                    {
                        // STEP 4 - Calculate distance from current Point in Cluster[i] to each Centroid
                        double currDist = pos->distanceTo(__kClusterArray[j].getCentroid());

                        // Save the smallest difference between current Point and whichever Centroid
                        if (minDist > currDist)
                        {
                            minDist = currDist;             // Save smallest distance each iteration
                            centCounter = j;                // Save index of Cluster that has closest Centroid
                        }
                    }

                    // STEP 5 - Check if Centroid is not equal to the Centroid of the current Cluster[i]
                    if (__kClusterArray[centCounter].getCentroid() != __kClusterArray[i].getCentroid())
                    {
                        int count = 0;                      // Stores index of Cluster with matching Centroid

                        // Search for Cluster that has matching Centroid
                        for (int h = 0; h < __k; h++)
                        {
                            if (__kClusterArray[centCounter].getCentroid() == __kClusterArray[h].getCentroid())
                            {
                                count = h;                  // Save index of Cluster with matching Centroid
                            }
                        }

                        // STEP 6 - Move current Point from current Cluster [i] to Cluster with closest Centroid
                        // TODO: Why do we have to use typename for this?
                        typename Cluster<Point<T, dim>, dim>::Move *m = new typename Cluster<Point<T, dim>, dim>
                        ::Move(*pos, &__kClusterArray[i], &__kClusterArray[count]);

                        delete m;
                    }

                    pos++;      // Increment iterator
                }
            }

            // If Centroids are invalid, recalculate Centroids for each Cluster
            for (int i = 0; i < __k; i++)
            {
                if (!__kClusterArray[i].getCentroidValidity())
                {
                    try
                    {
                        __kClusterArray[i].sort();          // Sort Cluster
                        __kClusterArray[i].calcCentroid();  // Recalculate Centroid of each Cluster
                    }
                    catch (RemoveFromEmptyEx e)
                    {
                        std::cout << "In KMeans recalculate Centroids: " << e << std::endl;
                    }
                }
            }

            try
            {
                score = computeClusteringScore();               // Compute new clusteringScore
                scoreDiff = fabs(SCORE_DIFF_THRESHOLD - score); // Compute difference and set scoreDiff

                // Uncomment to display scoreDiff
//                std::cout << "scoreDiff: " << scoreDiff << std::endl;
            }
            catch (DivideByZeroEx e)
            {
                /* If a DivideByZeroEx is caught, it means that all Clusters only contain one Point
                ** so the program must break out of the Clustering algorithm */
                std::cout << "In KMeans computeClusteringScore: " << e << std::endl;
                break;
            }

            iterations++; // Increment iterations
        }

        // Output iterations
        std::cout << "\nClustering took " << iterations << " iterations to complete!" << std::endl;
    } // End performClustering


    // METHOD - Implement Beta-CV criterion (coefficient of variation)
    template <typename T, int k, int dim>
    double KMeans<T, k, dim>::computeClusteringScore()
    {
        double W_in = 0;        // Numerator for intraCluster distances
        double W_out = 0;       // Denominator for interCluster distances
        double N_in = 0;        // Numerator for intraCluster edges
        double N_out = 0;       // Denominator interCluster edges
        double result = 0;      // = (W_in / W_out) / (N_in / N_out)

        // Calculate W_in: sum of intraCluster distances (distances between Points within Cluster)
        for (int i = 0; i < __k; i++)
        {
            W_in += __kClusterArray[i].intraClusterDistance();
        }

        // Calculate W_out: sum of interCluster distances (distances between Points between Clusters)
        for (int i = 0; i < (__k-1); i++)
        {
            for (int j = i+1; j < __k; j++)
            {
                W_out += interClusterDistance(__kClusterArray[i], __kClusterArray[j], __distanceMap);
            }
        }

        // Calculate N_in: number of distinct intraCluster edges
        // (every two distinct Points within a Cluster have an imaginary edge between them)
        for (int i = 0; i < __k; i++)
        {
            N_in += __kClusterArray[i].getClusterEdges();
        }

        // Calculate N_out: number of distinct interCluster edges
        // (every two distinct Points between Clusters have an imaginary edge between them)
        for (int i = 0; i < (__k-1); i++)
        {
            for (int j = i+1; j < __k; j++)
            {
                N_out += interClusterEdges(__kClusterArray[i], __kClusterArray[j]);
            }
        }

        // Check denominators for zeros
        if (N_in == 0 || N_out == 0)
            throw DivideByZeroEx();

        result = (W_in / N_in) / (W_out / N_out);   // Calculate result

        // Uncomment to display clustering score
//        std::cout << "Clustering Score: " << result << std::endl;

        return result;
    } // End computeClusteringScore

} // end Clustering namespace
#endif //CLUSTERING_KMEANS_H


/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/


///* NON-TEMPLATE KMEANS CLASS */
///* namespace wrap */
//namespace Clustering
//{
//    class KMeans
//    {
//    private:
//        unsigned long int                                   __k; // Holds k (number of Clusters)
//        Cluster*                                            __point_space; // Holds all Points
//        std::vector<Cluster>                                __kClusterArray; // Holds k Clusters
//        std::unordered_map<Key, double, KeyHash, KeyEqual>  __distanceMap; // Holds distances between Points
//
//    public:
//        /* Member variables */
//        static const double SCORE_DIFF_THRESHOLD;
//        /************************************************************/
//
//        /* Constructors */
//        KMeans(unsigned long int numClusters, unsigned long int numDims); // Default
//        ~KMeans() { delete __point_space; } // Destructor
//        /************************************************************/
//
//        /* Member functions */
//        // Read Points from a file
//        void readFromFile(std::string);
//
//        // Write Points to file
//        void writeToFile(std::string);
//
//        // Run clustering algorithm
//        void performClustering();
//
//        // Calculate clustering score
//        // Implements Beta-CV criterion (coefficient variation)
//        double computeClusteringScore();
//        /************************************************************/
//    };
//} // end Clustering namespace
//
//#endif //CLUSTERING_KMEANS_H