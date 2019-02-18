#ifndef PO_MAP
#define PO_MAP

#include "../ConfigParsers/MapData.h"
#include "../Constants.h"
#include "../Debug/DebugText.h"
#include "../Sprites/ScaledSpriteArray.h"
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
  std::shared_ptr<ScaledSpriteArray> getSprite();

 private:
  void importJSON();

  // JSON configs
  json map_config;
  json room_config;
  json tile_config;

  // Map data
  MapData map_data;

  // Engine features
  FileHandler file_handler;
  DebugText debug_text;
  Camera* game_camera = nullptr;
  ASGE::Renderer* renderer = nullptr;
};

#endif