#include "../Core/DebugText.h"
#include "../Core/DynamicSprite.h"
#include "../Core/GameObject.h"
#include "Scene.h"

namespace ASGE
{
class Renderer;
}

/**
 **   The first scene of the game, displays logos
 */
class Splashscreen : public Scene
{
 public:
  Splashscreen() = default;
  ~Splashscreen() = default;
  bool load(ASGE::Renderer* renderer, ASGE::Input* input, json core_config) override;
  int update(double delta_time) override;
  void render(double delta_time) override;
  void keyHandler(const ASGE::SharedEventData data) override;
  void mouseHandler(const ASGE::SharedEventData data, Vector mouse_position) override;

 private:
  // All sprites for this scene
  DynamicSprite* po_logo_fg = nullptr;
  DynamicSprite* po_logo_bg = nullptr;
  int switch_fade = 0;
  double time_waited = 0;

  DebugText debug_text;
};