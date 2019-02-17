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

  void moveTo(Point point) { position = point; };

 protected:
  ScaledSpriteArray* createSprite(const std::string& sprite_texture_path);
  ScaledSpriteArray* createSprite(const std::string& first_sprite_texture_path,
                                  const std::string& second_sprite_texture_path);

  Point position;
  ASGE::Renderer* renderer;
  float width = 0;
  float height = 0;
};

#endif // PLANNEDOBSOLESCENCE_UI_H
