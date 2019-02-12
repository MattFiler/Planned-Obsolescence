#include "Splashscreen.h"
#include "../Constants.h"
#include "../Core/DynamicSprite.h"
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Renderer.h>
using namespace std;

/**
 *   @brief   Loads all variables and sprites for this scene
 *   @details Initialises all variables and creates all the new
                         sprites for the scene
 */
bool Splashscreen::load(ASGE::Renderer* renderer, ASGE::Input* input, json core_config)
{
  renderer->setClearColour(ASGE::COLOURS::BLACK);
  rend = renderer;

  ASGE::Sprite* po_logo_fg_sprite = renderer->createRawSprite();
  if (!po_logo_fg_sprite->loadTexture("data/SPLASHSCREENS/PO_LogoFG.png"))
  {
    return false;
  }
  po_logo_fg_sprite->colour(ASGE::COLOURS::BLACK);

  po_logo_fg = new DynamicSprite(2);
  po_logo_fg->addSprite(*po_logo_fg_sprite);

  po_logo_fg->setFadeColour(ASGE::COLOURS::WHITE);

  po_logo_fg->scale(0.6666f);
  po_logo_fg->xPos(307);
  po_logo_fg->yPos(27);

  ASGE::Sprite* po_logo_bg_sprite = renderer->createRawSprite();
  if (!po_logo_bg_sprite->loadTexture("data/SPLASHSCREENS/PO_LogoBG.png"))
  {
    return false;
  }

  po_logo_bg = new DynamicSprite(2);
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
  auto key = static_cast<const ASGE::KeyEvent*>(data.get());
  if (key->key == ASGE::KEYS::KEY_ENTER && key->action == ASGE::KEYS::KEY_RELEASED)
  {
    next_scene = 1;
    string debug_string = "SKIPPING SPLASHSCREEN";
    debug_text.print(debug_string);
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
int Splashscreen::update(double delta_time)
{
  switch (switch_fade)
  {
    case 0:
    {
      // Fades the logo in
      if (po_logo_fg->fadeToColour(1500, delta_time, false))
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
        if (po_logo_fg->fadeToColour(500, delta_time, true))
        {
          next_scene = 1;
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