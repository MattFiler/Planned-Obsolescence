#include "Splashscreen.h"
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
bool Splashscreen::load(ASGE::Renderer* renderer, ASGE::Input* input, SoLoud::Soloud& player)
{
  renderer->setClearColour(ASGE::COLOURS::BLACK);
  rend = renderer;

  sound_player = &player;

  ASGE::Sprite* po_logo_fg_sprite = renderer->createRawSprite();
  if (!po_logo_fg_sprite->loadTexture("data/UI/SPLASHSCREEN/FOREGROUND.png"))
  {
    return false;
  }
  po_logo_fg_sprite->colour(ASGE::COLOURS::BLACK);

  po_logo_fg = new ScaledSpriteArray(2);
  po_logo_fg->addSprite(*po_logo_fg_sprite);

  po_logo_fg->scale(0.6666f);
  po_logo_fg->xPos(307);
  po_logo_fg->yPos(20);
  po_logo_fg->setColour(ASGE::COLOURS::WHITE);

  ASGE::Sprite* po_logo_bg_sprite = renderer->createRawSprite();
  if (!po_logo_bg_sprite->loadTexture("data/UI/SPLASHSCREEN/BACKGROUND.png"))
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
void Splashscreen::keyHandler(const ASGE::SharedEventData data)
{
  user_input.registerEvent(static_cast<const ASGE::KeyEvent*>(data.get()));
  if (user_input.keyReleased("Activate"))
  {
    next_scene = scenes::MAIN_MENU;
    debug_text.print("SKIPPING SPLASHSCREEN");
  }
}

/**
 *   @brief   Changes game state based on mouse inputs
 *   @details Is called for every input event and will change
 *            the game state / variables etc depending
 *   @param   data is the event, mouse_position the position of the cursor
 */
void Splashscreen::mouseHandler(const ASGE::SharedEventData data, Point mouse_position) {}

/**
 *   @brief   Updates all variables for this scene
 *   @details Runs every frame and handles all the logic and updates
 *			 of the active scene
 *   @param  delta_time is time since last update
 *   @return  number of the scene to switch to, -1 no change, -2 exit game
 */
scenes Splashscreen::update(double delta_time)
{
  switch (switch_fade)
  {
    case 0:
    {
      // Fades the logo in
      if (po_logo_fg->fadeIn(1500, delta_time))
      {
        switch_fade = 1;
      }
      break;
    }
    case 1:
    {
      // Waits a bit
      time_waited += delta_time;
      if (time_waited > 1500)
      {
        // Fades the logo out
        if (po_logo_fg->fadeOut(500, delta_time))
        {
          next_scene = scenes::MAIN_MENU;
        }
      }
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
void Splashscreen::render(double delta_time)
{
  rend->renderSprite(po_logo_bg->returnNextSprite(delta_time));
  rend->renderSprite(po_logo_fg->returnNextSprite(delta_time));
}