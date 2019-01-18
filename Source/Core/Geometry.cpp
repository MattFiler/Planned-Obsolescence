#include "Geometry.h"
#include <math.h>

/**
 *   @brief   Creates a point with passed values
 *   @param   px is the x position, px is the y position
 */
Point::Point(float px, float py)
{
  x = px;
  y = py;
}

/**
 *   @brief   Finds the distance from a->b
 *   @return  The straight line distance between a and b
 */
float Point::distanceBetween(Point a, Point b)
{
  float x_diff = a.x - b.x;
  float y_diff = a.y - b.y;
  return sqrtf((x_diff * x_diff) + (y_diff * y_diff));
}

/**
 *   @brief   Creates a vector with passed values
 *   @param   px is the x component, px is the y component
 */
Vector::Vector(float px, float py)
{
  x = px;
  y = py;
  magnitude = sqrtf(fabsf(x * x) + fabsf(y * y));
}

/**
 *   @brief   Creates a Line with passed values
 *   @param   gradient is m, y_intersect is c (y=mx+c), verticle is true if
 *   @param   the line has infinite gradient, x_intersect is where the line
 *   @param   intersects the x axis for infinite gradient lines
 */
Line::Line(float gradient, float y_intersect, bool verticle, float x_intersect)
{
  m = gradient;
  c = y_intersect;
  verticle_line = verticle;
  y = x_intersect;
}

/**
 *   @brief   Normalises this vector
 */
void Vector::normalise()
{
  if (magnitude != 0)
  {
    x = x / magnitude;
    y = y / magnitude;
  }
  magnitude = 1;
}

/**
 *   @brief   Sets a new x and y for the vector
 *   @param   vector(new_x,new_y)
 */
void Vector::set(float new_x, float new_y)
{
  x = new_x;
  y = new_y;
  magnitude = sqrtf(fabsf(x * x) + fabsf(y * y));
}

/**
 *   @brief   Flips the vector's direction
 */
void Vector::flip()
{
  x *= -1;
  y *= -1;
}

/**
 *   @brief   Reflects this vector in the passed vector
 *   @details using r = a - ((2a.n) / (||n||^2))*n to calcualte
 *            the reflected vector, where r is the reflected vector
 *            a is the original vector and n is the normal of the vector
 *            to reflect in
 *   @param   target_vector is the vector to reflect in
 *   @return  the reflected vector
 */
Vector Vector::reflectVector(Vector target_vector)
{
  // Calculate normal of target_vector
  Vector normal = target_vector.normal();

  float num = 2 * (dotProduct(*this, normal));
  num /= normal.magnitude * normal.magnitude;

  x = x - (normal.x * num);
  y = y - (normal.y * num);
  return Vector{ x, y };
}

/**
 *   @brief   Finds the normal to this vector
 *   @return  The normal of this vector
 */
Vector Vector::normal()
{
  return Vector(y, x * -1);
}

/**
 *   @brief   Calculates the angle between 2 vectors
 *   @param   a first vector, b second vector
 *   @return  The angle between a and b
 */
float Vector::angleBetweenVectors(Vector a, Vector b)
{
  float angle = acosf(dotProduct(a, b) / (a.magnitude * b.magnitude));
  if (angle > 180)
  {
    angle -= 180;
  }
  return angle;
}

/**
 *   @brief   Calculates the dot product of 2 vectors
 *   @param   a first vector, b second vector
 *   @return  The bot product of a and b
 */
float Vector::dotProduct(Vector a, Vector b)
{
  return (a.x * b.x) + (a.y * b.y);
}

/**
 *   @brief   Calculates if passed line intersects this one
 *   @param   line is the line to check, point will store where they intersect
 *            point will remain unchanged if the lines are the same
 *   @return  True if the lines intersect
 */
bool Line::intersects(Line line, Point& point)
{
  // If either line is verticle, can't use the standard formula
  if (verticle_line)
  {
    // If both lines are verticle
    if (line.verticle_line)
    {
      // Then they collide if they're the same
      // account for rounding errors with a 0.1 margin
      if (fabsf(y - line.y) < 0.1f)
      {
        return true;
      }
      // And don't if they're parallel
      return false;
    }
    point.x = y;
    point.y = (line.m * y) + line.c;
    return true;
  }
  else if (line.verticle_line)
  {
    point.x = line.y;
    point.y = (m * line.y) + c;
    return true;
  }

  // If m is the same, then they are parallel
  if (line.m == m)
  {
    // If m and c are the same, they are identical lines
    if (line.c == c)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  // Use the standard formula to calculate intersection
  else
  {
    point.x = (line.c - c) / (m - line.m);
    point.y = m * point.x + c;
  }
  return true;
}

/**
 *   @brief   Checks to see if a point lies between 2 other points
 *   @param   Is point a between c and b
 *   @return  True if a is between c and b
 */
bool Line::pointBetweenPoints(Point a, Point b, Point c)
{
  // If the intersect is between both points in the x
  if ((b.x >= a.x && c.x <= a.x) || (b.x <= a.x && c.x >= a.x))
  {
    // If the intersect is between both points in the y
    if ((b.y >= a.y && c.y <= a.y) || (b.y <= a.y && c.y >= a.y))
    {
      return true;
    }
  }
  return false;
}

/**
 *   @brief   Creates a unit vector from the line
 *   @return  The vector of this line
 */
Vector Line::vector()
{
  Vector new_vector;
  if (verticle_line)
  {
    new_vector = Vector(0, 1);
  }
  else
  {
    new_vector = Vector(1, m);
    new_vector.normalise();
  }
  return new_vector;
}