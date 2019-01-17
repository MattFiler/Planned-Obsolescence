#include <iostream>

#include <Engine/DebugPrinter.h>
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Keys.h>
#include <Engine/Platform.h>
#include <Engine/Sprite.h>

#include "Constants.h"
#include "PlannedObsolescence.h"
#include "Scenes/Splashscreen.h"

PlannedObsolescence::~PlannedObsolescence()
{
  if (scene_manager)
  {
    delete scene_manager;
    scene_manager = nullptr;
  }
}

bool PlannedObsolescence::init()
{
  // Load core configurations
  core_config = file_handler.openAsJSON("CONFIGS/game_core.json");

  // Configure resolution and game title
  setupResolution();
  game_name = "Planned Obsolescence";

  // Initialise the engine
  if (!initAPI())
  {
    return false;
  }

  // Display debug data if requested
  if (core_config["debug_enabled"])
  {
    toggleFPS();
  }

  // Disable input threading
  inputs->use_threads = false;

  // Assign input callbacks
  key_callback_id = inputs->addCallbackFnc(ASGE::E_KEY, &PlannedObsolescence::keyHandler, this);
  mouse_callback_id =
    inputs->addCallbackFnc(ASGE::E_MOUSE_CLICK, &PlannedObsolescence::clickHandler, this);

  // Initialise the scene manager
  scene_manager = new SceneManager();

  // Start out on the splashscreen scene
  scene_manager->current_scene = new Splashscreen();
  return scene_manager->loadCurrentScene(renderer.get(), inputs.get(), core_config);
}

/**
 *   @brief   Sets the game window resolution
 *   @details Sets the resolution for the game window, as well as the scale
 *            factor for AnimatedSprite
 *   @return  void
 */
void PlannedObsolescence::setupResolution()
{
  DynamicSprite::width_scale = 1;

  game_width = core_config["resolution"]["width"];
  game_height = core_config["resolution"]["height"];
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
void PlannedObsolescence::keyHandler(const ASGE::SharedEventData data)
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
void PlannedObsolescence::clickHandler(const ASGE::SharedEventData data)
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
void PlannedObsolescence::update(const ASGE::GameTime& game_time)
{
  int num = scene_manager->updateCurrentScene(game_time.delta_time.count());
  if (num == 1)
  {
    if (!scene_manager->loadCurrentScene(renderer.get(), inputs.get(), core_config))
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
void PlannedObsolescence::render(const ASGE::GameTime& game_time)
{
  scene_manager->renderCurrentScene(game_time.delta_time.count());
}