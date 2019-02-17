#include "UI.h"

ScaledSpriteArray* UI::createSprite(const std::string& sprite_texture_path)
{
  auto* scaled_sprite = new ScaledSpriteArray(1);
  ASGE::Sprite* sprite = renderer->createRawSprite();
  sprite->loadTexture(sprite_texture_path);
  scaled_sprite->addSprite(*sprite);
  return scaled_sprite;
}

ScaledSpriteArray* UI::createSprite(const std::string& first_sprite_texture_path,
                                    const std::string& second_texture_path)
{
  auto* scaled_sprite = new ScaledSpriteArray(1);
  ASGE::Sprite* sprite = renderer->createRawSprite();
  sprite->loadTexture(first_sprite_texture_path);
  scaled_sprite->addSprite(*sprite);
  sprite = renderer->createRawSprite();
  sprite->loadTexture(second_texture_path);
  scaled_sprite->addSprite(*sprite);
  return scaled_sprite;
}