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
  rend = renderer;

  ASGE::Sprite* po_logo_bg_sprite = renderer->createRawSprite();
  if (!po_logo_bg_sprite->loadTexture("data/SPLASHSCREENS/PO_LogoBG.png"))
  {
    return false;
  }

  po_logo_bg = new ScaledSpriteArray(2);
  po_logo_bg->addSprite(*po_logo_bg_sprite);

  po_logo_bg->scale(0.6666f);
  po_logo_bg->xPos(0);
  po_logo_bg->yPos(0);

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
  if (user_input.keyReleased("Activate"))
  {
    if (current_menu_index == 0)
    {
      next_scene = scenes::GAME_CORE;
      debug_text.print("ENTERING GAME");
    }
    else if (current_menu_index == 1)
    {
      next_scene = scenes::QUIT_GAME;
      debug_text.print("EXITING GAME");
    }
  }
  else if (user_input.keyReleased("Menu Up"))
  {
    if (current_menu_index > 0)
    {
      current_menu_index--;
    }
  }
  else if (user_input.keyReleased("Menu Down"))
  {
    if (current_menu_index < menu_item_count - 1)
    {
      current_menu_index++;
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
  // Menu background
  rend->renderSprite(po_logo_bg->returnNextSprite(delta_time));

  // Menu options
  rend->renderText("PLAY",
                   100,
                   static_cast<int>((SCREEN_HEIGHT * po_logo_bg->width_scale / 2) - 100),
                   (current_menu_index == 0) ? ASGE::COLOURS::GREY : ASGE::COLOURS::WHITE);
  rend->renderText("EXIT",
                   100,
                   static_cast<int>((SCREEN_HEIGHT * po_logo_bg->width_scale / 2) + 100),
                   (current_menu_index == 1) ? ASGE::COLOURS::GREY : ASGE::COLOURS::WHITE);
}