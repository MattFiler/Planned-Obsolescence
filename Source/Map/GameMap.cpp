#include "GameMap.h"
using namespace std;

/* Load our map */
void GameMap::load(ASGE::Renderer* renderer_instance, Camera* camera)
{
  // Save renderer location
  renderer = renderer_instance;
  game_camera = camera;

  // Load config
  string config_file = "map_core.json";
  string map_name = "TEST" + to_string((rand() % 5) + 1); // TODO: Vary this by number of configs.
  map_config = file_handler.loadConfig(config_file, map_name);

  string debug_string = "LOADING MAP " + map_name;
  debug_text.print(debug_string);

  // Load all rooms into the map
  rooms = new Room[map_config["rooms"].size()];
  room_count = static_cast<int>(map_config["rooms"].size());
  float room_x = 0.0f; // TODO: Update base position
  float room_y = 0.0f; // TODO: Update base position
  for (int i = 0; i < room_count; i++)
  {
    if (i != 0)
    {
      tile_count += rooms[i - 1].getTileCount();
    }

    Room new_room = Room(map_config["rooms"][i]);
    new_room.build(room_x, room_y, renderer, tile_count);
    rooms[i] = new_room;

    if ((i + 1) % static_cast<int>(map_config["rooms_w"]) == 0)
    {
      room_x = 0.0f; // TODO: Update base position
      room_y += new_room.getHeight();
    }
    else
    {
      room_x += new_room.getWidth();
    }
  }

  debug_string = "MAP FINISHED GENERATING WITH " + to_string(tile_count) + " TILES";
  debug_text.print(debug_string);
}

/* Render our map */
void GameMap::render(double delta_time)
{
  for (int i = 0; i < room_count; i++)
  {
    for (int x = 0; x < rooms[i].getTileCount(); x++)
    {
      Tile* tiles_to_render = rooms[i].getTiles();
      if (tiles_to_render[x].getSprite() != nullptr)
      {
         game_camera->renderSprite(tiles_to_render[x].getSprite(), delta_time);
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

/* Return the number of tiles in the map */
int GameMap::getTileCount()
{
  return tile_count;
}