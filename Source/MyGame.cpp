#include <iostream>

#include <Engine/DebugPrinter.h>
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Keys.h>
#include <Engine/Platform.h>
#include <Engine/Sprite.h>

#include "Constants.h"
#include "MyGame.h"
#include "TitleScene.h"

MyGame::~MyGame()
{
  if (scene_manager)
  {
    delete scene_manager;
    scene_manager = nullptr;
  }
}

bool MyGame::init()
{
  setupResolution();
  game_name = "Planned Obsolescence";

  if (!initAPI())
  {
    return false;
  }

  toggleFPS();

  // input handling functions
  inputs->use_threads = false;

  key_callback_id = inputs->addCallbackFnc(ASGE::E_KEY, &MyGame::keyHandler, this);

  mouse_callback_id = inputs->addCallbackFnc(ASGE::E_MOUSE_CLICK, &MyGame::clickHandler, this);

  scene_manager = new SceneManager();

  scene_manager->current_scene = new TitleScene();
  return scene_manager->loadCurrentScene(renderer.get(), inputs.get());
}

/**
 *   @brief   Sets the game window resolution
 *   @details Sets the resolution for the game window, as well as the scale
 *            factor for AnimatedSprite
 *   @return  void
 */
void MyGame::setupResolution()
{
  // Here you could load the resolution from file, but since it used the old
  // file system I haven't copied across what I did for angry birds,
  // so im just going to put it as a set resolution for now

  AnimatedSprite::width_scale = 1;

  game_width = BASE_WIDTH;
  game_height = BASE_HEIGHT;
}

/**
 *   @brief   Processes any key inputs
 *   @details This function is added as a callback to handle the game's
 *             keyboard input. For this game, calls to this function
 *            are thread safe, so you may alter the game's state as you
 *            see fit.
 *   @param   data The event data relating to key input.
 *   @see     KeyEvent
 *   @return  void
 */
void MyGame::keyHandler(const ASGE::SharedEventData data)
{
  scene_manager->sceneKeyHandler(data);
}

/**
 *   @brief   Processes any click inputs
 *   @details This function is added as a callback to handle the game's
 *            mouse button input. For this game, calls to this function
 *            are thread safe, so you may alter the game's state as you
 *            see fit.
 *   @param   data The event data relating to key input.
 *   @see     ClickEvent
 *   @return  void
 */
void MyGame::clickHandler(const ASGE::SharedEventData data)
{
  double x_pos, y_pos;
  inputs->getCursorPos(x_pos, y_pos);
  scene_manager->sceneMouseHandler(data,
                                   Vector(static_cast<float>(x_pos), static_cast<float>(y_pos)));
}

/**
 *   @brief   Updates the scene
 *   @details Prepares the renderer subsystem before drawing the
 *            current frame. Once the current frame is has finished
 *            the buffers are swapped accordingly and the image shown.
 *   @return  void
 */
void MyGame::update(const ASGE::GameTime& game_time)
{
  int num = scene_manager->updateCurrentScene(game_time.delta_time.count());
  if (num == 1)
  {
    if (!scene_manager->loadCurrentScene(renderer.get(), inputs.get()))
    {
      signalExit();
    }
  }
  else if (num == -1)
  {
    signalExit();
  }
}

/**
 *   @brief   Renders the scene
 *   @details Renders all the game objects to the current frame.
 *            Once the current frame is has finished the buffers are
 *            swapped accordingly and the image shown.
 *   @return  void
 */
void MyGame::render(const ASGE::GameTime& game_time)
{
  scene_manager->renderCurrentScene(game_time.delta_time.count());
}