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

#ifdef NDEBUG
#  define IS_IN_DEBUG_MODE false
#else
#  define IS_IN_DEBUG_MODE true
#endif

PlannedObsolescence::~PlannedObsolescence()
{
  delete scene_manager;
  scene_manager = nullptr;

  sound_player.deinit();
}

bool PlannedObsolescence::init()
{
  // Load core configurations
  core_config = file_handler.loadConfig("game_core.json");

  // Remember debug toggle (exit if not set, config issue)
  if (core_config["debug_enabled"].is_null())
  {
    return false;
  }
  debug_text.enabled = (core_config["debug_enabled"] && IS_IN_DEBUG_MODE);

  // Set keybinds
  user_keybinds.setup(core_config["keybinds"]);

  // Configure resolution and game title
  setupResolution();
  game_name = "Planned Obsolescence";

  // Initialise the engine
  if (!initAPI())
  {
    return false;
  }

  // Display debug data if requested
  if (core_config["debug_enabled"] && IS_IN_DEBUG_MODE)
  {
    toggleFPS();
  }

  // Seed srand
  srand(static_cast<unsigned int>(time(NULL)));

  // Disable input threading
  inputs->use_threads = false;

  // Assign input callbacks
  key_callback_id = inputs->addCallbackFnc(ASGE::E_KEY, &PlannedObsolescence::keyHandler, this);
  mouse_callback_id =
    inputs->addCallbackFnc(ASGE::E_MOUSE_CLICK, &PlannedObsolescence::clickHandler, this);

  // Load font
  auto font_buffer = file_handler.openAsBuffer("UI/font.ttf");
  po_font = renderer->loadFontFromMem("VCR Mono",
                                      font_buffer.as_unsigned_char(),
                                      static_cast<unsigned int>(font_buffer.length),
                                      static_cast<int>(40 * ScaledSpriteArray::width_scale));

  // Generic background
  delete generic_background;
  generic_background = new ScaledSpriteArray(1);
  ASGE::Sprite* _sprite_bg = renderer->createRawSprite();
  _sprite_bg->loadTexture("data/UI/BACKGROUND.jpg");
  generic_background->addSprite(*_sprite_bg);

  // Configure localised strings to selected language
  localiser.configure(core_config["language"]);

  // Hide cursor
  inputs->setCursorMode(ASGE::MOUSE::CursorMode::HIDDEN);

  // Initialise the scene manager
  scene_manager = new SceneManager();

  // Initialise sound player and play background music
  sound_player.init();
  file_handler.loadSound(background_music, "IN_GAME_SOUNDTRACK", 1.0f, true);
  sound_player.play(background_music);

  // Start out on the splashscreen scene
  scene_manager->current_scene = new Splashscreen();
  return scene_manager->loadCurrentScene(renderer.get(), inputs.get(), sound_player);
}

/**
 *   @brief   Sets the game window resolution
 *   @details Sets the resolution for the game window, as well as the scale
 *            factor for AnimatedSprite
 *   @return  void
 */
void PlannedObsolescence::setupResolution()
{
  game_width = core_config["resolution"]["width"];
  game_height = core_config["resolution"]["height"];

  ScaledSpriteArray::width_scale = static_cast<float>(game_width) / SCREEN_WIDTH;
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
                                   Point(static_cast<float>(x_pos), static_cast<float>(y_pos)));
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
    if (!scene_manager->loadCurrentScene(renderer.get(), inputs.get(), sound_player))
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
  renderer->setFont(po_font);
  renderer->renderSprite(generic_background->returnNextSprite(game_time.delta_time.count()),
                         render_index::BASE_LAYER);
  scene_manager->renderCurrentScene(game_time.delta_time.count());
}