//
// Created by tobyj on 22/01/2019.
//

#ifndef PLANNEDOBSOLESCENCE_VECTOR_H
#define PLANNEDOBSOLESCENCE_VECTOR_H

/**
 **   Represents a vector in 2d space
 */
struct Vector
{
  Vector(float px, float py);
  Vector(){};

  void normalise();
  void set(float new_x, float new_y);
  void recalculateMagnitude();
  void flip();
  Vector reflectVector(Vector target_vector);
  Vector normal();

  static float angleBetweenVectors(Vector a, Vector b);
  static float dotProduct(Vector a, Vector b);

  Vector operator-(Vector& vector);
  Vector operator+(Vector& vector);

  float x_mag = 0;
  float y_mag = 0;
  float magnitude = 0;
};

#endif // PLANNEDOBSOLESCENCE_VECTOR_H
