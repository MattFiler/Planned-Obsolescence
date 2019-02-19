#include "GameCore.h"
#include "../Constants.h"
#include "../Sprites/ScaledSpriteArray.h"
#include "../UI/GenericUI.h"
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Renderer.h>

#include "../Map/Room.h"

/**
 *   @brief   Loads all variables and sprites for this scene
 *   @details Initialises all variables and creates all the new
                         sprites for the scene
 */
bool GameCore::load(ASGE::Renderer* renderer, ASGE::Input* input)
{
  renderer->setClearColour(ASGE::COLOURS::BLACK);
  rend = renderer;
  camera.setRenderer(rend);

  game_map.load(renderer, &camera);

  character_manager.setMap(&game_map);
  character_manager.setCamera(&camera);

  spawnCharacters(renderer);

  ui_manager.setRenderer(rend);
  ui_manager.setInputData(input);
  ui_manager.setCamera(&camera);
  character_manager.setUIManager(&ui_manager);

  ui_manager.createMainHUD();

  Button* quit_button = new Button(Point(SCREEN_WIDTH - 148, 0),
                                   renderer,
                                   "data/UI/IN_GAME_UI/TOP_RIGHT_QUIT.png",
                                   "data/UI/IN_GAME_UI/TOP_RIGHT_QUIT.png",
                                   148,
                                   53);
  scenes* next = &next_scene;
  quit_button->click_function = [next] { *next = scenes::MAIN_MENU; };
  ui_manager.addButton(quit_button);

  return true;
}

/* Spawn all characters */
void GameCore::spawnCharacters(ASGE::Renderer* renderer)
{
  if (character_manager.canSpawn(character_type::GOON))
  {
    Goon* new_goon = new Goon();
    character_manager.spawnCharacter(new_goon);
  }
}

/**
 *   @brief   Changes game state based on inputs
 *   @details Is called for every input event and will change
 *   @details the game state / variables etc depending
 *   @param   data is the event
 */
void GameCore::keyHandler(const ASGE::SharedEventData data)
{
  user_input.registerEvent(static_cast<const ASGE::KeyEvent*>(data.get()));
  if (user_input.keyReleased("Back"))
  {
    next_scene = scenes::MAIN_MENU;
    debug_text.print("RETURNING TO MAIN MENU");
  }

  auto key = static_cast<const ASGE::KeyEvent*>(data.get());
  if (key->key == ASGE::KEYS::KEY_W)
  {
    if (key->action == ASGE::KEYS::KEY_PRESSED)
    {
      y_axis_input = -1;
    }
    else if (key->action == ASGE::KEYS::KEY_RELEASED)
    {
      y_axis_input = 0;
    }
  }
  if (key->key == ASGE::KEYS::KEY_S)
  {
    if (key->action == ASGE::KEYS::KEY_PRESSED)
    {
      y_axis_input = 1;
    }
    else if (key->action == ASGE::KEYS::KEY_RELEASED)
    {
      y_axis_input = 0;
    }
  }
  if (key->key == ASGE::KEYS::KEY_A)
  {
    if (key->action == ASGE::KEYS::KEY_PRESSED)
    {
      x_axis_input = -1;
    }
    else if (key->action == ASGE::KEYS::KEY_RELEASED)
    {
      x_axis_input = 0;
    }
  }
  if (key->key == ASGE::KEYS::KEY_D)
  {
    if (key->action == ASGE::KEYS::KEY_PRESSED)
    {
      x_axis_input = 1;
    }
    else if (key->action == ASGE::KEYS::KEY_RELEASED)
    {
      x_axis_input = 0;
    }
  }
}

/**
 *   @brief   Changes game state based on mouse inputs
 *   @details Is called for every input event and will change
 *            the game state / variables etc depending
 *   @param   data is the event, mouse_position the position of the cursor
 */
void GameCore::mouseHandler(const ASGE::SharedEventData data, Point mouse_position)
{
  auto click = static_cast<const ASGE::ClickEvent*>(data.get());

  if (click->action == ASGE::MOUSE::BUTTON_PRESSED)
  {
    // If the UI manager doesn't register this click
    if (!ui_manager.checkForClick(mouse_position / ScaledSpriteArray::width_scale))
    {
      character_manager.checkForClick(camera.displayedToSimulatedWorld(mouse_position));
    }
  }
  else if (click->action == ASGE::MOUSE::BUTTON_RELEASED)
  {
    ui_manager.releaseClick();
  }
}

/**
 *   @brief   Updates all variables for this scene
 *   @details Runs every frame and handles all the logic and updates
 *			 of the active scene
 *   @param  delta_time is time since last update
 *   @return  number of the scene to switch to, -1 no change, -2 exit game
 */
scenes GameCore::update(double delta_time)
{
  // Handle camera movement
  camera.moveCamera(x_axis_input * static_cast<float>(delta_time),
                    y_axis_input * static_cast<float>(delta_time));

  // Update managers
  ui_manager.update(delta_time);
  character_manager.update(delta_time);

  // Update project gauge
  project_gauge.update(delta_time);

  // Check for cursor hover
  if (ui_manager.checkForClick(
        ui_manager.getCursor()->getPosition() / ScaledSpriteArray::width_scale, false) ||
      character_manager.checkForClick(
        camera.displayedToSimulatedWorld(ui_manager.getCursor()->getPosition()), false))
  {
    ui_manager.getCursor()->setCursorType(cursor_variant::CURSOR_POINTER);
  }
  else
  {
    ui_manager.getCursor()->setCursorType(cursor_variant::CURSOR_DEFAULT);
  }

  return next_scene;
}

/**
 *   @brief   Renders all sprites for this scene
 *   @details Runs every frame and draws all the sprites in
 * 			 order
 */
void GameCore::render(double delta_time)
{
  // Render Map
  game_map.render(delta_time);

  // Render Characters
  character_manager.render(delta_time);

  // Render UI
  ui_manager.render(delta_time);
}