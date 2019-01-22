#include "GameMap.h"
using namespace std;

/* Load our map */
void GameMap::load(ASGE::Renderer* renderer_instance)
{
  // Save renderer location
  renderer = renderer_instance;

  // Load config
  string config_file = "map_core.json";
  map_config = file_handler.loadConfig(config_file, "EXAMPLE");
  // Using "EXAMPLE" map config for now, but later will expand this to be randomly selected.

  // Load all rooms into the map
  rooms = new Room[map_config["rooms"].size()];
  room_count = static_cast<int>(map_config["rooms"].size());
  for (int i = 0; i < room_count; i++)
  {
    Room new_room = Room(map_config["rooms"][i]);
    new_room.build(0, 0, renderer); // TODO: UPDATE POSITION
    rooms[i] = new_room;
  }
}

/* Render our map */
void GameMap::render()
{
  for (int i = 0; i < room_count; i++)
  {
    for (int x = 0; x < rooms[i].getTileCount(); x++)
    {
      Tile* tiles_to_render = rooms[i].getTiles();
      if (tiles_to_render[x].getSprite() != nullptr)
      {
        renderer->renderSprite(*tiles_to_render[x].getSprite());
      }
    }
  }
}

/* Return all rooms in the current map */
Room* GameMap::getRooms()
{
  return rooms;
}

/* Return the number of rooms in the current map */
int GameMap::getRoomCount()
{
  return room_count;
}