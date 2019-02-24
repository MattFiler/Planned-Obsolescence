#include "TutorialCore.h"
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
bool TutorialCore::load(ASGE::Renderer* renderer, ASGE::Input* input, SoLoud::Soloud& player)
{
  renderer->setClearColour(ASGE::COLOURS::BLACK);

  // Share the renderer
  rend = renderer;

  // Load tutorial slides
  tutorial_slides = new ScaledSpriteArray(tutorial_slide_count);
  for (int i = 0; i < tutorial_slide_count; i++)
  {
    ASGE::Sprite* slide = renderer->createRawSprite();
    slide->loadTexture("data/UI/TUTORIAL/" + localiser.getLanguage() + "/" + std::to_string(i) +
                       ".jpg");
    tutorial_slides->addSprite(*slide);
  }
  tutorial_slides->scale(0.6666f);
  tutorial_slides->xPos(1);
  tutorial_slides->yPos(-17);
  tutorial_slides->setCurrentSprite(tutorial_index);

  return true;
}

/**
 *   @brief   Changes game state based on inputs
 *   @details Is called for every input event and will change
 *   @details the game state / variables etc depending
 *   @param   data is the event
 */
void TutorialCore::keyHandler(const ASGE::SharedEventData data)
{
  user_input.registerEvent(static_cast<const ASGE::KeyEvent*>(data.get()));
  if (user_input.keyReleased("Activate"))
  {
    // Increment tutorial slides
    tutorial_index++;
    if (tutorial_index <= tutorial_slide_count)
    {
      tutorial_slides->setCurrentSprite(tutorial_index);
    }
  }
}

/**
 *   @brief   Changes game state based on mouse inputs
 *   @details Is called for every input event and will change
 *            the game state / variables etc depending
 *   @param   data is the event, mouse_position the position of the cursor
 */
void TutorialCore::mouseHandler(const ASGE::SharedEventData data, Point mouse_position) {}

/**
 *   @brief   Updates all variables for this scene
 *   @details Runs every frame and handles all the logic and updates
 *			 of the active scene
 *   @param  delta_time is time since last update
 *   @return  number of the scene to switch to, -1 no change, -2 exit game
 */
scenes TutorialCore::update(double delta_time)
{
  // Return to main menu when tutorial is over
  if (tutorial_index >= tutorial_slide_count)
  {
    next_scene = scenes::TUTORIAL_MENU;
  }
  return next_scene;
}

/**
 *   @brief   Renders all sprites for this scene
 *   @details Runs every frame and draws all the sprites in
 * 			 order
 */
void TutorialCore::render(double delta_time)
{
  // Render current tutorial slide
  rend->renderSprite(tutorial_slides->returnCurrentSprite());
}