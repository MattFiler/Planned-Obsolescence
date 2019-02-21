#include "Point.h"
#include <math.h>

/**
 *   @brief   Creates a point with passed values
 *   @param   px is the x position, px is the y position
 */
Point::Point(float px, float py)
{
  x_pos = px;
  y_pos = py;
}

/**
 *   @brief   Sets a new x and y for the point
 *   @param   vector(new_x,new_y)
 */
void Point::set(float new_x, float new_y)
{
  x_pos = new_x;
  y_pos = new_y;
}

bool Point::operator==(Point& point)
{
  float x_dif = fabs(this->x_pos - point.x_pos);
  float y_dif = fabs(this->y_pos - point.y_pos);
  return (x_dif < 0.01f && y_dif < 0.01f);
}

Point Point::operator+(const Point& point)
{
  Point return_point;
  return_point.x_pos = this->x_pos + point.x_pos;
  return_point.y_pos = this->y_pos + point.y_pos;
  return return_point;
}

Point Point::operator-(const Point& point)
{
  Point return_point;
  return_point.x_pos = this->x_pos - point.x_pos;
  return_point.y_pos = this->y_pos - point.y_pos;
  return return_point;
}

Point Point::Point::operator/(const float divider)
{
  Point return_point;
  return_point.x_pos = this->x_pos / divider;
  return_point.y_pos = this->y_pos / divider;
  return return_point;
}

Point Point::Point::operator*(const float multiplier)
{
  Point return_point;
  return_point.x_pos = this->x_pos * multiplier;
  return_point.y_pos = this->y_pos * multiplier;
  return return_point;
}

/**
 *   @brief   Finds the distance from point_1->point_2
 *   @return  The straight line distance between point_1 and point_2
 */
float Point::distanceBetween(Point point_1, Point point_2)
{
  float x_diff = point_1.x_pos - point_2.x_pos;
  float y_diff = point_1.y_pos - point_2.y_pos;
  return sqrtf((x_diff * x_diff) + (y_diff * y_diff));
}
