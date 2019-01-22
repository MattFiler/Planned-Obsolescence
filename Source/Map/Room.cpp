#include "Room.h"
using namespace std;

/* Load config and tiles on instantiation */
Room::Room(string room_name)
{
  // Load config
  string config_file = "rooms_core.json";
  room_config = file_handler.loadConfig(config_file, room_name);
}

/* Build our room */
void Room::build(float room_x, float room_y, ASGE::Renderer* renderer)
{
  // Store position data
  base_x = room_x;
  base_y = room_y;

  // Load all tiles into room at the correct position
  tiles = new Tile[room_config["tiles"].size()];
  tile_count = static_cast<int>(room_config["tiles"].size());
  float tile_x = base_x;
  float tile_y = base_y;
  for (int i = 0; i < tile_count; i++)
  {
    Tile new_tile = Tile(room_config["tiles"][i]);
    new_tile.configure(tile_x, tile_y, renderer);
    tiles[i] = new_tile;

    if ((i + 1) % static_cast<int>(room_config["tile_w"]) == 0)
    {
      tile_x = base_x;
      tile_y += new_tile.getHeight();
    }
    else
    {
      tile_x += new_tile.getWidth();
    }
  }

  // Store size data
  room_w = tile_x;
  room_h = tile_y;
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
Tile* Room::getTiles()
{
  return tiles;
}

/* Return the number of tiles in the room */
int Room::getTileCount()
{
  return tile_count;
}