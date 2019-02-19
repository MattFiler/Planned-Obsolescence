#ifndef PLANNEDOBSOLESCENCE_CURSOR_H
#define PLANNEDOBSOLESCENCE_CURSOR_H

#include "../Constants.h"
#include "../Math/Point.h"
#include "../Sprites/ScaledSpriteArray.h"
#include <Engine/Renderer.h>
#include <memory>

class Cursor
{
 public:
  Cursor() = default;
  ~Cursor() = default;

  void setupCursor(ASGE::Renderer* rend);
  void setCursorType(cursor_variant new_type);

  void updatePosition(double x_pos, double y_pos);
  Point getPosition();

  void render(double delta_time);

 private:
  std::shared_ptr<ScaledSpriteArray> cursor_sprite;
  ASGE::Renderer* renderer;
};

#endif // PLANNEDOBSOLESCENCE_CURSOR_H
