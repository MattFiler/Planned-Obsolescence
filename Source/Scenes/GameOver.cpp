#include "GameOver.h"
#include "../Constants.h"
#include "../Sprites/ScaledSpriteArray.h"
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Renderer.h>

game_over_type GameOver::game_over = game_over_type::NOT_YET_DECIDED;
game_over_reason GameOver::game_over_v = game_over_reason::ISNT_OVER_YET;

/**
 *   @brief   Loads all variables and sprites for this scene
 *   @details Initialises all variables and creates all the new
                         sprites for the scene
 */
bool GameOver::load(ASGE::Renderer* renderer, ASGE::Input* input, SoLoud::Soloud& player)
{
  renderer->setClearColour(ASGE::COLOURS::BLACK);

  // Share the renderer
  rend = renderer;
  main_menu.giveRenderer(renderer);

  // Sound player
  sound_player = &player;

  // Add menu sprites
  if (game_over == game_over_type::PLAYER_WON)
  {
    main_menu.addMenuSprite("GAME_OVER/BACKGROUND_VICTORY.png");
    debug_text.print("GAME OVER - PLAYER WON");
  }
  else if (game_over == game_over_type::PLAYER_LOST)
  {
    main_menu.addMenuSprite("GAME_OVER/BACKGROUND_LOSS.png");
    debug_text.print("GAME OVER - PLAYER LOST");
  }

  // Add menu options
  main_menu.addMenuItem("retry_game");
  main_menu.addMenuItem("return_to_menu");
  main_menu.addMenuItem("exit_game");

  return true;
}

/**
 *   @brief   Changes game state based on inputs
 *   @details Is called for every input event and will change
 *   @details the game state / variables etc depending
 *   @param   data is the event
 */
void GameOver::keyHandler(const ASGE::SharedEventData data)
{
  user_input.registerEvent(static_cast<const ASGE::KeyEvent*>(data.get()));
  if (main_menu.itemWasSelected(user_input))
  {
    if (main_menu.selectedItemWas("retry_game"))
    {
      next_scene = scenes::GAME_CORE;
      debug_text.print("ENTERING GAME");
    }
    else if (main_menu.selectedItemWas("return_to_menu"))
    {
      next_scene = scenes::MAIN_MENU;
      debug_text.print("RETURNING TO MAIN MENU");
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
void GameOver::mouseHandler(const ASGE::SharedEventData data, Point mouse_position) {}

/**
 *   @brief   Updates all variables for this scene
 *   @details Runs every frame and handles all the logic and updates
 *			 of the active scene
 *   @param  delta_time is time since last update
 *   @return  number of the scene to switch to, -1 no change, -2 exit game
 */
scenes GameOver::update(double delta_time)
{
  return next_scene;
}

/**
 *   @brief   Renders all sprites for this scene
 *   @details Runs every frame and draws all the sprites in
 * 			 order
 */
void GameOver::render(double delta_time)
{
  main_menu.render(delta_time);

  std::string victory_title = "placeholder_text";
  std::string victory_description = "placeholder_text";

  if (game_over == game_over_type::PLAYER_WON)
  {
    victory_title = "game_won";
    victory_description = "project_sabotaged";
  }
  else if (game_over == game_over_type::PLAYER_LOST)
  {
    victory_title = "game_lost";
    if (game_over_v == game_over_reason::PLAYER_WAS_DETECTED)
    {
      victory_description = "guards_spotted_you";
    }
    else
    {
      victory_description = "project_completed";
    }
  }

  rend->renderText(localiser.getString(victory_title),
                   static_cast<int>(650 * ScaledSpriteArray::width_scale),
                   main_menu.getMiddleOfWindow() -
                     (static_cast<int>(20 * ScaledSpriteArray::width_scale)),
                   2.5f,
                   ASGE::COLOURS::WHITE);
  rend->renderText(localiser.getString(victory_description),
                   static_cast<int>(650 * ScaledSpriteArray::width_scale),
                   main_menu.getMiddleOfWindow() +
                     (static_cast<int>(25 * ScaledSpriteArray::width_scale)),
                   0.7f,
                   ASGE::COLOURS::WHITE);
}