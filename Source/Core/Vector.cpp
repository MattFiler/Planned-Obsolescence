#include "Vector.h"
#include <math.h>

/**
 *   @brief   Creates a vector with passed values
 *   @param   px is the x component, px is the y component
 */
Vector::Vector(float px, float py)
{
  x_mag = px;
  y_mag = py;
  recalculateMagnitude();
}

/**
 *   @brief   Normalises this vector
 */
void Vector::normalise()
{
  if (magnitude != 0)
  {
    x_mag = x_mag / magnitude;
    y_mag = y_mag / magnitude;
  }
  magnitude = 1;
}

/**
 *   @brief   Sets a new x and y for the vector
 *   @param   vector(new_x,new_y)
 */
void Vector::set(float new_x, float new_y)
{
  x_mag = new_x;
  y_mag = new_y;
  recalculateMagnitude();
}

/**
 *   @brief   Flips the vector's direction
 */
void Vector::flip()
{
  x_mag *= -1;
  y_mag *= -1;
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

  x_mag = x_mag - (normal.x_mag * num);
  y_mag = y_mag - (normal.y_mag * num);
  return Vector{ x_mag, y_mag };
}

/**
 *   @brief   Finds the normal to this vector
 *   @return  The normal of this vector
 */
Vector Vector::normal()
{
  return Vector(y_mag, x_mag * -1);
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
  return (a.x_mag * b.x_mag) + (a.y_mag * b.y_mag);
}

/* Re-calculate the magnitude of this vector */
void Vector::recalculateMagnitude()
{
  magnitude = sqrtf(fabsf(x_mag * x_mag) + fabsf(y_mag * y_mag));
}

Vector Vector::operator+(Vector& vector)
{
  Vector return_vector;
  return_vector.x_mag = this->x_mag + vector.x_mag;
  return_vector.y_mag = this->y_mag + vector.y_mag;
  magnitude = sqrtf(fabsf(x_mag * x_mag) + fabsf(y_mag * y_mag));
  return return_vector;
}

Vector Vector::operator-(Vector& vector)
{
  Vector return_vector;
  return_vector.x_mag = this->x_mag - vector.x_mag;
  return_vector.y_mag = this->y_mag - vector.y_mag;
  return return_vector;
}