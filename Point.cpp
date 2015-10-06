// Programming Assignment 2 - Three Dimensional Triangle

// Author:      Dylan Lang
// Date:        10 Sept 2015

// Point class implementation

#include <cmath>
#include <ostream>
#include "Point.h"

// namespace wrap
namespace Clustering
{
// Constructors
    Point::Point(int dimensions)
    {
      if (dimensions == 0)
      {
        dimensions = 2;
      }

      dim = dimensions;

      values = new double[dim];
    }

// Copy constructor
    Point::Point(const Point &right)
    {
      dim = right.dim;

      values = new double[dim];

      for (int i = 0; i < dim; i++)
      {
        values[i] = right.values[i];
      }
    }

// Overloaded assignment operator
    Point &Point::operator =(const Point &right)
    {
      if (this == &right)
      {
        return *this;
      }

      else
      {
        delete [] values;

        dim = right.dim;

        values = new double[dim];

        for (int i = 0; i < dim; i++)
        {
          values[i] = right.values[i];
        }
      }

      return *this;
    }
// ******************************************

// Destructor
    Point::~Point()
    {
      delete [] values;
    }
// ******************************************

// Mutator methods
    void Point::setValue(int element, double value) const
    {
      if (element >= 1 && element <= dim)
      {
        values[element - 1] = value;
      }
    }
// ******************************************

// Accessors
    double Point::getValue(int element) const
    {
      if (element >= 1 && element <= dim)
      {
        return values[element - 1];
      }

      return 0;
    }
// ******************************************

// Calculates distance between two points
// Uses Pythagorean theorem
    double Point::distanceTo(const Point &p) const
    {
      if (p.dim == dim)
      {
        double sum = 0;
        double distance = 0;

        for (int i = 0; i < dim; i++)
        {
          double diff = values[i] - p.values[i];
          sum += diff * diff; // sum = sum + pow(diff, 2);
        }

        distance = sqrt(sum);
        return distance;
      }

      return 0;

      /* Calculate distance using Pythagorean Theorem
      double distance = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2) + pow((z1 - z2), 2));

      return distance;*/
    }
// ******************************************

// Overloaded compound assignment operators
    Point &Point::operator *=(double d)
    {
      for (int i = 0; i < dim; i++)
      {
        values[i] *= d;
      }

      return *this;
    }

    Point &Point::operator /=(double d)
    {
      // Check if d == 0
      if (d != 0) {
        for (int i = 0; i < dim; i++)
        {
          values[i] /= d;
        }
      }
      return *this;
    }
// ******************************************

// Overloaded arithmetic operators
    const Point Point::operator *(double d) const
    {
      // Copy point
      Point result = *this;
      // Use overloaded *= operator to multiply
      result *= d;

      return result;
    }

    const Point Point::operator /(double d) const
    {
      // Copy point
      Point result = *this;
      // Use overloaded /= operator to divide
      result /= d;

      return result;
    }
// ******************************************

// Overloaded insertion operator
    std::ostream &operator <<(std::ostream &out, const Point &right)
    {
        out << "(";
        for (int i = 0; i < right.dim; i++)
        {
            out << right.values[i];

            if (i < (right.dim) - 1)
            {
                out << ",";
            }
        }
        out << ")";

        return out;
    }
// ******************************************

// Overloaded compound assignment operators
    Point &operator +=(Point &left, const Point &right)
    {
      // Compare left and right Points
      if (left == right)
      {
        // If equal, multiply left Point by 2
        return left *= 2;
      }
        // Compare dimensions
      else if (left.dim == right.dim)
      {
        // If equal, add right values to left point
        for (int i = 0; i < left.dim; i++)
        {
          left.values[i] += right.values[i];
        }
      }
      return left;
    }

Point &operator -=(Point &left, const Point &right)
{
  // Compare dimensions
  if (left.dim == right.dim)
  {
    for (int i = 0; i < left.dim; i++)
    {
      left.values[i] -= right.values[i];
    }
  }

  return left;
}
// ******************************************

// Overloaded binary arithmetic operators
const Point operator +(const Point &left, const Point &right)
{
  // Copy point
  Point result = left;

  // Set dimensions of left hand side if less than right
  if (left.dim < right.dim)
  {
    result.dim = right.dim;
  }

  for (int i = 0; i < result.dim; i++)
  {
    // Add right to left Point values
    result.values[i] += right.values[i];
  }
  // Return new left side
  return result;
}

const Point operator -(const Point &left, const Point &right)
{
  // Copy Point
  Point result = left;

  for (int i = 0; i < result.dim; i++)
  {
    result.values[i] -= right.values[i];
  }
  // Return new left side
  return result;
}
// ******************************************

// Overloaded relational operators (bools)
// ==, !=, >, <, >=, <=
bool operator ==(const Point &left, const Point &right)
{
  // Check dimensions. If not the same, Points are not equal
  if (left.dim != right.dim)
  {
    return false;
  }

  // Compare values of both Points. If not the same, they are not equal.
  for (int i = 0; i < left.dim; i++)
  {
    if (left.values[i] != right.values[i])
    {
      return false;
    }
  }

  return true;
}

bool operator !=(const Point &left, const Point &right)
{
  // Use overloaded == operator to see if they are equal
  return !(left == right);
}

bool operator >(const Point &left, const Point &right)
{
  // Compare dimensions
  if (left.dim > right.dim)
  {
    return true;
  }
  else if (left.dim < right.dim)
  {
    return false;
  }
  else if (left.dim == right.dim)
  {
    // Compare values of both Points
    for (int i = 0; i < left.dim; i++)
    {
      if (left.values[i] < right.values[i])
      {
        return false;
      }
    }
  }

  return true;
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





