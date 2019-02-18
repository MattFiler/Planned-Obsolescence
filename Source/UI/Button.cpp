#include "Button.h"

Button::Button(Point pos,
               ASGE::Renderer* rend,
               const std::string& texture_path_1,
               const std::string& texture_path_2,
               float _width,
               float _height) :
  UI(pos, rend)
{
  width = _width;
  height = _height;
  position = pos;
  click_area = ClickArea(position, width, height);
  sprite = createSprite(texture_path_1, texture_path_2);
  sprite->setWidth(width);
  sprite->setHeight(height);
  sprite->xPos(position.x_pos);
  sprite->yPos(position.y_pos);
}

Button::~Button()
{
  delete sprite;
  sprite = nullptr;
}

void Button::render(double delta_time)
{
  renderer->renderSprite(sprite->returnNextSprite(delta_time));
}

void Button::moveTo(Point point)
{
  position = point;
  sprite->xPos(point.x_pos);
  sprite->yPos(point.y_pos);
  click_area.setPosition(point);
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
