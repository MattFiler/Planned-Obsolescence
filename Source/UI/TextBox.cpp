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
  wrapText();
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

/* Horizontally wraps text to stay within the width of this TextBos */
void TextBox::wrapText()
{
  // Calculate the max number of characters per line, this is only roughly accurate unfortunately
  // Also need to remove the width_scale since all other calculations are done in simulated world
  // space
  auto char_per_line = static_cast<unsigned long long>((font_size * (width - padding.x_pos)) /
                                                       (ScaledSpriteArray::width_scale));
  unsigned long long str_index = 0;

  // While there are characters left to process
  while (str_index < displayed_text.size())
  {
    // Check if any newlines already exist
    bool newline_exists = false;
    for (unsigned long long i = str_index; i < str_index + char_per_line; i++)
    {
      if (displayed_text[i] == '\n')
      {
        newline_exists = true;
        str_index = i + 1;
        break;
      }
    }
    if (!newline_exists)
    {
      str_index += char_per_line;
      // If there is a full line left
      if (str_index < displayed_text.length())
      {
        // Backtrack to the last space
        while (displayed_text[str_index] != ' ')
        {
          // If the index gets to 0, this is the best we can do so finish here
          if (str_index == 0)
          {
            return;
          }
          str_index--;
        }
        // Replace that space with a newline
        displayed_text[str_index] = '\n';
        str_index++;
      }
    }
  }
}