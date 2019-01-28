#include "GameCore.h"
#include "../Constants.h"
#include "../Core/DynamicSprite.h"
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Renderer.h>

#include "../Map/Room.h"
using namespace std;

/**
 *   @brief   Loads all variables and sprites for this scene
 *   @details Initialises all variables and creates all the new
                         sprites for the scene
 */
bool GameCore::load(ASGE::Renderer* renderer, ASGE::Input* input, json core_config)
{
  renderer->setClearColour(ASGE::COLOURS::BLACK);
  rend = renderer;

  game_map.load(renderer);

  character_manager.setMap(&game_map);

  spawnCharacters(renderer);

  return true;
}

/* Spawn all characters */
void GameCore::spawnCharacters(ASGE::Renderer* renderer)
{
  Boss boss_demo;
  boss_demo.wake(renderer);
  boss_demo.setSpawnPosition(0, 0);
  character_manager.spawn(boss_demo);
}

/**
 *   @brief   Changes game state based on inputs
 *   @details Is called for every input event and will change
 *   @details the game state / variables etc depending
 *   @param   data is the event
 */
void GameCore::keyHandler(const ASGE::SharedEventData data)
{
  auto key = static_cast<const ASGE::KeyEvent*>(data.get());
  if (key->key == ASGE::KEYS::KEY_ESCAPE && key->action == ASGE::KEYS::KEY_RELEASED)
  {
    next_scene = 1;
    string debug_string = "RETURNING TO MAIN MENU";
    debug_text.print(debug_string);
  }
}

/**
 *   @brief   Changes game state based on mouse inputs
 *   @details Is called for every input event and will change
 *            the game state / variables etc depending
 *   @param   data is the event, mouse_position the position of the cursor
 */
void GameCore::mouseHandler(const ASGE::SharedEventData data, Vector mouse_position) {}

/**
 *   @brief   Updates all variables for this scene
 *   @details Runs every frame and handles all the logic and updates
 *			 of the active scene
 *   @param  delta_time is time since last update
 *   @return  number of the scene to switch to, -1 no change, -2 exit game
 */
int GameCore::update(double delta_time)
{
  character_manager.update(delta_time);
  return next_scene;
}

/**
 *   @brief   Renders all sprites for this scene
 *   @details Runs every frame and draws all the sprites in
 * 			 order
 */
void GameCore::render(double delta_time)
{
  rend->renderText("THE GAME", 100, 100, ASGE::COLOURS::RED);

  // Render Map
  game_map.render();

  // Render Characters
  character_manager.render(delta_time, rend);
}