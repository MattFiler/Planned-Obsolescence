#ifndef PO_MAP
#define PO_MAP

#include "../Core/DebugText.h"
#include "Room.h"
#include <Engine/Renderer.h>

class GameMap
{
 public:
  GameMap();
  ~GameMap();

  void load(ASGE::Renderer* renderer_instance, Camera* camera);
  void render();

  std::vector<Room> getRooms();
  int getRoomCount();
  int getTileCount();

 private:
  void importJSON();

  // JSON Configs
  json map_config;
  json room_config;
  json tile_config;

  // Engine Scripts
  FileHandler file_handler;
  DebugText debug_text;

  // Engine Functions
  ASGE::Renderer* renderer = nullptr;

  // Map Data
  std::vector<Room> rooms;
  int room_count = 0;
  int tile_count = 0;
};

#endif