#ifndef PO_PAUSEMENU
#define PO_PAUSEMENU

#include "../Sprites/ScaledSpriteArray.h"
#include "../UI/Menu.h"
#include "Scene.h"

namespace ASGE
{
class Renderer;
}

/**
 **   The first scene of the game, displays logos
 */
class TutorialMenu : public Scene
{
 public:
  TutorialMenu() = default;
  ~TutorialMenu() = default;
  bool load(ASGE::Renderer* renderer, ASGE::Input* input) override;
  scenes update(double delta_time) override;
  void render(double delta_time) override;
  void keyHandler(const ASGE::SharedEventData data) override;
  void mouseHandler(const ASGE::SharedEventData data, Point mouse_position) override;

 private:
  Menu main_menu;
  GetLocalisedString localiser;
  int x_offset = 0;
};

#endif