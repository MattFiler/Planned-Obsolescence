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
  bool load(ASGE::Renderer* renderer, ASGE::Input* input, SoLoud::Soloud& player) override;
  scenes update(double delta_time) override;
  void render(double delta_time) override;
  void keyHandler(const ASGE::SharedEventData data) override;
  void mouseHandler(const ASGE::SharedEventData data, Point mouse_position) override;

  void setGameOverType(game_over_type type) { game_over = type; };
  void setGameOverReason(game_over_reason reason) { game_over_v = reason; };
  game_over_type getGameOverType() { return game_over; };
  game_over_reason getGameOverReason() { return game_over_v; };

 private:
  Menu main_menu;
  FileHandler file_handler;
  static game_over_type game_over;
  static game_over_reason game_over_v;
  GetLocalisedString localiser;

  SoLoud::Wav ending_sound;
};

#endif