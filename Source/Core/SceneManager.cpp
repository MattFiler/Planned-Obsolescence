#include "SceneManager.h"
#include "../Scenes/Splashscreen.h"
#include "../Scenes/GameCore.h"
#include "../Scenes/GameOver.h"
#include "../Scenes/MainMenu.h"
#include "../Scenes/PauseMenu.h"

/**
 *   @brief   Constructor
 *   @details Needs a reference to the running games renderer
 *   @param   Adress of current game
 */
SceneManager::SceneManager() {}

/**
 *   @brief   Default Deconstructor.
 */
SceneManager::~SceneManager()
{
  if (current_scene)
  {
    delete current_scene;
    current_scene = nullptr;
  }
}

/**
 *   @brief   Loads the active scene
 *   @details Calls loadScene() on scene that is currently active
 *   @param   renderer is a pointer to the renderer
 */
bool SceneManager::loadCurrentScene(ASGE::Renderer* renderer, ASGE::Input* input, json core_config)
{
  return current_scene->load(renderer, input, core_config);
}

/**
 *   @brief   Handles inputs of the active scene
 *   @param   data is the event
 */
void SceneManager::sceneKeyHandler(const ASGE::SharedEventData data)
{
  current_scene->keyHandler(data);
}

/**
 *   @brief   Handles mouse clicks and movement of the active scene
 *   @param   data is the eventm mouse_position is the position of the cursor on screen
 */
void SceneManager::sceneMouseHandler(const ASGE::SharedEventData data, Vector mouse_position)
{
  current_scene->mouseHandler(data, mouse_position);
}

/**
 *   @brief   Updates the active scene
 *   @details Calls updateScene() on scene that is currently active
 *   @param   delta_time is time since last update
 *   @return  1 if the scene has changed, 0 if it hasn't and -1 signals to exit
 */
int SceneManager::updateCurrentScene(double delta_time)
{
  switch (current_scene->update(delta_time))
  {
    // Scene -1 signifies no change
    case -1:
      return 0;
    case 0:
      swapScene(new Splashscreen);
      break;
    case 1:
      swapScene(new MainMenu);
      break;
    case 2:
      swapScene(new GameCore);
      break;
    // Anything else is unhandled, and we will signal to exit.
    default:
      return -1;
  }
  return 1;
}

/**
 *   @brief   Renders the active scene
 *   @details Calls renderScene() on scene that is currently active
 *   @param   renderer is a pointer to the renderer
 *   @param  delta_time is time since last update
 */
void SceneManager::renderCurrentScene(double delta_time)
{
  current_scene->render(delta_time);
}

// Swap the current scene
void SceneManager::swapScene(Scene* new_scene)
{
  delete current_scene;
  current_scene = new_scene;
}