#ifndef PLANNEDOBSOLESCENCE_CLICKAREA_H
#define PLANNEDOBSOLESCENCE_CLICKAREA_H

#include "../Core/Point.h"

class ClickArea
{
 public:
  ClickArea(Point top_right_corner, Point bottom_left_corner);
  ~ClickArea() = default;

  bool isPointInArea(Point point);

 private:
  Point top_right;
  Point bottom_left;
};

#endif // PLANNEDOBSOLESCENCE_CLICKAREA_H
