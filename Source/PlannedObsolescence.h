#include "FileHandler/FileHandler.h"
#include "Keybinds/Keybinds.h"
#include "Managers/SceneManager.h"
#include "Sprites/ScaledSpriteArray.h"
#include "UI/GetLocalisedString.h"
#include <Engine/OGLGame.h>
#include <json.hpp>
#include <soloud.h>
#include <soloud_wav.h>
#include <string>

using json = nlohmann::json;

class PlannedObsolescence : public ASGE::OGLGame
{
 public:
  PlannedObsolescence() = default;
  ~PlannedObsolescence();

  bool init() override;
  void update(const ASGE::GameTime& game_time) override;
  void render(const ASGE::GameTime& game_time) override;

 private:
  void keyHandler(const ASGE::SharedEventData data);
  void clickHandler(const ASGE::SharedEventData data);
  void setupResolution();

  int key_callback_id = -1;   /**< Key Input Callback ID. */
  int mouse_callback_id = -1; /**< Mouse Input Callback ID. */

  SceneManager* scene_manager = nullptr;
  FileHandler file_handler;
  DebugText debug_text;
  Keybinds user_keybinds;
  GetLocalisedString localiser;
  SoLoud::Soloud sound_player;

  SoLoud::Wav background_music;

  ScaledSpriteArray* generic_background = nullptr;

  int po_font = 0;

  json core_config;
};