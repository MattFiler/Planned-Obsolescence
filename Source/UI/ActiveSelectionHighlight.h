#ifndef PLANNEDOBSOLESCENCE_ACTIVEHIGHLIGHT_H
#define PLANNEDOBSOLESCENCE_ACTIVEHIGHLIGHT_H

#include "../Map/Tile.h"
#include "../Sprites/ScaledSpriteArray.h"
#include "../Viewport/Camera.h"
#include <Engine/Renderer.h>
#include <Engine/Sprite.h>

class Character;

class ActiveSelectionHighlight
{
 public:
  ActiveSelectionHighlight(ASGE::Renderer* rend, Camera* cam);
  ~ActiveSelectionHighlight() = default;

  void highlightCharacter(Character& clicked_character);
  void highlightTile(Tile& clicked_tile);

  void render();
  void update();

 private:
  ScaledSpriteArray* highlight_sprite = nullptr;
  ASGE::Renderer* renderer = nullptr;
  Character* highlighted_character = nullptr;
  Camera* game_camera = nullptr;
};

#endif // PLANNEDOBSOLESCENCE_ACTIVEHIGHLIGHT_H
