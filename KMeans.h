//// Programming Assignment 4 - KMeans Clustering
//
//// Author:      Dylan Lang
//// Date:        28 October 2015
//
//// KMeans Class header file
//
//// include guard
//#ifndef CLUSTERING_KMEANS_H
//#define CLUSTERING_KMEANS_H
//
//#include <cfloat> // For DBL_MAX
//
//#include "Cluster.h"
///************************************************************/

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



/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/



///* TEMPLATE KMEANS CLASS */
///* namespace wrap */
//namespace Clustering
//{
//    /* Template declaration */
//    template <typename T, int k, int dim>
//    /************************************************************/
//    class KMeans
//    {
//    private:
//        int                                           __k;
//        T*                              __point_space; // Pointer to initial Cluster that holds all Points
//        std::vector<T>                  __kClusterArray;
//        std::unordered_map<Key, T, KeyHash, KeyEqual> __distanceMap; // Holds distances between Points
//
//    public:
//        /* Member variables */
//        static const double SCORE_DIFF_THRESHOLD;
//        /************************************************************/
//
//        /* Constructors */
//        KMeans(); // Default
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
//
//    /* Member variables */
//    template <typename T, int k, int dim>
//    const double KMeans<T, k, dim>::SCORE_DIFF_THRESHOLD = 0.8; // Must be less than 1.0 and greater than 0
//    /************************************************************/
//
//    /* Constructors */
//    template <typename T, int k, int dim>
//    KMeans<T, k, dim>::KMeans()
//    {
//        /* Setup and Initialization */
//
//        // Initialize file strings
//        std::string inputFile = "input.csv";
//        std::string outputFile = "output.csv";
//
//        // Set __k and check if it is less than or equal to zero
//        __k = k;
//
//        if (__k <= 0)
//        {
//            // Display error
//            std::cerr << "__k cannot be less than or equal to zero!\n" << "Exiting program!";
//            exit(0);
//        }
//
//        // Create a new Cluster to hold all Points
//        __point_space = new T;
//
//        // Read Points from inputFile into __point_space
//        this->readFromFile(inputFile);
//
//        // Calculate distances between all Points in __point_space and store in __distances
//        __point_space->setDistanceMap();
//
//        // Copy __point_space distances into __distanceMap
//        __distanceMap = __point_space->getMap();
//
//        // Create Centroid array and pick Points from __point_space
//        // TODO: Fix this
//        Point<T, dim> **centroidArray = new Point<T, dim>*[__k];
//        __point_space->pickPoints(__k, dim, centroidArray);
//
//        /* Initialize __kClusterArray */
//        unsigned long int res = (unsigned long int) __k;
//        __kClusterArray.reserve(res); // Reserve memory
//        __kClusterArray.push_back(*__point_space); // Add __point_space to kClusterArray
//
//        // Add __k-1 empty Clusters to kClusterArray
//        for (int i = 0; i < (__k-1); i++)
//        {
//            __kClusterArray.emplace_back(dim);
//        }
//
//        // Set Centroids of Clusters
//        for (int i = 0; i < __k; i++)
//        {
//            __kClusterArray[i].setCentroid(*centroidArray[i]);
//
//            // Display initial Centroids
//            std::cout << "Initial kCluster " << __kClusterArray[i].getID()
//            << " Centroid: " << __kClusterArray[i].getCentroid() << std::endl;
//        }
//
//        /* Run clustering algorithm */
//        this->performClustering();
//
//        // Display kClusters
//        for (int i = 0; i < __k; i++)
//        {
//            std::cout << "\nkCluster " << i+1 << " (FINAL):\n"
//            << "Centroid: " << __kClusterArray[i].getCentroid() << "\n" << __kClusterArray[i];
//        }
//
//        /* Write results to file */
//        // Write out the Clustering results to a file
//        this->writeToFile(outputFile);
//
//        /* Cleanup */
//        // All Clusters and Points are destroyed by KMeans destructor
//        // Destroy centroidArray
//        std::cout << "\nPerforming cleanup..." << std::endl;
//
//        for (int i = 0; i < __k; i++)
//        {
//            delete centroidArray[i];
//        }
//
//        delete [] centroidArray;
//
//        std::cout << "Centroid array destroyed!" << std::endl;
//    }
//    /************************************************************/
//
//    /* Member functions */
//    // Read Points from a file into __point_space
//    template <typename T, int k, int dim>
//    void KMeans<T, k, dim>::readFromFile(std::string input)
//    {
//        // Open data file and read Points into __point_space
//        std::ifstream inFile(input); // Create a new input file stream
//
//        // Check if file opened
//        if (inFile)
//        {
//            // Display confirmation message
//            std::cout << "\nInput file opened!" << std::endl;
//            std::cout << "Reading Points from input file into point_space..." << std::endl;
//
//            // Read Points from file into point_space Cluster
//            inFile >> *__point_space;
//            inFile.close();
//
//            // Display number of Points successfully imported
//            std::cout << std::endl << "Number of Points successfully read in from file: "
//            << __point_space->numberImported() << std::endl;
//
//            // Display number of Points failed to import
//            std::cout << "Number of Points that failed to read in from file: "
//            << __point_space->numberFailed() << std::endl;
//
//            // Display sorted __point_space
//            std::cout << "\npoint_space:\n" << *__point_space << std::endl;
//        }
//        else
//        {
//            // Display error message and exit
//            std::cout << "Input file did not open!" << std::endl;
//            exit(EXIT_FAILURE);
//        }
//    }
//
//    // Write output to file
//    template <typename T, int k, int dim>
//    void KMeans<T, k, dim>::writeToFile(std::string output)
//    {
//        std::ofstream outFile(output); // Open output file
//
//        if (outFile)
//        {
//            std::cout << "\nOutput file opened!" << std::endl;
//            std::cout << "Writing data to output file..." << std::endl;
//
//            // Loop through cluster array and output to file
//            for (int i = 0; i < __k; i++)
//            {
//                outFile << __kClusterArray[i] << std::endl;
//            }
//
//            std::cout << "Output successfully written to file!" << std::endl;
//        }
//        else
//        {
//            // Display error message and exit
//            std::cout << "Output file did not open!" << std::endl;
//            exit(EXIT_FAILURE);
//        }
//    }
//
//    // Run clustering algorithm
//    template <typename T, int k, int dim>
//    void KMeans<T, k, dim>::performClustering()
//    {
//        // Create variables to hold Clustering score and scoreDiff
//        int iterations = 0; // Keep track of iterations
//        double score, scoreDiff;
//        scoreDiff = SCORE_DIFF_THRESHOLD + 2; // Ensures we iterate at least once
//
//        std::cout << "\nRunning Clustering algorithm..." << std::endl << std::endl;
//
//        // STEP 1 - Loop until scoreDiff < SCORE_DIFF_THRESHOLD
//        while(SCORE_DIFF_THRESHOLD < scoreDiff)
//        {
//            // STEP 2 - Loop through all Clusters
//            for (int i = 0; i < __k; i++)
//            {
//                // Copy forward list of current Cluster[i]
//                auto list = __kClusterArray[i].getHead();
//
//                // Create iterator for above list
//                auto pos = list.begin();
//
//                // STEP 3 - Loop through all Points in current Cluster[i]
//                while (pos != list.end())
//                {
//                    double minDist = DBL_MAX; // Will store smallest distance found from a Point to a Centroid
//
//                    int centCounter = 0; // Will store index number for Centroid corresponding to minDist
//
//                    // Loop through all Clusters (again)
//                    for (int j = 0; j < __k; j++)
//                    {
//                        // STEP 4 - Calculate distance from current Point in Cluster[i] to each Centroid
//                        double currDist = pos->distanceTo(__kClusterArray[j].getCentroid());
//
//                        // Save the smallest difference between current Point and whichever Centroid
//                        if (minDist > currDist)
//                        {
//                            minDist = currDist; // Save smallest distance each iteration
//                            centCounter = j; // Save index of Cluster that has closest Centroid
//                        }
//                    }
//
//                    // STEP 5 - Check if Centroid is not equal to the Centroid of the current Cluster[i]
//                    if (__kClusterArray[centCounter].getCentroid() != __kClusterArray[i].getCentroid())
//                    {
//                        int count = 0; // Will store
//
//                        // Search for Cluster that has matching Centroid
//                        for (int h = 0; h < __k; h++)
//                        {
//                            if (__kClusterArray[centCounter].getCentroid() == __kClusterArray[h].getCentroid())
//                            {
//                                count = h;
//                            }
//                        }
//
//                        // STEP 6 - Move current Point from current Cluster [i] to Cluster with closest Centroid
//                        // TODO: Fix this
//                        T::Move *m = new T::Move(*pos, &__kClusterArray[i], &__kClusterArray[count]);
//                        delete m;
//                    }
//
//                    // Increment iterator
//                    pos++;
//                }
//            }
//
//            // If Centroids are invalid, recalculate Centroids for each Cluster
//            std::cout << "Recalculating Centroids..." << std::endl;
//            for (int i = 0; i < __k; i++)
//            {
//                if (!__kClusterArray[i].getCentroidValidity())
//                {
//                    try
//                    {
//                        __kClusterArray[i].calcCentroid();
//                    }
//                    catch (RemoveFromEmptyEx e)
//                    {
//                        std::cerr << "In KMeans recalculate Centroids - " << e << std::endl;
//                    }
//                }
//            }
//
//            try
//            {
//                // Compute new clusteringScore
//                score = computeClusteringScore();
//
//                // Compute absolute difference and set scoreDiff
//                scoreDiff = fabs(SCORE_DIFF_THRESHOLD - score);
//
//                std::cout << "scoreDiff: " << scoreDiff << std::endl;
//            }
//            catch (DivideByZeroEx e)
//            {
//                // If a DivideByZeroEx is caught, it means that all Clusters only contain one Point
//                // so the program must break out of the Clustering algorithm
//                std::cerr << "In KMeans computeClusteringScore - " << e << std::endl;
//                break;
//            }
//
//            iterations++; // Increment iterations
//        }
//
//        // Output iterations
//        std::cout << "\nClustering took " << iterations << " iterations to complete!" << std::endl;
//    }
//
//    // Implement Beta-CV criterion (coefficient of variation)
//    template <typename T, int k, int dim>
//    double KMeans<T, k, dim>::computeClusteringScore()
//    {
//        double W_in = 0;
//        double W_out = 0;
//        double N_in = 0;
//        double N_out = 0;
//        double result = 0;
//
//        // Calculate W_in: sum of intraCluster distances (distances between Points within Cluster)
//        for (int i = 0; i < __k; i++)
//        {
//            W_in += __kClusterArray[i].intraClusterDistance();
//        }
//
//        // Calculate W_out: sum of interCluster distances (distances between Points between Clusters)
//        for (int i = 0; i < (__k-1); i++)
//        {
//            for (int j = i+1; j < __k; j++)
//            {
//                W_out += interClusterDistance(__kClusterArray[i], __kClusterArray[j], __distanceMap);
//            }
//        }
//
//        // Calculate N_in: number of distinct intraCluster edges
//        // (every two distinct Points within a Cluster have an imaginary edge between them)
//        for (int i = 0; i < __k; i++)
//        {
//            N_in += __kClusterArray[i].getClusterEdges();
//        }
//
//        // Calculate N_out: number of distinct interCluster edges
//        // (every two distinct Points between Clusters have an imaginary edge between them)
//        for (int i = 0; i < (__k-1); i++)
//        {
//            for (int j = i+1; j < __k; j++)
//            {
//                N_out += interClusterEdges(__kClusterArray[i], __kClusterArray[j]);
//            }
//        }
//
//        if (N_in != 0 && N_out != 0)
//            result = (W_in / N_in) / (W_out / N_out);
//
//        else
//            throw DivideByZeroEx();
//
//        std::cout << "Clustering Score: " << result << std::endl;
//
//        return result;
//    }
//    /************************************************************/
//} // end Clustering namespace
//
//#endif //CLUSTERING_KMEANS_H