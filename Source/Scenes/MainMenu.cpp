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
  main_menu.addMenuSprite("SPLASHSCREENS/PO_LogoBG.png")->scale(0.6666f);

  // Add menu options
  main_menu.addMenuItem("PLAY");
  main_menu.addMenuItem("EXIT");

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
  int menu_activated = main_menu.keyHandler(user_input);
  if (menu_activated != -1)
  {
    if (menu_activated == 0)
    {
      next_scene = scenes::GAME_CORE;
      debug_text.print("ENTERING GAME");
    }
    else if (menu_activated == 1)
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