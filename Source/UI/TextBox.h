#ifndef PLANNEDOBSOLESCENCE_TEXTBOX_H
#define PLANNEDOBSOLESCENCE_TEXTBOX_H

#include "UI.h"

/* A self contained text box that once set only needs render to be called */
class TextBox : public UI
{
 public:
  TextBox() = default;
  explicit TextBox(Point pos,
                   ASGE::Renderer* rend,
                   const std::string& text,
                   float _width = 300,
                   float _height = 100,
                   float _font_size = 1,
                   ASGE::Colour colour = ASGE::COLOURS::BLACK,
                   Point _padding = Point(10, 10));
  ~TextBox() override;

  void render(double delta_time) override;
  void setBackgroundSprite(const std::string& sprite_texture_path);
  void setText(const std::string& new_text);

 private:
  void wrapText();

  std::string displayed_text = "";
  float font_size = 0;
  ASGE::Colour font_colour = ASGE::COLOURS::BLACK;
  Point padding = Point(10, 10); // Offset applied before rendering the text

  ScaledSpriteArray* background_sprite = nullptr;
};

#endif // PLANNEDOBSOLESCENCE_TEXTBOX_H
