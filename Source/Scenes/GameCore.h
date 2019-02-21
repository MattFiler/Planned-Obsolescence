#ifndef PO_GAMECORE
#define PO_GAMECORE

#include "../Debug/DebugText.h"
#include "../Managers/CharacterManager.h"
#include "../Managers/GaugeManager.h"
#include "../Managers/UIManager.h"
#include "../Map/GameMap.h"
#include "../Sprites/ScaledSpriteArray.h"
#include "../UI/Button.h"
#include "../UI/MainHUD.h"
#include "../UI/ProgressBar.h"
#include "../UI/TextBox.h"
#include "../Viewport/Camera.h"
#include "GameOver.h"
#include "Scene.h"

namespace ASGE
{
class Renderer;
}

/**
 **   The core game scene
 */
class GameCore : public Scene
{
 public:
  GameCore() = default;
  ~GameCore() = default;
  bool load(ASGE::Renderer* renderer, ASGE::Input* input, SoLoud::Soloud& player) override;
  scenes update(double delta_time) override;
  void render(double delta_time) override;
  void keyHandler(const ASGE::SharedEventData data) override;
  void mouseHandler(const ASGE::SharedEventData data, Point mouse_position) override;
  void endGame(game_over_type type);

 private:
  void spawnCharacters(ASGE::Renderer* renderer);
  void passReferences(ASGE::Input* input);

  CharacterManager character_manager;
  GameMap game_map;
  UIManager ui_manager;
  GaugeManager project_gauge;
  GameOver game_over_instance;
  FileHandler file_handler;

  SoLoud::Wav sound_wav;

  Camera camera;
  float x_axis_input = 0;
  float y_axis_input = 0;
};

#endif