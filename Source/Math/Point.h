//
// Created by tobyj on 22/01/2019.
//

#ifndef PLANNEDOBSOLESCENCE_POINT_H
#define PLANNEDOBSOLESCENCE_POINT_H

/**
 **   Represents a point in 2d space
 */
struct Point
{
  Point(float px, float py);
  Point() = default;
  float x_pos = 0;
  float y_pos = 0;

  void set(float new_x, float new_y);

  bool operator==(Point& point);
  Point operator-(const Point& point);
  Point operator+(const Point& point);
  Point operator/(const float multiplier);

  static float distanceBetween(Point a, Point b);
};

#endif // PLANNEDOBSOLESCENCE_POINT_H