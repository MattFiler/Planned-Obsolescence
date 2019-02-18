#ifndef PLANNEDOBSOLESCENCE_ROOMDATA_H
#define PLANNEDOBSOLESCENCE_ROOMDATA_H

#include "../Map/Tile.h"
#include <vector>

struct RoomData
{
  // Load config data in
  void load(json* room_global_config, const std::string& room_name)
  {
    FileHandler file_handler;
    json room_config = file_handler.loadConfigFromExisting(*room_global_config, room_name);

    // Room tile dimensions
    tiles_x = room_config["tile_w"];
    tiles_y = room_config["tile_h"];

    // Get tile count and reserve space to load in
    tile_count = static_cast<int>(room_config["tiles"].size());
    tiles.reserve(static_cast<size_t>(tile_count));
    tile_names.reserve(static_cast<size_t>(tile_count));

    // Tile names
    for (int i = 0; i < tile_count; i++)
    {
      tile_names.push_back(room_config["tiles"][i]);
    }
  }

  // Update our room's position
  void updatePosition(float x, float y)
  {
    x_pos = x;
    y_pos = y;
  }

  // Tiles in room
  std::vector<Tile> tiles;
  std::vector<std::string> tile_names;
  int tile_count = 0;

  // Tiles per width/height
  int tiles_x = 0;
  int tiles_y = 0;

  // Positions
  float x_pos = 0.0f;
  float y_pos = 0.0f;

  // Sizes
  float height = 0.0f;
  float width = 0.0f;
};

#endif // PLANNEDOBSOLESCENCE_ROOMDATA_H
