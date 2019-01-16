#ifndef HELLOASGE_MYGAME_H
#define HELLOASGE_MYGAME_H

#include "AnimatedSprite.h"
#include "SceneManager.h"
#include <Engine/OGLGame.h>

class MyGame : public ASGE::OGLGame
{
  public:
  ~MyGame();

  bool init() override;
  void update(const ASGE::GameTime& game_time) override;
  void render(const ASGE::GameTime& game_time) override;

  private:
  void keyHandler(const ASGE::SharedEventData data);
  void clickHandler(const ASGE::SharedEventData data);
  void setupResolution();

  int key_callback_id = -1;   /**< Key Input Callback ID. */
  int mouse_callback_id = -1; /**< Mouse Input Callback ID. */

  SceneManager* scene_manager = nullptr;
};

#endif // HELLOASGE_MYGAME_H
