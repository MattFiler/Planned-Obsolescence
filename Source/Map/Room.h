#ifndef PO_ROOM
#define PO_ROOM

#include "../ConfigParsers/RoomData.h"
#include "../Debug/DebugText.h"
#include "Tile.h"

class Room
{
 public:
  Room(std::string room_name, json* room_big_config, json* tile_big_config);
  ~Room() = default;

  void build(float room_x, float room_y, ASGE::Renderer* renderer, int tile_offset);

  std::vector<Tile>* getTiles();
  int getTileCount();

  float getHeight();
  float getWidth();

  float getPositionX();
  float getPositionY();

  int getTilesX() { return room_data.tiles_x; };
  int getTilesY() { return room_data.tiles_y; };

 private:
  // Configs
  json* tile_config;
  RoomData room_data;

  // Engine functionality
  FileHandler file_handler;
  DebugText debug_text;
};

#endif