#include "MainMenu.h"
#include "../Constants.h"
#include "../Core/DynamicSprite.h"
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Renderer.h>

/**
 *   @brief   Loads all variables and sprites for this scene
 *   @details Initialises all variables and creates all the new
                         sprites for the scene
 */
bool MainMenu::load(ASGE::Renderer* renderer, ASGE::Input* input, json core_config)
{
  renderer->setClearColour(ASGE::COLOURS::BLACK);
  rend = renderer;
  return true;
}

/**
 *   @brief   Changes game state based on inputs
 *   @details Is called for every input event and will change
 *   @details the game state / variables etc depending
 *   @param   data is the event
 */
void MainMenu::keyHandler(const ASGE::SharedEventData data)
{
  auto key = static_cast<const ASGE::KeyEvent*>(data.get());
  if (key->key)
  {
    next_scene = 2;
  }
}

/**
 *   @brief   Changes game state based on mouse inputs
 *   @details Is called for every input event and will change
 *            the game state / variables etc depending
 *   @param   data is the event, mouse_position the position of the cursor
 */
void MainMenu::mouseHandler(const ASGE::SharedEventData data, Vector mouse_position)
{
  // auto click = static_cast<const ASGE::ClickEvent*>(data.get());

}

/**
 *   @brief   Updates all variables for this scene
 *   @details Runs every frame and handles all the logic and updates
 *			 of the active scene
 *   @param  delta_time is time since last update
 *   @return  number of the scene to switch to, -1 no change, -2 exit game
 */
int MainMenu::update(double delta_time)
{
  return next_scene;
}

/**
 *   @brief   Renders all sprites for this scene
 *   @details Runs every frame and draws all the sprites in
 * 			 order
 */
void MainMenu::render(double delta_time)
{
  rend->renderText("PRESS ENTER TO CONTINUE TO GAME", 100, 100, ASGE::COLOURS::RED);
}