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
class GameOver : public Scene
{
  public:
  GameOver() = default;
  ~GameOver() = default;
  bool load(ASGE::Renderer* renderer, ASGE::Input* input, json core_config) override;
  int update(double delta_time) override;
  void render(double delta_time) override;
  void keyHandler(const ASGE::SharedEventData data) override;
  void mouseHandler(const ASGE::SharedEventData data, Vector mouse_position) override;

  private:

};