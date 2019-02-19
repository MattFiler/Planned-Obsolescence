#include "Cursor.h"

/* setup cursor */
void Cursor::setupCursor(ASGE::Renderer* rend)
{
  renderer = rend;

  cursor_sprite = std::make_shared<ScaledSpriteArray>(2);

  ASGE::Sprite* sprite1 = renderer->createRawSprite();
  sprite1->loadTexture("data/UI/CURSOR_DEFAULT.png");
  sprite1->width(sprite1->width() / ScaledSpriteArray::width_scale);
  sprite1->height(sprite1->height() / ScaledSpriteArray::width_scale);
  cursor_sprite->addSprite(*sprite1);

  ASGE::Sprite* sprite2 = renderer->createRawSprite();
  sprite2->loadTexture("data/UI/CURSOR_POINTER.png");
  sprite2->width(sprite2->width() / ScaledSpriteArray::width_scale);
  sprite2->height(sprite2->height() / ScaledSpriteArray::width_scale);
  cursor_sprite->addSprite(*sprite2);

  cursor_sprite->setCurrentSprite(0);
}

/* set cursor type (hover/not) */
void Cursor::setCursorType(cursor_variant new_type)
{
  cursor_sprite->setCurrentSprite(new_type);
}

/* Update cursor postion */
void Cursor::updatePosition(double x_pos, double y_pos)
{
  cursor_sprite->xPos(static_cast<float>(x_pos) / ScaledSpriteArray::width_scale);
  cursor_sprite->yPos(static_cast<float>(y_pos) / ScaledSpriteArray::width_scale);
}

/* Get cursor postion */
Point Cursor::getPosition()
{
  return Point(cursor_sprite->xPos(), cursor_sprite->yPos());
}

/* render cursor */
void Cursor::render(double delta_time)
{
  renderer->renderSprite(cursor_sprite->returnCurrentSprite(), render_index::UI_TOP_LAYER_CAP);
}