#ifndef PO_MAP
#define PO_MAP

#include "../Core/DebugText.h"
#include "Room.h"
#include <Engine/Renderer.h>

class GameMap
{
 public:
  GameMap() = default;
  ~GameMap() = default;

  void load(ASGE::Renderer* renderer_instance, Camera* camera);
  void render();

  Room* getRooms();
  int getRoomCount();
  int getTileCount();

 private:
  json map_config;
  FileHandler file_handler;
  ASGE::Renderer* renderer = nullptr;
  DebugText debug_text;

  Room* rooms = nullptr;
  int room_count = 0;
  int tile_count = 0;
};

#endif