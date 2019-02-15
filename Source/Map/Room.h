#ifndef PO_ROOM
#define PO_ROOM

#include "../Debug/DebugText.h"
#include "Tile.h"

class Room
{
 public:
  Room(std::string room_name, json* room_big_config, json* tile_big_config);
  ~Room() = default;

  void build(float room_x, float room_y, ASGE::Renderer* renderer, int tile_offset);

  std::vector<Tile> getTiles();
  int getTileCount();

  float getHeight();
  float getWidth();

  std::shared_ptr<ScaledSpriteArray> getSprite();

  float getPositionX();
  float getPositionY();

 private:
  // Tiles in room
  std::vector<Tile> tiles;
  int tile_count = 0;

  // Configs (to be refactored)
  json room_config;
  json* tile_config;

  // Engine functionality
  FileHandler file_handler;
  DebugText debug_text;

  // Room sprite
  std::shared_ptr<ScaledSpriteArray> sprite = nullptr;

  // Positions
  float base_x = 0.0f;
  float base_y = 0.0f;
  float room_h = 0.0f;
  float room_w = 0.0f;
};

#endif