#ifndef PO_ROOM
#define PO_ROOM

#include "Tile.h"

class Room
{
 public:
  Room(std::string room_name = "DEFAULT", ASGE::Renderer* renderer = nullptr);
  ~Room() = default;

  Tile* getTiles();
  int getTileCount();

 private:
  Tile* tiles = nullptr;
  int tile_count = 0;

  json room_config;
  FileHandler file_handler;
};

#endif