#include "Room.h"
using namespace std;

/* Load config and tiles on instantiation */
Room::Room(string room_name, json* room_big_config, json* tile_big_config)
{
  // Load configs
  room_config = file_handler.loadConfigFromExisting(*room_big_config, room_name);
  tile_config = tile_big_config;
}

/* Delete all tiles when we're destroyed */
Room::~Room()
{
  // delete[] tiles;
  // tiles = nullptr;
}

/* Build our room */
void Room::build(
  float room_x, float room_y, ASGE::Renderer* renderer, int tile_offset, Camera* camera)
{
  // Store position data
  base_x = room_x;
  base_y = room_y;

  // Load all tiles into room at the correct position
  tile_count = static_cast<int>(room_config["tiles"].size());
  tiles.reserve(static_cast<size_t>(tile_count));
  float tile_x = base_x;
  float tile_y = base_y;
  float y_modifier = 0.0f;
  for (int i = 0; i < tile_count; i++)
  {
    Tile new_tile = Tile(room_config["tiles"][i], tile_config);
    new_tile.configure(tile_x, tile_y, renderer, camera);
    new_tile.setIndexInRoom(i);
    new_tile.setIndexInMap(tile_offset + i);
    tiles.push_back(new_tile);

    if ((i + 1) % static_cast<int>(room_config["tile_w"]) == 0)
    {
      float new_room_w = tile_x - base_x + new_tile.getWidth();

      tile_x = base_x;
      tile_y += y_modifier;
      y_modifier = 0.0f;

      if (room_w < new_room_w)
      {
        room_w = new_room_w;
      }
      if (room_h < tile_y - base_y)
      {
        room_h = tile_y - base_y;
      }
    }
    else
    {
      tile_x += new_tile.getWidth();
      if (new_tile.getHeight() > y_modifier)
      {
        y_modifier = new_tile.getHeight();
      }
    }
  }
}

/* Return room width */
float Room::getWidth()
{
  return room_w;
}

/* Return room height */
float Room::getHeight()
{
  return room_h;
}

/* Return room position X */
float Room::getPositionX()
{
  return base_y;
}

/* Return room position Y */
float Room::getPositionY()
{
  return base_y;
}

/* Return all tiles in the room */
vector<Tile> Room::getTiles()
{
  return tiles;
}

/* Return the number of tiles in the room */
int Room::getTileCount()
{
  return tile_count;
}