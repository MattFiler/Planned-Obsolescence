#ifndef PLANNEDOBSOLESCENCE_UIMANAGER_H
#define PLANNEDOBSOLESCENCE_UIMANAGER_H

#include "../UI/ActiveSelectionHighlight.h"
#include "../UI/Cursor.h"
#include "../UI/GenericUI.h"
#include "../UI/InteractionPopup.h"
#include "../UI/MainHUD.h"
#include "../UI/PopupWindow.h"
#include "../Viewport/Camera.h"
#include <Engine/Input.h>

class Character;

class UIManager
{
 public:
  UIManager(UIManager const&) = delete;
  void operator=(UIManager const&) = delete;

  UIManager();
  ~UIManager();

  void addGenericUI(GenericUI* new_generic_ui);
  void addButton(Button* new_button);
  void addTextBox(TextBox* new_textbox);
  void addProgressBar(ProgressBar* new_progressbar);

  void createMainHUD(CharacterManager* character_manager);

  void updateAndShowCharacterInfo(Character& clicked_character);
  void updateAndShowTileData(Tile& clicked_tile);

  void setRenderer(ASGE::Renderer* rend) { renderer = rend; }; // must be called first!
  void setCamera(Camera* cam) { camera = cam; };
  void setInputData(ASGE::Input* inp) { input = inp; }
  void setSoundPlayer(SoLoud::Soloud* player)
  {
    delete sound_player;
    sound_player = player;
  }
  void update();
  void render(double delta_time);
  bool checkForClick(Point click, bool act_on_click = true);
  void releaseClick();

  Cursor* getCursor() { return game_cursor; };
  MainHUD* getMainHUD() { return main_hud_element; };

 private:
  void initCharacterPopup();
  void initPointOfInterestPopup(CharacterManager* character_manager);

  std::vector<Button*> buttons;
  std::vector<TextBox*> text_boxes;
  std::vector<ProgressBar*> progress_bars;
  std::vector<GenericUI*> generic_spriteset;
  MainHUD* main_hud_element = nullptr;

  InteractionPopup* char_info_popup = nullptr;
  InteractionPopup* poi_interaction_popup = nullptr;
  ActiveSelectionHighlight* active_highlight = nullptr;

  Cursor* game_cursor = nullptr;
  double cursor_x = 0;
  double cursor_y = 0;

  Button* clicked_button = nullptr;
  ASGE::Renderer* renderer = nullptr;
  ASGE::Input* input = nullptr;
  Camera* camera = nullptr;
  FileHandler file_handler;

  SoLoud::Soloud* sound_player;
};

#endif // PLANNEDOBSOLESCENCE_UIMANAGER_H
