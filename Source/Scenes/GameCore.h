#include "../Core/CharacterManager.h"
#include "../Core/DebugText.h"
#include "../Core/DynamicSprite.h"
#include "../Core/GameObject.h"
#include "../Map/GameMap.h"
#include "Scene.h"

namespace ASGE
{
class Renderer;
}

/**
 **   The core game scene
 */
class GameCore : public Scene
{
 public:
  GameCore() = default;
  ~GameCore() = default;
  bool load(ASGE::Renderer* renderer, ASGE::Input* input, json core_config) override;
  int update(double delta_time) override;
  void render(double delta_time) override;
  void keyHandler(const ASGE::SharedEventData data) override;
  void mouseHandler(const ASGE::SharedEventData data, Vector mouse_position) override;

 private:
  void spawnCharacters(ASGE::Renderer* renderer);

  CharacterManager character_manager;
  GameMap game_map;
  DebugText debug_text;
};