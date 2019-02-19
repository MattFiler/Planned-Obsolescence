#ifndef PLANNEDOBSOLESCENCE_UI_H
#define PLANNEDOBSOLESCENCE_UI_H

#include "../../Libs/ASGE/include/Engine/Renderer.h"
#include "../Math/Point.h"
#include "../Sprites/ScaledSpriteArray.h"

/* Virtual base class for all UI elements */
class UI
{
 public:
  UI() = default;
  UI(Point pos, ASGE::Renderer* rend) : position(pos), renderer(rend){};
  virtual ~UI() = default;

  virtual void render(double delta_time) = 0;

  virtual void moveTo(Point point) { position = point; };
  Point getPosition() { return position; };
  float getWidth() { return width; };
  float getHeight() { return height; };

 protected:
  ScaledSpriteArray* createSprite(const std::string& sprite_texture_path);
  ScaledSpriteArray*
  createSprite(const std::string& texture_path1, const std::string& texture_path2);

  Point position;
  ASGE::Renderer* renderer;
  float width = 0;
  float height = 0;
};

#endif // PLANNEDOBSOLESCENCE_UI_H
