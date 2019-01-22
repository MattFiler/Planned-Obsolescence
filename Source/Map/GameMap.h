#ifndef PO_MAP
#define PO_MAP

#include "Room.h"
#include <Engine/Renderer.h>

class GameMap
{
 public:
  GameMap() = default;
  ~GameMap() = default;

  void load(ASGE::Renderer* renderer_instance);
  void render();

  Room* getRooms();
  int getRoomCount();

 private:
  json map_config;
  FileHandler file_handler;
  Room* rooms = nullptr;
  int room_count = 0;
  ASGE::Renderer* renderer;
};

#endif