#include "TextBox.h"

TextBox::TextBox(Point pos,
                 ASGE::Renderer* rend,
                 std::string text,
                 float _width,
                 float _height,
                 float _font_size,
                 ASGE::Colour colour,
                 Point _padding) :
  UI(pos, rend),
  displayed_text(text), width(_width), height(_height),
  font_size(_font_size * ScaledSpriteArray::width_scale), font_colour(colour), padding(_padding)
{
}

/* Renders this text to screen with its background (if any) */
void TextBox::render(double delta_time)
{
  if (background_sprite)
  {
    renderer->renderSprite(background_sprite->returnNextSprite(delta_time));
  }
  renderer->renderText(displayed_text,
                       static_cast<int>(position.x_pos + padding.x_pos),
                       static_cast<int>(position.y_pos + padding.y_pos),
                       font_size,
                       font_colour);
}

/* Sets the sprite that will be rendered behind the text */
void TextBox::setBackgroundSprite(ScaledSpriteArray* sprite)
{
  background_sprite = sprite;
}

/* Replaces the current text with the passed argument */
void TextBox::setText(std::string new_text)
{
  displayed_text = new_text;
}