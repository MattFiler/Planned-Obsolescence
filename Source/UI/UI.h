#ifndef PLANNEDOBSOLESCENCE_UI_H
#define PLANNEDOBSOLESCENCE_UI_H

#include "../../Libs/ASGE/include/Engine/Renderer.h"
#include "../Math/Point.h"

/* Virtual base class for all UI elements */
class UI
{
 public:
  UI() = default;
  UI(Point pos, ASGE::Renderer* rend) : position(pos), renderer(rend){};
  virtual ~UI() = default;

  virtual void render(double delta_time) = 0;

  void moveTo(Point point) { position = point; };

 protected:
  Point position;
  ASGE::Renderer* renderer;
};

#endif // PLANNEDOBSOLESCENCE_UI_H
