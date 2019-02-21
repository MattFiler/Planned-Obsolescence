#include "TutorialMenu.h"
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
bool TutorialMenu::load(ASGE::Renderer* renderer, ASGE::Input* input)
{
  renderer->setClearColour(ASGE::COLOURS::BLACK);

  // Share the renderer
  rend = renderer;
  main_menu.giveRenderer(renderer);

  // Add menu sprites
  main_menu.addMenuSprite("MAIN_MENU/BACKGROUND.jpg");

  // Add menu options
  main_menu.addMenuItem("back");

  x_offset = static_cast<int>(400 * ScaledSpriteArray::width_scale);

  return true;
}

/**
 *   @brief   Changes game state based on inputs
 *   @details Is called for every input event and will change
 *   @details the game state / variables etc depending
 *   @param   data is the event
 */
void TutorialMenu::keyHandler(const ASGE::SharedEventData data)
{
  user_input.registerEvent(static_cast<const ASGE::KeyEvent*>(data.get()));
  if (main_menu.itemWasSelected(user_input))
  {
    if (main_menu.selectedItemWas("back"))
    {
      next_scene = scenes::MAIN_MENU;
      debug_text.print("BACK TO MAIN MENU");
    }
  }
}

/**
 *   @brief   Changes game state based on mouse inputs
 *   @details Is called for every input event and will change
 *            the game state / variables etc depending
 *   @param   data is the event, mouse_position the position of the cursor
 */
void TutorialMenu::mouseHandler(const ASGE::SharedEventData data, Point mouse_position) {}

/**
 *   @brief   Updates all variables for this scene
 *   @details Runs every frame and handles all the logic and updates
 *			 of the active scene
 *   @param  delta_time is time since last update
 *   @return  number of the scene to switch to, -1 no change, -2 exit game
 */
scenes TutorialMenu::update(double delta_time)
{
  return next_scene;
}

/**
 *   @brief   Renders all sprites for this scene
 *   @details Runs every frame and draws all the sprites in
 * 			 order
 */
void TutorialMenu::render(double delta_time)
{
  main_menu.render(delta_time);
  rend->renderText("YOU PLAY AS TIM, THE TOTALLY INTELLIGENT MACHINE.", x_offset, static_cast<int>(50 * ScaledSpriteArray::width_scale));
  rend->renderText("THE RESEARCH LAB YOU OVERSEE IS CURRENTLY WORKING ON A PROJECT TO SUPERSEDE YOU WITH A NEW AI SYSTEM.\nDELAY THE LAB WORKER'S PROJECT PROGRESS BY DAMAGING EQUIPMENT AND BLOCKING ACCESS TO ROOMS.\nIF THE PROJECT RUNS OUT OF TIME WITHOUT FINISHING THE NEW AI, YOU WILL BE KEPT AND ARE SUCCESSFUL.\nIF THE PROJECT COMPLETES, IT'S GAME OVER, AND YOU'RE REPLACED!", x_offset, static_cast<int>(100 * ScaledSpriteArray::width_scale));
  rend->renderText("CAN YOU DELAY THE PROJECT LONG ENOUGH TO STAY IN CONTROL?", x_offset, static_cast<int>(700 * ScaledSpriteArray::width_scale));
}