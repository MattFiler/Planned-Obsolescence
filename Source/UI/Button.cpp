#include "Button.h"

Button::Button(Point pos,
               ASGE::Renderer* rend,
               const std::string& texture_path_1,
               const std::string& texture_path_2,
               float _width,
               float _height,
               const std::string& button_text,
               float text_size,
               Point text_offset,
               ASGE::Colour text_colour) :
  UI(pos, rend),
  click_area(ClickArea(pos, _width, _height)), my_b_text(button_text), my_b_text_size(text_size),
  my_b_text_offset(text_offset), my_b_text_colour(text_colour)
{
  width = _width;
  height = _height;
  position = pos;
  sprite = createSprite(texture_path_1, texture_path_2);
  sprite->setWidth(width);
  sprite->setHeight(height);
  sprite->xPos(position.x_pos);
  sprite->yPos(position.y_pos);
  if (my_b_text != "")
  {
    my_b_text = localiser.getString(button_text);
  }
}

Button::~Button()
{
  delete sprite;
  sprite = nullptr;
}

void Button::render(double delta_time)
{
  renderer->renderSprite(sprite->returnCurrentSprite());
  if (my_b_text != "")
  {
    renderer->renderText(
      my_b_text,
      static_cast<int>((my_b_text_offset.x_pos + position.x_pos) * ScaledSpriteArray::width_scale),
      static_cast<int>((height + position.y_pos - my_b_text_offset.y_pos) *
                       ScaledSpriteArray::width_scale),
      my_b_text_size,
      ASGE::COLOURS::WHITE);
  }
}

void Button::moveTo(Point point)
{
  position = point;
  sprite->xPos(point.x_pos);
  sprite->yPos(point.y_pos);
  click_area.setPosition(point);
}

/* acts like a hover effect */
bool Button::checkForClick(Point click_location)
{
  if (is_active && click_area.isPointInArea(click_location))
  {
    sprite->setCurrentSprite(1);
    return true;
  }
  sprite->setCurrentSprite(0);
  return false;
}

/* Resets the buttons back to resting state */
void Button::releaseClick()
{
  sprite->setCurrentSprite(0);
  click_function();
}
