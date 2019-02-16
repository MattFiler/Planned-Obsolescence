#ifndef PLANNEDOBSOLESCENCE_CAMERA_H
#define PLANNEDOBSOLESCENCE_CAMERA_H

#include "../Math/Point.h"
#include "../Sprites/ScaledSpriteArray.h"
#include <Engine/Renderer.h>
#include <vector>

/**
 **   Keeps track of all sprites to render, and adjusts sprite position to allow the user to
 *    move their view around the map
 */
class Camera
{
 public:
  Camera() = default;

  void setRenderer(ASGE::Renderer* rend);
  ASGE::Renderer* getRenderer();
  void renderSprite(ScaledSpriteArray* sprite, double delta_time);
  Point getCameraPosition();
  Point displayedToSimulatedWorld(Point point);
  void moveCamera(float x_amount, float y_amount);

 private:
  Point position = Point(0, 0);
  ASGE::Renderer* renderer = nullptr;
};

#endif // PLANNEDOBSOLESCENCE_CAMERA_H
