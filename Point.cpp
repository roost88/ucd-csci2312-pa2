// Programming Assignment 4 - KMeans Clustering

// Author:      Dylan Lang
// Date:        28 October 2015

// Point class implementation

#include "Point.h"
#include "Cluster.h"

/* namespace wrap */
namespace Clustering
{
    /* Public member variables */
    unsigned int Point::__idGenerator = 1; // Initialize Point ID value to 1
    const char Point::POINT_VALUE_DELIM = ','; // Defines Point I/O delimiter

    /* Constructors */
    Point::Point(unsigned long int dimensions)
    {
        // TODO: Throw DimensionalityMismatchEx exception
        // Create new Point ID
        __id = __idGenerator++;

        // Set dimensions of Point
        __dim = dimensions;

        // Set capacity of __values vector
        __values.reserve(__dim);
    }

    // Copy constructor
    Point::Point(const Point &right)
    {
        // Copy Point ID
        __id = right.getID();

        // Set dimensions
        __dim = right.getDim();

        // Set capacity of __values vector
        __values.reserve(__dim);

        // Loop to copy __values from right into left
        for (int i = 0; i < __dim; i++)
        {
            __values[i] = right.__values[i];
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
        // If they don't, reset __values array
        else
        {
            __id = right.getID();

            // Clear old __values
            __values.clear();

            // Set dimensions
            __dim = right.getDim();

            // Set capacity of __values vector
            __values.reserve(__dim);

            // Loop to copy __values from right into left
            for (int i = 0; i < __dim; i++)
            {
                __values[i] = right.__values[i];
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

        // Loop through __values
        for (int i = 0; i < __dim; i++)
        {
            // Compute difference between __values
            double diff = __values[i] - p.__values[i];

            // Add square to difference to sum (will be a positive number)
            sum += diff * diff;
        }
        // Compute distance and return it
        distance = sqrt(sum);
        return distance;
    }
    // ******************************************

    /* Setters */
    void Point::setValue(int element, double value)
    {
        if (element >= 1 && element <= __dim)
        {
            __values[element - 1] = value;
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
        if (element >= 1 && element <= __dim)
        {
            return __values[element - 1];
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
        // Loop through __values of Point
        for (int i = 0; i < __dim; i++)
        {
            // Multiply __values by d
            __values[i] *= d;
        }
        return *this;
    }

    Point &Point::operator /=(double d)
    {
        // Check if d == 0
        if (d != 0)
        {
            // Loop through __values and divide by d
            for (int i = 0; i < __dim; i++)
            {
                __values[i] /= d;
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
        // Loop through __values
        for (int i = 0; i < right.getDim(); i++)
        {
            // Output Point __values to one decimal place
            output << std::fixed << std::setprecision(1) << right.__values[i];

            // Add in ',' and space if not the end of array
            if (i < (right.getDim()) - 1)
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

        // Loop through comma-separated __values
        for (int i = 1; i <= right.getDim(); i++)
        {
            // Create string to hold value
            std::string value;

            // Get the value from the stringstream
            std::getline(lineStr, value, Point::POINT_VALUE_DELIM);

            // Transform value into a double
            double val = atof(value.c_str());

            // Set Point's dimension __values
            right.setValue(i, val);
        }
        return input;
    }
    // ******************************************

    /* Overloaded compound assignment operators */
    Point &operator +=(Point &left, const Point &right)
    {
        // Loop through __values and add right to left
        for (int i = 0; i < right.getDim(); i++)
        {
            left.__values[i] += right.__values[i];
        }
        // Return new left side
        return left;
    }

    Point &operator -=(Point &left, const Point &right)
    {
        // Loop through __values and subtract right from left
        for (int i = 0; i < left.getDim(); i++)
        {
            left.__values[i] -= right.__values[i];
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

        // Loop through __values and add right to new left
        for (int i = 0; i < result.getDim(); i++)
        {
            result.__values[i] += right.__values[i];
        }
        return result;
    }

    const Point operator -(const Point &left, const Point &right)
    {
        // Copy left hand Point
        Point result = left;

        // Loop through __values and add right to new left
        for (int i = 0; i < result.getDim(); i++)
        {
            result.__values[i] -= right.__values[i];
        }
        return result;
    }
    // ******************************************

    /* Overloaded relational operators (bools) */
    bool operator ==(const Point &left, const Point &right)
    {
        // Compare __id and __values of Points
        if (left.getID() == right.getID())
        {
            // Loop through __values
            for (int i = 0; i < left.getDim(); i++)
            {
                // Compare for equality
                if (left.__values[i] != right.__values[i])
                {
                    // If __values are not equal, return false
                    return false;
                }
            }
            // If loop terminates without returning, return true
            return true;
        }
        else
        {
            return false;
        }
    }

    bool operator !=(const Point &left, const Point &right)
    {
        // Use overloaded == operator to see if they are equal
        return !(left == right);
    }

    bool operator >(const Point &left, const Point &right)
    {
        // Loop through __values
        for (int i = 0; i < left.getDim(); i++)
        {
            // Compare __values
            if (left.__values[i] > right.__values[i])
            {
                // If left > right, return true
                return true;
            }
            else if (left.__values[i] == right.__values[i])
            {
                // If __values are equal, move to next value
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





