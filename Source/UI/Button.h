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
         const std::string& texture_path_1,
         const std::string& texture_path_2,
         float _width = 100,
         float _height = 50);
  ~Button() override;

  void render(double delta_time) override;
  void moveTo(Point point) override;
  bool checkForClick(Point click_location);
  void releaseClick();

  void setActive(bool active) { is_active = active; };
  bool isActive() { return is_active; };

  std::function<void()> click_function = []() {};

 private:
  ScaledSpriteArray* sprite = nullptr;
  ClickArea click_area;
  bool is_active = true;
};

#endif // PLANNEDOBSOLESCENCE_BUTTON_H
