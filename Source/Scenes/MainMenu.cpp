#include "MainMenu.h"
#include "../Constants.h"
#include "../Sprites/ScaledSpriteArray.h"
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Renderer.h>

/**
 *   @brief   Loads all variables and sprites for this scene
 *   @details Initialises all variables and creates all the new
                         sprites for the scene
 */
bool MainMenu::load(ASGE::Renderer* renderer, ASGE::Input* input)
{
  renderer->setClearColour(ASGE::COLOURS::BLACK);

  // Share the renderer
  rend = renderer;
  main_menu.giveRenderer(renderer);

  // Add menu sprites
  main_menu.addMenuSprite("MAIN_MENU/BACKGROUND.jpg");

  // Add menu options
  main_menu.addMenuItem("play_game");
  main_menu.addMenuItem("exit_game");

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
  user_input.registerEvent(static_cast<const ASGE::KeyEvent*>(data.get()));
  if (main_menu.itemWasSelected(user_input))
  {
    if (main_menu.selectedItemWas("play_game"))
    {
      next_scene = scenes::GAME_CORE;
      debug_text.print("ENTERING GAME");
    }
    else if (main_menu.selectedItemWas("exit_game"))
    {
      next_scene = scenes::QUIT_GAME;
      debug_text.print("EXITING GAME");
    }
  }
}

/**
 *   @brief   Changes game state based on mouse inputs
 *   @details Is called for every input event and will change
 *            the game state / variables etc depending
 *   @param   data is the event, mouse_position the position of the cursor
 */
void MainMenu::mouseHandler(const ASGE::SharedEventData data, Point mouse_position) {}

/**
 *   @brief   Updates all variables for this scene
 *   @details Runs every frame and handles all the logic and updates
 *			 of the active scene
 *   @param  delta_time is time since last update
 *   @return  number of the scene to switch to, -1 no change, -2 exit game
 */
scenes MainMenu::update(double delta_time)
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
  main_menu.render(delta_time);
}