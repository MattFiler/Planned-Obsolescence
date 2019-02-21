#ifndef PO_SCENE
#define PO_SCENE

#include "../Constants.h"
#include "../Debug/DebugText.h"
#include "../Keybinds/Keybinds.h"
#include "../Math/Point.h"

#include <Engine/Colours.h>
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <memory>
#include <soloud.h>
#include <soloud_wav.h>

namespace ASGE
{
class Renderer;
struct EventData;
}

/**
 *  Holds all of the data and update code for a scene
 */
class Scene
{
 public:
  Scene() = default;
  virtual ~Scene() = default;
  virtual bool load(ASGE::Renderer* renderer, ASGE::Input* input, SoLoud::Soloud& player) = 0;
  virtual scenes update(double delta_time) = 0;
  virtual void render(double delta_time) = 0;
  virtual void keyHandler(const ASGE::SharedEventData data) = 0;
  virtual void mouseHandler(const ASGE::SharedEventData data, Point mouse_position) = 0;

 protected:
  // Scene data
  scenes next_scene = scenes::NO_CHANGE;

  // Engine features
  ASGE::Renderer* rend = nullptr;
  Keybinds user_input;
  DebugText debug_text;
  SoLoud::Soloud* sound_player;
};

#endif