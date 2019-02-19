#ifndef PLANNEDOBSOLESCENCE_UIMANAGER_H
#define PLANNEDOBSOLESCENCE_UIMANAGER_H

#include "../Characters/Boss.h"
#include "../UI/CharacterInfoPopup.h"
#include "../UI/Cursor.h"
#include "../UI/GenericUI.h"
#include "../UI/MainHUD.h"
#include "../UI/PopupWindow.h"
#include "../UI/WorldInteractionPopup.h"
#include "../Viewport/Camera.h"
#include <Engine/Input.h>

class UIManager
{
 public:
  UIManager(UIManager const&) = delete;
  void operator=(UIManager const&) = delete;

  UIManager() = default;
  ~UIManager();

  void addGenericUI(GenericUI* new_generic_ui);
  void addButton(Button* new_button);
  void addTextBox(TextBox* new_textbox);
  void addProgressBar(ProgressBar* new_progressbar);

  void createMainHUD();

  void updateAndShowCharacterInfo(const std::string& character_type,
                                  float character_gauge,
                                  const std::string& gauge_name);
  void updateAndShowPointInfo(const std::string& point_name);

  void setRenderer(ASGE::Renderer* rend) { renderer = rend; }; // must be called first!
  void setCamera(Camera* cam) { camera = cam; };
  void setInputData(ASGE::Input* inp) { input = inp; }
  void update(double delta_time);
  void render(double delta_time);
  bool checkForClick(Point click, bool act_on_click = true);
  void releaseClick();

  Cursor* getCursor();

 private:
  void initCharacterPopup();
  void initPointOfInterestPopup();

  void keepUIWithinScreen(UI* ui_object);

  std::vector<Button*> buttons;
  std::vector<TextBox*> text_boxes;
  std::vector<ProgressBar*> progress_bars;
  std::vector<GenericUI*> generic_spriteset;
  MainHUD* main_hud_element = nullptr;

  CharacterInfoPopup* char_info_popup = nullptr;
  WorldInteractionPopup* poi_interaction_popup = nullptr;

  Cursor* game_cursor = nullptr;
  double cursor_x = 0;
  double cursor_y = 0;

  Button* clicked_button = nullptr;
  ASGE::Renderer* renderer = nullptr;
  ASGE::Input* input = nullptr;
  Camera* camera = nullptr;
};

#endif // PLANNEDOBSOLESCENCE_UIMANAGER_H
