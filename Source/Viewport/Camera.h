#ifndef PLANNEDOBSOLESCENCE_CAMERA_H
#define PLANNEDOBSOLESCENCE_CAMERA_H

#include "../Constants.h"
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

  void setRenderer(ASGE::Renderer* rend) { renderer = rend; };
  void setMapDims(Point new_dims) { map_dims = new_dims * ScaledSpriteArray::width_scale; }

  void renderSprite(ScaledSpriteArray* sprite,
                    double delta_time,
                    render_index index,
                    bool should_flipbook = true);

  Point displayedToSimulatedWorld(Point point);
  void moveCamera(float x_amount, float y_amount);

  Point getCameraPosition() { return position / ScaledSpriteArray::width_scale; };
  ASGE::Renderer* getRenderer() { return renderer; };

 private:
  Point position = Point(0, 0);
  Point map_dims = Point(0, 0);
  ASGE::Renderer* renderer = nullptr;
};

#endif // PLANNEDOBSOLESCENCE_CAMERA_H
