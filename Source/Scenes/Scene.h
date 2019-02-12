#ifndef PO_SCENE
#define PO_SCENE

#include "../Core/Point.h"

#include "../../Libs/ASGE/include/Engine/Colours.h"
#include "../../Libs/ASGE/include/Engine/Input.h"
#include "../../Libs/ASGE/include/Engine/InputEvents.h"
#include <memory>

#include "../../Libs/nlohmann/json.hpp"
using json = nlohmann::json;

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
  virtual bool load(ASGE::Renderer* renderer, ASGE::Input* input, json core_config) = 0;
  virtual int update(double delta_time) = 0;
  virtual void render(double delta_time) = 0;
  virtual void keyHandler(const ASGE::SharedEventData data) = 0;
  virtual void mouseHandler(const ASGE::SharedEventData data, Point mouse_position) = 0;

 protected:
  int next_scene = -1;
  ASGE::Colour clear_colour = ASGE::COLOURS::BLACK;
  ASGE::Renderer* rend = nullptr;
};

#endif