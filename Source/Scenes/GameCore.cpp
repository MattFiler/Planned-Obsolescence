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

GameCore::~GameCore()
{
  // player.deinit();
}

bool GameCore::load(ASGE::Renderer* renderer, ASGE::Input* input)
{
  // Setup
  renderer->setClearColour(ASGE::COLOURS::BLACK);
  rend = renderer;

  // load map
  game_map.load(renderer, &camera);

  // Pass references out and spawn characters
  passReferences(input);
  spawnCharacters(renderer);

  // Create UI
  ui_manager.createMainHUD(&character_manager);

  Button* quit_button = new Button(Point(SCREEN_WIDTH - 148, 0),
                                   renderer,
                                   "data/UI/IN_GAME_UI/TOP_RIGHT_QUIT.png",
                                   "data/UI/IN_GAME_UI/TOP_RIGHT_QUIT_HOVER.png",
                                   148,
                                   53,
                                   "exit_game",
                                   0.7f,
                                   Point(45, 17));
  scenes* next = &next_scene;
  quit_button->click_function = [next] { *next = scenes::MAIN_MENU; };
  ui_manager.addButton(quit_button);

  // Reset game over config for new load
  game_over_instance.setGameOverType(game_over_type::NOT_YET_DECIDED);
  project_gauge.resetAll();

  /*
  player.init();
  file_handler.loadSound(sound_file, "CLICK_11.wav");
  player.play(sound_file);
   */

  return true;
}

/* Pass references to other classes */
void GameCore::passReferences(ASGE::Input* input)
{
  camera.setRenderer(rend);

  ui_manager.setRenderer(rend);
  ui_manager.setInputData(input);
  ui_manager.setCamera(&camera);

  character_manager.setMap(&game_map);
  character_manager.setCamera(&camera);
  character_manager.setUIManager(&ui_manager);

  project_gauge.setUIManager(&ui_manager);
  project_gauge.setCharacterManager(&character_manager);

  game_map.setUIManager(&ui_manager);
}

/* Spawn all characters */
void GameCore::spawnCharacters(ASGE::Renderer* renderer)
{
  if (character_manager.canSpawn(character_type::GOON))
  {
    Goon* new_goon = new Goon();
    character_manager.spawnCharacter(new_goon);
    new_goon->setSpawnPosition(100, 150);
    new_goon = new Goon();
    character_manager.spawnCharacter(new_goon);
    new_goon->setSpawnPosition(500, 150);
    new_goon = new Goon();
    character_manager.spawnCharacter(new_goon);
    new_goon->setSpawnPosition(500, 500);
  }
  if (character_manager.canSpawn(character_type::SECURITY))
  {
    Security* new_guard = new Security();
    character_manager.spawnCharacter(new_guard);
    new_guard->setSpawnPosition(150, 150);
    // std::vector<Point>* route = new_guard->getPatrolRoute();
    // route->push_back(Point(game_map.getMapData()->rooms_x))
  }

  if (character_manager.canSpawn(character_type::TECHNICIAN))
  {
    LabTechnician* new_tech = new LabTechnician();
    character_manager.spawnCharacter(new_tech);
    new_tech->setSpawnPosition(100, 100);
    new_tech = new LabTechnician();
    character_manager.spawnCharacter(new_tech);
    new_tech->setSpawnPosition(100, 100);
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
      if (!character_manager.checkForClick(camera.displayedToSimulatedWorld(mouse_position)))
      {
        game_map.clickedPointCheck(camera.displayedToSimulatedWorld(mouse_position));
      }
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

  // Update gauges and check for ending conditions (end game if required)
  game_over_type current_endstate = project_gauge.update(delta_time);
  if (current_endstate != game_over_type::NOT_YET_DECIDED)
  {
    endGame(current_endstate);
  }

  // Update managers
  ui_manager.update();
  character_manager.update(delta_time);

  // Check for cursor hover
  Point click_position = ui_manager.getCursor()->getPosition();
  if (ui_manager.checkForClick(click_position / ScaledSpriteArray::width_scale, false) ||
      character_manager.checkForClick(camera.displayedToSimulatedWorld(click_position), false) ||
      game_map.clickedPointCheck(camera.displayedToSimulatedWorld(click_position), false))
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

/* Trigger a game over */
void GameCore::endGame(game_over_type type)
{
  game_over_instance.setGameOverType(type);
  game_over_instance.setGameOverReason(project_gauge.whyDidGameEnd());
  next_scene = scenes::GAME_OVER;
}