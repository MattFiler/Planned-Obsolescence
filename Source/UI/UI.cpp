#include "UI.h"

ScaledSpriteArray* UI::createSprite(const std::string& sprite_texture_path)
{
  auto* scaled_sprite = new ScaledSpriteArray(1);
  ASGE::Sprite* sprite = renderer->createRawSprite();
  sprite->loadTexture(sprite_texture_path);
  scaled_sprite->addSprite(*sprite);
  return scaled_sprite;
}

ScaledSpriteArray*
UI::createSprite(const std::string& texture_path1, const std::string& texture_path2)
{
  auto* scaled_sprite = new ScaledSpriteArray(1);
  ASGE::Sprite* sprite1 = renderer->createRawSprite();
  sprite1->loadTexture(texture_path1);
  scaled_sprite->addSprite(*sprite1);
  ASGE::Sprite* sprite2 = renderer->createRawSprite();
  sprite2->loadTexture(texture_path2);
  scaled_sprite->addSprite(*sprite2);
  return scaled_sprite;
}