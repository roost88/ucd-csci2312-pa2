// Programming Assignment 2 - Three Dimensional Triangle

// Author:      Dylan Lang
// Date:        10 Sept 2015

#include <iostream>
#include "Point.h"
#include "Cluster.h"

// Function prototypes
void testPoint();
void testCluster();

int main()
{
    testPoint();
    testCluster();

    return 0;
}

// Function definitions
void testPoint()
{
    std::cout << "Testing Point implementation" << std::endl;

    /* Constructors */
    Clustering::Point p1(3); // Creates a Point p1 with dim = 3 and no values.
    p1.setValue(1, 5); p1.setValue(2, 36); p1.setValue(3, 103);

    std::cout << "p1: " << p1 << std::endl;

    Clustering::Point p2(p1); // Copies p1 into p2
    std::cout << "p2: " << p2 << std::endl; // Output values of p2

    Clustering::Point p3 = p2; // Assigns members of p2 to p3
    // Output values of p3
    std::cout << "p3: " << p3 << std::endl;

    Clustering::Point p4(3); // Create a new Point p4 with 3 dimensions
    p4.setValue(1, 26); // Sets first value of p4 to 26
    p4.setValue(2, 158); // Sets second value of p4 to 158
    p4.setValue(3, 14); // Sets third value of p4 to 14

    std::cout << "p4: " << p4 << std::endl;

    /* Other member functions */
    Clustering::Point p5(3); // Create a new Point p5 with 3 dimensions
    p5.setValue(1, 306);
    p5.setValue(2, 123);
    p5.setValue(3, 52);

    std::cout << "p5: " << p5 << std::endl;

    /* Output distance between Points p4 and p5 - should be 284.726 */
    std::cout << "Distance between p4 and p5: " << p4.distanceTo(p5) << std::endl;

    /* Overloaded compound assignment operators */
    Clustering::Point p6(3);
    p6.setValue(1, 3);
    p6.setValue(2, 3);
    p6.setValue(3, 3);

    std::cout << "p6: " << p6 << std::endl;

    p6 *= 2; // Multiply each p6 value by 2
    // All values of p6 are now equal to 6
    std::cout << "p6 *= 2: " << p6 << std::endl;

    p6 /= 3; // Divide each p6 value by 3
    // All values of p6 are now equal to 2
    std::cout << "p6 /= 3: " << p6 << std::endl;

    /* Overloaded arithmetic operators */
    Clustering::Point p7 = p6 * 5; // Create a new Point p7 which is equal to all p6 values multiplied by 5
    // All values of p7 are now equal to 10
    std::cout << "p7 = p6 * 5: " << p7 << std::endl;

    Clustering::Point p8 = p7 / 2; // Create new Point p8 which is equal to p7 divided by 2
    // All values of p8 are now equal to 5
    std::cout << "p8 = p7 / 2: " << p8 << std::endl;

    /* Overloaded compound assignment operators */
    p7 += p8; // Add values of p8 to p7
    // All values of p7 are now equal to 15
    std::cout << "p7 += p8: " << p7 << std::endl;

    p7 -= p6; // Subtract values of p6 from p7
    // All values of p7 are now equal to 13
    std::cout << "p7 -= p6: " << p7 << std::endl;

    /* Overloaded binary arithmetic operators */
    Clustering::Point p9 = p8 - p6; // Point p9 is equal to the values of p8 minus p6
    // All values of p9 are equal to 3
    std::cout << "p9 = p8 - p6: " << p9 << std::endl;

    Clustering::Point p10 = p9 + p6; // Point p10 is equal to the values of p9 minus p6
    // All values of p10 are equal to 5
    std::cout << "p10 = p9 + p6: " << p10 << std::endl << std::endl;

    /* Overloaded comparison operators */
    std::cout << "Is p9 == p6: " << (p9 == p6) << std::endl; // Outputs 0 because statement is FALSE
    std::cout << "Is p10 == p10: " << (p10 == p10) << std::endl << std::endl; // Outputs 1 because statement is TRUE

    std::cout << "Is p9 != p6: " << (p9 != p6) << std::endl; // Outputs 1 because statement is TRUE
    std::cout << "Is p9 != p9: " << (p9 != p9) << std::endl << std::endl; // Outputs 0 because statement is FALSE

    std::cout << "Is p9 > p6: " << (p9 > p6) << std::endl; // Outputs 1 because statement is TRUE
    std::cout << "Is p9 < p6: " << (p9 < p6) << std::endl << std::endl; // Outputs 0 because statement is FALSE

    std::cout << "Is p7 >= p9: " << (p7 >= p9) << std::endl; // Outputs 1 because statement is TRUE
    std::cout << "Is p9 >= p7: " << (p9 >= p7) << std::endl; // Outputs 0 because statement is FALSE
    std::cout << "Is p9 >= p9: " << (p9 >= p9) << std::endl << std::endl; // Outputs 1 because statement is TRUE

    std::cout << "Is p9 <= p7: " << (p9 <= p7) << std::endl; // Outputs 1 because statement is TRUE
    std::cout << "Is p7 <= p9: " << (p7 <= p9) << std:: endl; // Outputs 0 because statement is FALSE
    std::cout << "Is p7 <= p7: " << (p7 <= p7) << std::endl;  // Outputs 1 because statement is TRUE

    std::cout << "Point testing completed." << std::endl << std::endl;
}

