#include "ActiveSelectionHighlight.h"
#include "../Characters/Character.h"

// Load highlight sprite
ActiveSelectionHighlight::ActiveSelectionHighlight(ASGE::Renderer* rend, Camera* cam) :
  renderer(rend), game_camera(cam)
{
  ASGE::Sprite* new_highlight_sprite = renderer->createRawSprite();
  new_highlight_sprite->loadTexture("data/UI/WHITE.png");
  highlight_sprite = new ScaledSpriteArray(1);
  highlight_sprite->addSprite(*new_highlight_sprite);
  highlight_sprite->setOpacity(0.5);
  highlight_sprite->setColour(ASGE::COLOURS::RED);
  highlight_sprite->hide();
}

// Highlight character
void ActiveSelectionHighlight::highlightCharacter(Character& clicked_character)
{
  highlighted_character = &clicked_character;

  highlight_sprite->setWidth(clicked_character.getWidth());
  highlight_sprite->setHeight(clicked_character.getHeight());
  highlight_sprite->xPos(clicked_character.getPosition().x_pos);
  highlight_sprite->yPos(clicked_character.getPosition().y_pos);
  highlight_sprite->show();
}

// Highlight tile
void ActiveSelectionHighlight::highlightTile(Tile& clicked_tile)
{
  highlight_sprite->setWidth(clicked_tile.getWidth());
  highlight_sprite->setHeight(clicked_tile.getHeight());
  highlight_sprite->xPos(clicked_tile.getPositionX());
  highlight_sprite->yPos(clicked_tile.getPositionY());
  highlight_sprite->show();
}

// Render
void ActiveSelectionHighlight::render()
{
  game_camera->renderSprite(highlight_sprite, 0, render_index::CHARACTER_LAYER, false);
}

// Update (if highlighting moving character)
void ActiveSelectionHighlight::update()
{
  highlight_sprite->xPos(highlighted_character->getPosition().x_pos);
  highlight_sprite->yPos(highlighted_character->getPosition().y_pos);
}