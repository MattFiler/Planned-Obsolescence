#ifndef PO_MAP
#define PO_MAP

#include "../Core/DebugText.h"
#include "Room.h"
#include <Engine/Renderer.h>

class GameMap
{
 public:
  GameMap();
  ~GameMap() = default;

  void load(ASGE::Renderer* renderer_instance, Camera* camera);
  void render(double delta_time);

  std::vector<Room> getRooms();
  int getRoomCount();
  int getTileCount();

 private:
  void importJSON();

  // JSON configs
  json map_config;
  json room_config;
  json tile_config;

  // Engine features
  FileHandler file_handler;
  DebugText debug_text;
  Camera* game_camera = nullptr;
  ASGE::Renderer* renderer = nullptr;

  // Map data
  std::vector<Room> rooms;
  int room_count = 0;
  int tile_count = 0;
};

#endif