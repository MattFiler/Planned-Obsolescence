#include "../Debug/DebugText.h"
#include "../Managers/CharacterManager.h"
#include "../Map/GameMap.h"
#include "../Sprites/ScaledSpriteArray.h"
#include "../UI/Button.h"
#include "../UI/ProgressBar.h"
#include "../UI/TextBox.h"
#include "../Viewport/Camera.h"
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
  bool load(ASGE::Renderer* renderer, ASGE::Input* input) override;
  scenes update(double delta_time) override;
  void render(double delta_time) override;
  void keyHandler(const ASGE::SharedEventData data) override;
  void mouseHandler(const ASGE::SharedEventData data, Point mouse_position) override;

 private:
  void spawnCharacters(ASGE::Renderer* renderer);

  CharacterManager character_manager;
  GameMap game_map;

  Camera camera;
  float x_axis_input = 0;
  float y_axis_input = 0;

  // TEST CODE
  TextBox test_text;
  ProgressBar test_progress;
  Button test_button;
  bool button_pressed = false;
};