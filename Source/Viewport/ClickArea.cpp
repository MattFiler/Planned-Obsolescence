#include "ClickArea.h"

/* Returns true is he passed point is within the area defined by this object */
bool ClickArea::isPointInArea(Point point)
{
  return point.x_pos < position.x_pos + width && point.x_pos > position.x_pos &&
         point.y_pos > position.y_pos && point.y_pos < position.y_pos + height;
}