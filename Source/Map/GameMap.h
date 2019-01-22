#ifndef PO_MAP
#define PO_MAP

#include "Room.h"
#include <Engine/Renderer.h>

class GameMap
{
 public:
  GameMap() = default;
  ~GameMap() = default;

  void load(ASGE::Renderer* renderer);
  void render(double delta_time, ASGE::Renderer* renderer);

 private:
  json map_config;
  FileHandler file_handler;
  Room* rooms = nullptr;
  int room_count = 0;
};

#endif