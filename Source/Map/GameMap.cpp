#include "GameMap.h"

/* Load our map */
void GameMap::load(ASGE::Renderer* renderer)
{
  // Load config
  map_config = file_handler.loadConfig("map_core.json", "EXAMPLE");
  // Using "EXAMPLE" map config for now, but later will expand this to be randomly selected.

  // Load all rooms into the map
  rooms = new Room[map_config["rooms"].size()];
  room_count = static_cast<int>(map_config["rooms"].size());
  for (int i = 0; i < room_count; i++)
  {
    Room new_room = Room(map_config["rooms"][i], renderer);
    rooms[i] = new_room;
  }
}

/* Render our map */
void GameMap::render(double delta_time, ASGE::Renderer* renderer)
{
  for (int i = 0; i < room_count; i++)
  {
    for (int x = 0; x < rooms[i].getTileCount(); i++)
    {
      Tile* tiles_to_render = rooms[i].getTiles();
      if (tiles_to_render[i].getSprite() != nullptr)
      {
        renderer->renderSprite(tiles_to_render[i].getSprite()->returnNextSprite(delta_time));
      }
    }
  }
}