#ifndef PLANNEDOBSOLESCENCE_BUTTON_H
#define PLANNEDOBSOLESCENCE_BUTTON_H

#include "../Debug/DebugText.h"
#include "../Viewport/ClickArea.h"
#include "GetLocalisedString.h"
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
         float _height = 50,
         const std::string& button_text = "",
         float text_size = 1.0f,
         Point text_offset = Point(0, 0));
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
  GetLocalisedString localiser;
  bool is_active = true;

  std::string my_b_text = "";
  float my_b_text_size = 0.0f;
  Point my_b_text_offset; // For reference, offset is (PADDING FROM LEFT, PADDING FROM BOTTOM)
};

#endif // PLANNEDOBSOLESCENCE_BUTTON_H
