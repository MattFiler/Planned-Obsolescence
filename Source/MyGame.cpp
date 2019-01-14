#include <iostream>

#include <Engine/DebugPrinter.h>
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Keys.h>
#include <Engine/Platform.h>
#include <Engine/Sprite.h>

#include "MyGame.h"

bool MyGame::init()
{
  game_name = "Planned Obsolescence";

  if (!initAPI())
  {
    return false;
  }

  toggleFPS();
  return true;
}

//Update
void MyGame::update(const ASGE::GameTime& game_time)
{
  return;
}

//Render
void MyGame::render(const ASGE::GameTime& game_time)
{
  return;
}
