#ifndef PO_GAMEOVER
#define PO_GAMEOVER

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
class GameOver : public Scene
{
 public:
  GameOver() = default;
  ~GameOver() = default;
  bool load(ASGE::Renderer* renderer, ASGE::Input* input) override;
  scenes update(double delta_time) override;
  void render(double delta_time) override;
  void keyHandler(const ASGE::SharedEventData data) override;
  void mouseHandler(const ASGE::SharedEventData data, Point mouse_position) override;

  void setGameOverType(game_over_type type) { game_over = type; };
  game_over_type getGameOverType() { return game_over; };

 private:
  Menu main_menu;
  static game_over_type game_over;
  GetLocalisedString localiser;
};

#endif