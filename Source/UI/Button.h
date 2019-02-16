#ifndef PLANNEDOBSOLESCENCE_BUTTON_H
#define PLANNEDOBSOLESCENCE_BUTTON_H

#include "../Debug/DebugText.h"
#include "../Sprites/ScaledSpriteArray.h"
#include "../Viewport/ClickArea.h"
#include "UI.h"
#include <functional>

class Button : public UI
{
 public:
  Button() = default;
  Button(Point pos,
         ASGE::Renderer* rend,
         ScaledSpriteArray* _sprite,
         float _width = 100,
         float _height = 50);
  ~Button() override = default;

  void render(double delta_time) override;
  bool checkForClick(Point click_location);
  void releaseClick();

  std::function<void()> click_function = []() {};

 private:
  float width = 0;
  float height = 0;

  ScaledSpriteArray* sprite = nullptr;
  ClickArea click_area;
};

#endif // PLANNEDOBSOLESCENCE_BUTTON_H
