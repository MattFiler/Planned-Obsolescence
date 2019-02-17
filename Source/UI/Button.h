#ifndef PLANNEDOBSOLESCENCE_BUTTON_H
#define PLANNEDOBSOLESCENCE_BUTTON_H

#include "../Debug/DebugText.h"
#include "../Viewport/ClickArea.h"
#include "UI.h"
#include <functional>

class Button : public UI
{
 public:
  Button() = default;
  Button(Point pos,
         ASGE::Renderer* rend,
         const std::string& first_sprite_texture_path,
         const std::string& second_sprite_texture_path,
         float _width = 100,
         float _height = 50);
  ~Button() override = default;

  void render(double delta_time) override;
  bool checkForClick(Point click_location);
  void releaseClick();

  std::function<void()> click_function = []() {};

 private:
  ScaledSpriteArray* sprite = nullptr;
  ClickArea click_area;
};

#endif // PLANNEDOBSOLESCENCE_BUTTON_H
