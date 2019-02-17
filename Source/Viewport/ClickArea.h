#ifndef PLANNEDOBSOLESCENCE_CLICKAREA_H
#define PLANNEDOBSOLESCENCE_CLICKAREA_H

#include "../Math/Point.h"

class ClickArea
{
 public:
  ClickArea() = default;
  /* Sets up the area for this object by using 2 points to 'draw' a box */
  ClickArea(Point pos, float _width, float _height) :
    position(pos), width(_width), height(_height){};
  ~ClickArea() = default;

  void setHeight(float _height) { height = _height; };
  void setWidth(float _width) { width = _width; };

  bool isPointInArea(Point point);

 private:
  Point position;
  float width;
  float height;
};

#endif // PLANNEDOBSOLESCENCE_CLICKAREA_H