void testCluster()
{
    /* Create some new Points */
    Clustering::Point p3(3); p3.setValue(1, 5); p3.setValue(2, 36); p3.setValue(3, 103);
    Clustering::Point p4(3); p4.setValue(1, 26); p4.setValue(2, 158); p4.setValue(3, 14);
    Clustering::Point p5(3); p5.setValue(1, 306); p5.setValue(2, 123); p5.setValue(3, 52);
    Clustering::Point p6(3); p6.setValue(1, 2); p6.setValue(2, 2); p6.setValue(3, 2);
    Clustering::Point p7(3); p7.setValue(1, 13); p7.setValue(2, 13); p7.setValue(3, 13);
    Clustering::Point p9(3); p9.setValue(1, 3); p9.setValue(2, 3); p9.setValue(3, 3);
    Clustering::Point p10(3); p10.setValue(1, 5); p10.setValue(2, 5); p10.setValue(3, 5);

    std::cout << "Testing Cluster implementation" << std::endl;

    /* Cluster.cpp testing */
    std::cout << "p3: " << p3 << std::endl;
    std::cout << "p4: " << p4 << std::endl;
    std::cout << "p5: " << p5 << std::endl;
    std::cout << "p6: " << p6 << std::endl;
    std::cout << "p7: " << p7 << std::endl;
    std::cout << "p9: " << p9 << std:: endl;
    std::cout << "p10: " << p10 << std::endl << std::endl;

    Clustering::Cluster c1; // Default constructor

    // Add Points to Cluster
    c1.add(&p3);
    c1.add(&p4);

    Clustering::Cluster c2(c1); // Copy constructor
    Clustering::Cluster c3 = c2; // Assignment operator

    // These Clusters should all be the same
    std::cout << "c1: " << c1 << std::endl;
    std::cout << "c2: " << c2 << std::endl;
    std::cout << "c3: " << c3 << std::endl;

    // Comparison operators
    std::cout << "c1 == c2: " << (c1 == c2) << std::endl; // returns TRUE
    std::cout << "c1 != c2: " << (c1 != c2) << std::endl; // returns FALSE
    std::cout << "c1: " << c1 << std::endl;

    // Assignment operators (with Clusters and Points)
    std::cout << "c2 += p5: " << (c2 += p5) << std::endl;
    std::cout << "c1: " << c1 << std::endl;
    std::cout << "c1 -= p4: " << (c1 -= p4) << std::endl;

    Clustering::Cluster c4;
    c4.add(&p6);
    c4.add(&p7);
    c4.add(&p9);

    std::cout << "c1: " << c1;
    std::cout << "c2: " << c2;
    std::cout << "c3: " << c3;
    std::cout << "c4: " << c4 << std::endl;

    // Addition and subtraction operator (with Clusters)
    std::cout << "c2 + c4: " << (c2 + c4);
    std::cout << "c2 - c1: " << (c2 - c1);

    // Addition and Subtraction operator (with Clusters and Points)
    std::cout << "c1 + p10: " << (c1 + &p10);
    std::cout << "c1 - p3: " << (c1 - &p3) << std::endl;

    std::cout << "c1: " << c1;
    std::cout << "c2: " << c2;
    std::cout << "c3: " << c3;
    std::cout << "c4: " << c4 << std::endl;

    // Assignment operators (with Clusters only)
    c4 += c1;
    std::cout << "c4 += c1: " << c4;
    c2 -= c3;
    std::cout << "c2 -= c3: " << c2;

    std::cout << "Cluster testing complete." << std::endl;
}


