#include "Splashscreen.h"
#include "../Core/AnimatedSprite.h"
#include "../Constants.h"
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Renderer.h>

/**
 *   @brief   Loads all variables and sprites for this scene
 *   @details Initialises all variables and creates all the new
                         sprites for the scene
 */
bool Splashscreen::load(ASGE::Renderer* renderer, ASGE::Input* input, json core_config)
{
  renderer->setClearColour(ASGE::COLOURS::BLACK);
  rend = renderer;

  po_logo_fg = new GameObject();
  ASGE::Sprite* pos_logo_fg_sprite = renderer->createRawSprite();
  if (!pos_logo_fg_sprite->loadTexture("data/SPLASHSCREENS/PO_LogoFG.png"))
  {
    return false;
  }
  pos_logo_fg_sprite->colour(ASGE::COLOURS::BLACK);

  auto* anim_sprite = new AnimatedSprite(2);
  anim_sprite->addSprite(*pos_logo_fg_sprite);

  anim_sprite->setFadeColour(ASGE::COLOURS::WHITE);
  po_logo_fg->setAnimatedSprite(anim_sprite);
  po_logo_fg->scaleToHeight(core_config["resolution"]["height"].get<float>() / 2);
  po_logo_fg->CenterSpriteOnPoint(core_config["resolution"]["width"].get<float>() / 2, (core_config["resolution"]["height"].get<float>() / 2));

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
  auto key = static_cast<const ASGE::KeyEvent*>(data.get());
  if (key->key)
  {
    // use any keypress to skip title scene
    // next_scene = 1;
  }
}

/**
 *   @brief   Changes game state based on mouse inputs
 *   @details Is called for every input event and will change
 *            the game state / variables etc depending
 *   @param   data is the event, mouse_position the position of the cursor
 */
void Splashscreen::mouseHandler(const ASGE::SharedEventData data, Vector mouse_position) {}

/**
 *   @brief   Updates all variables for this scene
 *   @details Runs every frame and handles all the logic and updates
 *			 of the active scene
 *   @param  delta_time is time since last update
 *   @return  number of the scene to switch to, -1 no change, -2 exit game
 */
int Splashscreen::update(double delta_time)
{
  switch (switch_fade)
  {
    case 0:
    {
      // Fades the logo in
      if (po_logo_fg->getAnimatedSprite()->fadeToColour(1500, delta_time, false))
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
        if (po_logo_fg->getAnimatedSprite()->fadeToColour(500, delta_time, true))
        {
          // setting next_scene here will switch to the scene when returning
          // next_scene = 1;
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
  rend->renderSprite(po_logo_fg->getAnimatedSprite()->returnNextSprite(delta_time));
}