#ifndef PO_MAINMENU
#define PO_MAINMENU

#include "../Debug/DebugText.h"
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
class MainMenu : public Scene
{
 public:
  MainMenu() = default;
  ~MainMenu() = default;
  bool load(ASGE::Renderer* renderer, ASGE::Input* input, SoLoud::Soloud& player) override;
  scenes update(double delta_time) override;
  void render(double delta_time) override;
  void keyHandler(const ASGE::SharedEventData data) override;
  void mouseHandler(const ASGE::SharedEventData data, Point mouse_position) override;

 private:
  Menu main_menu;
};

#endif