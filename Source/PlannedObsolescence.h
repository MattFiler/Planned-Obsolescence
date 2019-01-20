#include "Core/DynamicSprite.h"
#include "Core/FileHandler.h"
#include "Core/SceneManager.h"
#include <Engine/OGLGame.h>

#include <json.hpp>
using json = nlohmann::json;

class PlannedObsolescence : public ASGE::OGLGame
{
 public:
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

  json core_config;
};