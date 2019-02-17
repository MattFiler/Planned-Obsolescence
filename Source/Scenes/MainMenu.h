#include "../Debug/DebugText.h"
#include "../Sprites/ScaledSpriteArray.h"
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
  bool load(ASGE::Renderer* renderer, ASGE::Input* input) override;
  scenes update(double delta_time) override;
  void render(double delta_time) override;
  void keyHandler(const ASGE::SharedEventData data) override;
  void mouseHandler(const ASGE::SharedEventData data, Point mouse_position) override;

 private:
  ScaledSpriteArray* po_logo_bg = nullptr;
  int current_menu_index = 0;
  int menu_item_count = 2;
};