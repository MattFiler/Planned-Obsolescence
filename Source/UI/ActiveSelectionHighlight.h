#ifndef PLANNEDOBSOLESCENCE_ACTIVEHIGHLIGHT_H
#define PLANNEDOBSOLESCENCE_ACTIVEHIGHLIGHT_H

#include "../Map/Tile.h"
#include "../Sprites/ScaledSpriteArray.h"
#include <Engine/Renderer.h>
#include <Engine/Sprite.h>

class Character;

class ActiveSelectionHighlight
{
 public:
  ActiveSelectionHighlight(ASGE::Renderer* rend);
  ~ActiveSelectionHighlight() = default;

  void highlightCharacter(Character& clicked_character);
  void highlightTile(Tile& clicked_tile);

  void render();
  void update();

 private:
  ScaledSpriteArray* highlight_sprite = nullptr;
  ASGE::Renderer* renderer = nullptr;
  Character* highlighted_character = nullptr;
};

#endif // PLANNEDOBSOLESCENCE_ACTIVEHIGHLIGHT_H
