#ifndef PO_PAUSEMENU
#define PO_PAUSEMENU

#include "../Sprites/ScaledSpriteArray.h"
#include "Scene.h"

namespace ASGE
{
class Renderer;
}

/**
 **   The first scene of the game, displays logos
 */
class PauseMenu : public Scene
{
 public:
  PauseMenu() = default;
  ~PauseMenu() = default;
  bool load(ASGE::Renderer* renderer, ASGE::Input* input) override;
  scenes update(double delta_time) override;
  void render(double delta_time) override;
  void keyHandler(const ASGE::SharedEventData data) override;
  void mouseHandler(const ASGE::SharedEventData data, Point mouse_position) override;
};

#endif