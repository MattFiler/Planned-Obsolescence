#ifndef PLANNEDOBSOLESCENCE_CAMERA_H
#define PLANNEDOBSOLESCENCE_CAMERA_H

#include "DynamicSprite.h"
#include "Point.h"
#include <Engine/Renderer.h>
#include <vector>

/**
 **   Keeps track of all sprites to render, and adjusts sprite position to allow the user to
 *    move their view around the map
 */
class Camera
{
 public:
  Camera();

  void setRenderer(ASGE::Renderer* rend);
  void registerGameSprite(DynamicSprite* sprite);
  void registerUiSprite(DynamicSprite* sprite);
  void renderSprites(double delta_time);
  Point getCameraPosition();
  void moveCamera(float x_amount, float y_amount);

 private:
  std::vector<DynamicSprite*> game_sprites;
  std::vector<DynamicSprite*> ui_sprites;
  Point position = Point(0, 0);
  ASGE::Renderer* renderer = nullptr;
};

#endif // PLANNEDOBSOLESCENCE_CAMERA_H
