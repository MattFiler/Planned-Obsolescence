#include "ClickArea.h"

/* Returns true is he passed point is within the area defined by this object */
bool ClickArea::isPointInArea(Point point)
{
  return point.x_pos < top_right.x_pos && point.x_pos > bottom_left.x_pos &&
         point.y_pos > top_right.y_pos && point.y_pos < bottom_left.y_pos;
}