#include "Room.h"
using namespace std;

/* Load config and tiles on instantiation */
Room::Room(string room_name, ASGE::Renderer* renderer)
{
  // Load config
  string config_file = "rooms_core.json";
  room_config = file_handler.loadConfig(config_file, room_name);

  // Load all tiles into room
  tiles = new Tile[room_config["tiles"].size()];
  tile_count = static_cast<int>(room_config["tiles"].size());
  for (int i = 0; i < tile_count; i++)
  {
    Tile new_tile = Tile(room_config["tiles"][i], renderer);
    tiles[i] = new_tile;
  }
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