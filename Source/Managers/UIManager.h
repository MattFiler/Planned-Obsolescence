#ifndef PLANNEDOBSOLESCENCE_UIMANAGER_H
#define PLANNEDOBSOLESCENCE_UIMANAGER_H

#include "../UI/GenericUI.h"
#include "../UI/PopupWindow.h"
#include "../Viewport/Camera.h"

class Boss;

class UIManager
{
 public:
  static UIManager& getInstance();
  UIManager(UIManager const&) = delete;
  void operator=(UIManager const&) = delete;

  ~UIManager();

  void addGenericUI(GenericUI* new_generic_ui);
  void addButton(Button* new_button);

  void buildUI();
  void setRenderer(ASGE::Renderer* rend) { renderer = rend; };
  void setCamera(Camera* cam) { camera = cam; };
  void render(double delta_time);
  bool checkForClick(Point click);
  scenes releaseClick();

  void enableBossPopup(Boss* boss);

 private:
  UIManager() = default;

  void buildButtons();
  void buildTextBoxes();
  void buildProgressBars();
  void buildPopupWindows();
  void keepUIWithinScreen(UI* ui_object);

  std::vector<Button*> buttons;
  std::vector<TextBox*> text_boxes;
  std::vector<ProgressBar*> progress_bars;
  std::vector<GenericUI*> generic_spriteset;

  // All the different popup types
  PopupWindow* boss_popup = nullptr;

  Button* clicked_button = nullptr;
  ASGE::Renderer* renderer = nullptr;
  Camera* camera = nullptr;

  bool loaded = false;
  scenes next_scene = scenes::NO_CHANGE; // Ideally this whole process would use an event system
};

#endif // PLANNEDOBSOLESCENCE_UIMANAGER_H
