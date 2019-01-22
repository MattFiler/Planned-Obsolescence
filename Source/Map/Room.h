#ifndef PO_ROOM
#define PO_ROOM

#include "Tile.h"

class Room
{
 public:
  Room(std::string room_name = "DEFAULT");
  ~Room() = default;

  Room(const Room&) = delete;

  void build(float room_x, float room_y, ASGE::Renderer* renderer);

  Tile* getTiles();
  int getTileCount();

  float getHeight();
  float getWidth();

  float getPositionX();
  float getPositionY();

 private:
  Tile* tiles = nullptr;
  int tile_count = 0;

  json room_config;
  FileHandler file_handler;

  float base_x = 0.0f;
  float base_y = 0.0f;
  float room_h = 0.0f;
  float room_w = 0.0f;
};

#endif