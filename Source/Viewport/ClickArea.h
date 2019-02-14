#ifndef PLANNEDOBSOLESCENCE_CLICKAREA_H
#define PLANNEDOBSOLESCENCE_CLICKAREA_H

#include "../Math/Point.h"

class ClickArea
{
 public:
  /* Sets up the area for this object by using 2 points to 'draw' a box */
  ClickArea(Point top_right_corner, Point bottom_left_corner) :
    top_right(top_right_corner), bottom_left(bottom_left_corner){};
  ~ClickArea() = default;

  bool isPointInArea(Point point);

 private:
  Point top_right;
  Point bottom_left;
};

#endif // PLANNEDOBSOLESCENCE_CLICKAREA_H
