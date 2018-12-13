//
// Created by Huxy on 03/10/2018.
//

#ifndef HELLOASGE_MYGAME_H
#define HELLOASGE_MYGAME_H

#include <Engine/OGLGame.h>

class MyGame : public ASGE::OGLGame
{
  public:
  ~MyGame() override = default;

  bool init() override;
  void update(const ASGE::GameTime& game_time) override;
  void render(const ASGE::GameTime& game_time) override;
};

#endif // HELLOASGE_MYGAME_H
