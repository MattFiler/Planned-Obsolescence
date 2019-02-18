#ifndef PLANNEDOBSOLESCENCE_POPUPWINDOW_H
#define PLANNEDOBSOLESCENCE_POPUPWINDOW_H

#include "../UI/Button.h"
#include "../UI/ProgressBar.h"
#include "../UI/TextBox.h"
#include <array>

/* Basically just a collection of other UI elements packaged into a single object.
 * Has a close button by default which hides the window.*/
class PopupWindow : public UI
{
 public:
  PopupWindow(Point pos,
              ASGE::Renderer* rend,
              const std::string& background_sprite_texture_path,
              float _width = 300,
              float _height = 180);
  ~PopupWindow() override;

  void render(double delta_time) override;
  void moveTo(Point point) override;
  void setActive(bool is_active) { active = is_active; };
  bool isActive() { return active; };
  Button* checkForClick(Point click_location);

  void addButton(Button* new_button);
  void addTextBox(TextBox* new_text_box);
  void addProgressBar(ProgressBar* new_progress_bar);

 private:
  bool active = false;
  ScaledSpriteArray* background_sprite = nullptr;

  std::vector<Button*> buttons;
  std::vector<TextBox*> text_boxes;
  std::vector<ProgressBar*> progress_bars;
};

#endif // PLANNEDOBSOLESCENCE_POPUPWINDOW_H
