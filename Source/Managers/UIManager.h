#ifndef PLANNEDOBSOLESCENCE_UIMANAGER_H
#define PLANNEDOBSOLESCENCE_UIMANAGER_H

#include "../UI/PopupWindow.h"

class UIManager
{
 public:
  static UIManager& getInstance();
  UIManager(UIManager const&) = delete;
  void operator=(UIManager const&) = delete;

  ~UIManager();

  void buildUI();
  void setRenderer(ASGE::Renderer* rend) { renderer = rend; };
  void render(double delta_time);
  bool checkForClick(Point click);
  scenes releaseClick();

 private:
  UIManager() = default;
  std::vector<Button*> buttons;
  std::vector<TextBox*> text_boxes;
  std::vector<ProgressBar*> progress_bars;

  Button* clicked_button = nullptr;
  ASGE::Renderer* renderer = nullptr;

  bool loaded = false;
  scenes next_scene = scenes::NO_CHANGE; // Ideally this whole process would use an event system
};

#endif // PLANNEDOBSOLESCENCE_UIMANAGER_H
