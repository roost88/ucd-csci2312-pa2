// Programming Assignment 3 - KMeans Clustering

// Author:      Dylan Lang
// Date:        20 October 2015

// Point class implementation

#include "Point.h"
#include "Cluster.h"

/* namespace wrap */
namespace Clustering
{
    /* Public member variables */
    const char Point::POINT_VALUE_DELIM = ','; // Defines Point I/O delimiter

    /* Constructors */
    Point::Point(int dimensions)
    {
        // Default to two dimensions
        if (dimensions == 0)
        {
            dimensions = 2;
        }

        // Set dimensions of Point
        dim = dimensions;

        // Create new values array
        values = new double[dim];
    }

    // Copy constructor
    Point::Point(const Point &right)
    {
        // Set dimensions
        dim = right.dim;

        // Create values array for left side
        values = new double[dim];

        // Loop to copy values from right into left
        for (int i = 0; i < dim; i++)
        {
            values[i] = right.values[i];
        }
    }

    // Overloaded assignment operator
    Point &Point::operator =(const Point &right)
    {
        // If Points already equal each other, return left side
        if (this == &right)
        {
            return *this;
        }
        // If they don't, reset values array
        else
        {
            // Delete old values
            delete [] values;

            // Set dimensions
            dim = right.dim;

            // Create new values array
            values = new double[dim];

            // Loop to copy values from right into left
            for (int i = 0; i < dim; i++)
            {
                values[i] = right.values[i];
            }
            return *this;
        }
    }
    // ******************************************

    /* Member functions */
    // Calculates distance between two points
    double Point::distanceTo(const Point &p) const
    {
        // Create variables to increment
        double sum = 0;
        double distance = 0;

        // Loop through values
        for (int i = 0; i < dim; i++)
        {
            // Compute difference between values
            double diff = values[i] - p.values[i];

            // Add square to difference to sum (will be a positive number)
            sum += diff * diff;
        }
        // Compute distance and return it
        distance = sqrt(sum);
        return distance;
    }
    // ******************************************

    /* Setters */
    void Point::setValue(int element, double value) const
    {
        if (element >= 1 && element <= dim)
        {
            values[element - 1] = value;
        }
        else
        {
            // Display error message
            std::cout << "That element does not exist in the array!" << std::endl;
        }
    }
    // ******************************************

    /* Getters */
    double Point::getValue(int element) const
    {
        if (element >= 1 && element <= dim)
        {
            return values[element - 1];
        }
        else
        {
            // Display error message
            std::cout << "That element does not exist in the array!" << std::endl;
            return 0;
        }
    }
    // ******************************************

    /* Overloaded compound assignment operators */
    Point &Point::operator *=(double d)
    {
        // Loop through values of Point
        for (int i = 0; i < dim; i++)
        {
            // Multiply values by d
            values[i] *= d;
        }
        return *this;
    }

    Point &Point::operator /=(double d)
    {
        // Check if d == 0
        if (d != 0)
        {
            // Loop through values and divide by d
            for (int i = 0; i < dim; i++)
            {
                values[i] /= d;
            }
        }
        else
        {
            // Display error message
            std::cout << "Cannot divide by 0!" << std::endl;
        }
        return *this;
    }
    // ******************************************

    /* Overloaded arithmetic operators */
    const Point Point::operator *(double d) const
    {
        // Copy left hand Point
        Point result = *this;

        // Multiply by d and return result
        result *= d;
        return result;
    }

    const Point Point::operator /(double d) const
    {
        // Copy point
        Point result = *this;

        // Divide by d and return result
        result /= d;
        return result;
    }
    // ******************************************

    /* Overloaded iostream operators */
    // Overloaded insertion operator
    std::ostream &operator <<(std::ostream &output, const Point &right)
    {
        // Output will look like: x, y, z
        // Loop through values
        for (int i = 0; i < right.dim; i++)
        {
            // Output Point values to one decimal place
            output << std::fixed << std::setprecision(1) << right.values[i];

            // Add in ',' and space if not the end of array
            if (i < (right.dim) - 1)
            {
                output << Point::POINT_VALUE_DELIM << " ";
            }
        }
        return output;
    }

    // Overloaded extraction operator
    std::istream &operator >>(std::istream &input, Point &right)
    {
        // TODO: check for proper input formatting (x,y,z,,)
        /* These are here in case we read directly from a file */
        // Create empty string
        std::string line;

        // Get next line of input and place in string
        std::getline(input, line, '\n');

        // Turn string into a stream
        std::stringstream lineStr(line);

        // Loop through comma-separated values
        for (int i = 1; i <= right.dim; i++)
        {
            // Create string to hold value
            std::string value;

            // Get the value from the stringstream
            std::getline(lineStr, value, Point::POINT_VALUE_DELIM);

            // Transform value into a double
            double val = atof(value.c_str());

            // Set Point's dimension values
            right.setValue(i, val);
        }
        return input;
    }
    // ******************************************

    /* Overloaded compound assignment operators */
    Point &operator +=(Point &left, const Point &right)
    {
        // Loop through values and add right to left
        for (int i = 0; i < right.dim; i++)
        {
            left.values[i] += right.values[i];
        }
        // Return new left side
        return left;
    }

    Point &operator -=(Point &left, const Point &right)
    {
        // Loop through values and subtract right from left
        for (int i = 0; i < left.dim; i++)
        {
            left.values[i] -= right.values[i];
        }
        // Return new left side
        return left;
    }
    // ******************************************

    /* Overloaded binary arithmetic operators */
    const Point operator +(const Point &left, const Point &right)
    {
        // Copy left hand Point
        Point result = left;

        // Loop through values and add right to new left
        for (int i = 0; i < result.dim; i++)
        {
            result.values[i] += right.values[i];
        }
        return result;
    }

    const Point operator -(const Point &left, const Point &right)
    {
        // Copy left hand Point
        Point result = left;

        // Loop through values and add right to new left
        for (int i = 0; i < result.dim; i++)
        {
            result.values[i] -= right.values[i];
        }
        return result;
    }
    // ******************************************

    /* Overloaded relational operators (bools) */
    bool operator ==(const Point &left, const Point &right)
    {
        // Loop through values
        for (int i = 0; i < left.dim; i++)
        {
            // Compare for equality
            if (left.values[i] != right.values[i])
            {
                // If values are not equal, return false
                return false;
            }
            else
            {
                // If values are equal, move on to next value
                continue;
            }
        }
        // If loop terminates without returning, return true
        return true;
    }

    bool operator !=(const Point &left, const Point &right)
    {
        // Use overloaded == operator to see if they are equal
        return !(left == right);
    }

    bool operator >(const Point &left, const Point &right)
    {
        // Loop through values
        for (int i = 0; i < left.dim; i++)
        {
            // Compare values
            if (left.values[i] > right.values[i])
            {
                // If left > right, return true
                return true;
            }
            else if (left.values[i] == right.values[i])
            {
                // If values are equal, move to next value
                continue;
            }
            else
            {
                // If left value is not >= right value, return false
                break;
            }
        }
        return false;
    }

    bool operator <(const Point &left, const Point &right)
    {
        // Use overloaded > operator to compare
        return !(left > right);
    }

    bool operator >=(const Point &left, const Point &right)
    {
        // Use overloaded > and == to compare
        return (left > right || left == right);
    }

    bool operator <=(const Point &left, const Point &right)
    {
        // Use overloaded < and == to compare
        return (left < right || left == right);
    }
} // end namespace Clustering





