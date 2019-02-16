#include "Button.h"

/* The sprites used to create this button can have either 1 or 2 sprites, if the latter it will
 * switch to that sprite when the button is pressed. Ensure flipbook is set to false when adding
 * the sprite */
Button::Button(
  Point pos, ASGE::Renderer* rend, ScaledSpriteArray* _sprite, float _width, float _height) :
  UI(pos, rend),
  width(_width), height(_height), sprite(_sprite)
{
  click_area = ClickArea(Point(position.x_pos + width, position.y_pos),
                         Point(position.x_pos, position.y_pos + height));
  sprite->setWidth(width);
  sprite->setHeight(height);
  sprite->xPos(pos.x_pos);
  sprite->yPos(position.y_pos);
}

void Button::render(double delta_time)
{
  renderer->renderSprite(sprite->returnNextSprite(delta_time));
}

/* Checks to see if a given point is within this objects click area and updates accordingly */
bool Button::checkForClick(Point click_location)
{
  if (click_area.isPointInArea(click_location))
  {
    sprite->setCurrentSprite(1);
    return true;
  }
  return false;
}

/* Resets the buttons back to resting state */
void Button::releaseClick()
{
  sprite->setCurrentSprite(0);
  click_function();
}
