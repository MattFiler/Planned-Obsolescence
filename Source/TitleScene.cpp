//
// Created by tobyj on 15/01/2019.
//

#include "TitleScene.h"
#include "AnimatedSprite.h"
#include "Constants.h"
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Renderer.h>

/**
 *   @brief   Loads all variables and sprites for this scene
 *   @details Initialises all variables and creates all the new
                         sprites for the scene
 */
bool TitleScene::load(ASGE::Renderer* renderer, ASGE::Input* input)
{
  renderer->setClearColour(ASGE::COLOURS::BLACK);
  rend = renderer;

  asge_logo = new GameObject();
  uwe_logo = new GameObject();
  ASGE::Sprite* new_sprite = renderer->createRawSprite();
  if (!new_sprite->loadTexture("ASGELogo.png"))
  {
    return false;
  }
  new_sprite->colour(ASGE::COLOURS::BLACK);
  auto* anim_sprite = new AnimatedSprite(1);
  anim_sprite->addSprite(*new_sprite);

  anim_sprite->setFadeColour(ASGE::COLOURS::WHITE);
  asge_logo->setAnimatedSprite(anim_sprite);
  asge_logo->scaleToHeight(BASE_HEIGHT / 2);
  asge_logo->CenterSpriteOnPoint(BASE_WIDTH / 2, (BASE_HEIGHT / 2));

  new_sprite = renderer->createRawSprite();
  if (!new_sprite->loadTexture("UWELogo.png"))
  {
    return false;
  }
  anim_sprite = new AnimatedSprite(1);
  anim_sprite->addSprite(*new_sprite);

  anim_sprite->setFadeColour(ASGE::COLOURS::WHITE);
  uwe_logo->setAnimatedSprite(anim_sprite);
  uwe_logo->scaleToHeight(BASE_HEIGHT / 2);
  uwe_logo->CenterSpriteOnPoint(BASE_WIDTH / 2, (BASE_HEIGHT / 2));

  return true;
}

/**
 *   @brief   Changes game state based on inputs
 *   @details Is called for every input event and will change
 *   @details the game state / variables etc depending
 *   @param   data is the event
 */
void TitleScene::keyHandler(const ASGE::SharedEventData data)
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
void TitleScene::mouseHandler(const ASGE::SharedEventData data, Vector mouse_position) {}

/**
 *   @brief   Updates all variables for this scene
 *   @details Runs every frame and handles all the logic and updates
 *			 of the active scene
 *   @param  delta_time is time since last update
 *   @return  number of the scene to switch to, -1 no change, -2 exit game
 */
int TitleScene::update(double delta_time)
{
  switch (switch_fade)
  {
    case 0:
    {
      // Fades the logo in
      if (asge_logo->getAnimatedSprite()->fadeToColour(1500, delta_time, false))
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
        if (asge_logo->getAnimatedSprite()->fadeToColour(500, delta_time, true))
        {
          switch_fade = 2;
          time_waited = 0;
        }
      }
      break;
    }
    case 2:
    {
      // Fades the logo in
      if (uwe_logo->getAnimatedSprite()->fadeToColour(1500, delta_time, false))
      {
        switch_fade = 3;
      }
      break;
    }
    case 3:
    {
      // Waits a bit
      time_waited += delta_time;
      if (time_waited > 1500)
      {
        // Fades the logo out
        if (uwe_logo->getAnimatedSprite()->fadeToColour(500, delta_time, true))
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
void TitleScene::render(double delta_time)
{
  if (switch_fade < 2)
  {
    rend->renderSprite(asge_logo->getAnimatedSprite()->returnNextSprite(delta_time));
  }
  else
  {
    rend->renderSprite(uwe_logo->getAnimatedSprite()->returnNextSprite(delta_time));
  }
}