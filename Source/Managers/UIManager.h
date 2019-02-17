#ifndef PLANNEDOBSOLESCENCE_UIMANAGER_H
#define PLANNEDOBSOLESCENCE_UIMANAGER_H

#include "../UI/Button.h"
#include "../UI/ProgressBar.h"
#include "../UI/TextBox.h"
#include <vector>

class UIManager
{
 public:
  UIManager() = default;
  ~UIManager() = default;

  void render(double delta_time);
  bool checkForClick(Point click);
  void releaseClick();

 private:
  std::vector<Button> buttons;
  std::vector<TextBox> text_boxs;
  std::vector<ProgressBar> progress_bars;

  Button* clicked_button = nullptr;
};

#endif // PLANNEDOBSOLESCENCE_UIMANAGER_H
