#include "GameCore.h"
#include "../Constants.h"
#include "../Sprites/ScaledSpriteArray.h"
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Renderer.h>

#include "../Map/Room.h"
using namespace std;

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

  // TEST CODE
  test_text = TextBox(Point(100, 100),
                      renderer,
                      "The quick brown fox jumps over the lazy dog. The quick brown fox jumps over "
                      "the lazy dog",
                      510,
                      250,
                      1);
  auto* sprite = new ScaledSpriteArray(1);
  ASGE::Sprite* asge_sprite = renderer->createRawSprite();
  asge_sprite->loadTexture("data/UI/default.png");
  sprite->addSprite(*asge_sprite);
  test_text.setBackgroundSprite(sprite);

  test_progress = ProgressBar(Point(100, 500), rend, 200, 20);
  sprite = new ScaledSpriteArray(1);
  asge_sprite = renderer->createRawSprite();
  asge_sprite->loadTexture("data/UI/default.png");
  sprite->addSprite(*asge_sprite);
  test_progress.addBackgroundSprite(sprite);
  sprite = new ScaledSpriteArray(1);
  asge_sprite = renderer->createRawSprite();
  asge_sprite->loadTexture("data/UI/default.png");
  asge_sprite->colour(ASGE::COLOURS::BLUE);
  sprite->addSprite(*asge_sprite);
  test_progress.addFillSprite(sprite);

  sprite = new ScaledSpriteArray(2, false);
  asge_sprite = renderer->createRawSprite();
  asge_sprite->loadTexture("data/UI/default.png");
  asge_sprite->colour(ASGE::COLOURS::WHITE);
  sprite->addSprite(*asge_sprite);
  asge_sprite = renderer->createRawSprite();
  asge_sprite->loadTexture("data/UI/default.png");
  asge_sprite->colour(ASGE::COLOURS::BLACK);
  sprite->addSprite(*asge_sprite);
  test_button = Button(Point(600, 500), renderer, sprite);
  DebugText* debug_ref = &debug_text;
  test_button.click_function = [&debug_ref] { debug_ref->print("Button pressed!"); };

  return true;
}

/* Spawn all characters */
void GameCore::spawnCharacters(ASGE::Renderer* renderer)
{
  if (character_manager.canSpawn(character_type::BOSS))
  {
    Boss* new_boss = new Boss();
    character_manager.spawnCharacter(new_boss);
    new_boss->calculateRouteToPoint(Point(300, 300));
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
      y_axis_input = 1;
    }
    else if (key->action == ASGE::KEYS::KEY_RELEASED)
    {
      y_axis_input = 0;
    }
  }
  else if (key->key == ASGE::KEYS::KEY_S)
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
  else if (key->key == ASGE::KEYS::KEY_A)
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
  else if (key->key == ASGE::KEYS::KEY_D)
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
    mouse_position = camera.displayedToSimulatedWorld(mouse_position);
    if (test_button.checkForClick(mouse_position))
    {
      button_pressed = true;
    }
  }
  else if (click->action == ASGE::MOUSE::BUTTON_RELEASED && button_pressed)
  {
    button_pressed = false;
    test_button.releaseClick();
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
  character_manager.update(delta_time);
  camera.moveCamera(x_axis_input * static_cast<float>(delta_time),
                    y_axis_input * static_cast<float>(delta_time));
  return next_scene;
}

/**
 *   @brief   Renders all sprites for this scene
 *   @details Runs every frame and draws all the sprites in
 * 			 order
 */
void GameCore::render(double delta_time)
{
  rend->renderText("THE GAME", 100, 100, ASGE::COLOURS::RED);

  // Render Map
  game_map.render(delta_time);

  // Render Characters
  character_manager.render(delta_time);

  // TEST CODE
  // test_text.render(delta_time);
  // test_progress.addProgress(static_cast<float>(delta_time) / 10000.0f);
  // test_progress.render(delta_time);
  // test_button.render(delta_time);
}