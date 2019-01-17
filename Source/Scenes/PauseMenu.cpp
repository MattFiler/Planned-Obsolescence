#include "PauseMenu.h"
#include "../Core/DynamicSprite.h"
#include "../Constants.h"
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Renderer.h>

/**
 *   @brief   Loads all variables and sprites for this scene
 *   @details Initialises all variables and creates all the new
                         sprites for the scene
 */
bool PauseMenu::load(ASGE::Renderer* renderer, ASGE::Input* input, json core_config)
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
void PauseMenu::keyHandler(const ASGE::SharedEventData data)
{
  //auto key = static_cast<const ASGE::KeyEvent*>(data.get());

}

/**
 *   @brief   Changes game state based on mouse inputs
 *   @details Is called for every input event and will change
 *            the game state / variables etc depending
 *   @param   data is the event, mouse_position the position of the cursor
 */
void PauseMenu::mouseHandler(const ASGE::SharedEventData data, Vector mouse_position)
{
  //auto click = static_cast<const ASGE::ClickEvent*>(data.get());

}

/**
 *   @brief   Updates all variables for this scene
 *   @details Runs every frame and handles all the logic and updates
 *			 of the active scene
 *   @param  delta_time is time since last update
 *   @return  number of the scene to switch to, -1 no change, -2 exit game
 */
int PauseMenu::update(double delta_time)
{
  switch (switch_fade)
  {
    case 0:
    {
      break;
    }
    default:
      break;
  }
  return next_scene;
}

/**
 *   @brief   Renders all sprites for this scene
 *   @details Runs every frame and draws all the sprites in
 * 			 order
 */
void PauseMenu::render(double delta_time)
{

}