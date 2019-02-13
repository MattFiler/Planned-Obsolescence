#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <memory>

#include "../Constants.h"
#include "../Scenes/Scene.h"
#include "Point.h"

#include <json.hpp>
using json = nlohmann::json;

namespace ASGE
{
class Renderer;
struct EventData;
}

/**
 *  Stores all of the games scenes and handles loading and unloading them
 */
class SceneManager
{
 public:
  SceneManager();
  ~SceneManager();

  // Changes the active scene to the passed scene
  bool loadCurrentScene(ASGE::Renderer* renderer, ASGE::Input* input);
  int updateCurrentScene(double delta_time);
  void renderCurrentScene(double delta_time);
  void sceneKeyHandler(const ASGE::SharedEventData data);
  void sceneMouseHandler(const ASGE::SharedEventData data, Point mouse_position);

  Scene* current_scene = nullptr;

 private:
  void swapScene(Scene* new_scene);
};