#include "GameMap.h"
using namespace std;

GameMap::GameMap()
{
  importJSON();
  
  // Save renderer location
  renderer = renderer_instance;
  game_camera = camera;
}

/* Delete all rooms when we're destroyed */
GameMap::~GameMap()
{
  // delete[] rooms;
  // rooms = nullptr;
}

/* Import map JSON data */
void GameMap::importJSON()
{
  // -- CONFIGURED MAP CONFIG --
  string config_file = "map_core.json";
  string map_name = "TEST" + to_string((rand() % 5) + 1); // TODO: Vary this by number of configs.
  map_config = file_handler.loadConfig(config_file, map_name);
  string debug_string = "LOADING MAP " + map_name;
  debug_text.print(debug_string);

  // -- BASIC ROOM CONFIG --
  config_file = "CONFIGS/rooms_core.json";
  room_config = file_handler.openAsJSON(config_file);
  string dfsdfds = to_string(room_config.size());
  debug_text.print(dfsdfds);

  // -- BASIC TILE CONFIG --
  config_file = "CONFIGS/tiles_core.json";
  tile_config = file_handler.openAsJSON(config_file);
}

/* Load our map */
void GameMap::load(ASGE::Renderer* renderer_instance, Camera* camera)
{
  // Save renderer location
  renderer = renderer_instance;

  // Load all rooms into the map
  room_count = static_cast<int>(map_config["rooms"].size());
  rooms.reserve(static_cast<size_t>(room_count));
  float room_x = 0.0f; // TODO: Update base position
  float room_y = 0.0f; // TODO: Update base position
  for (int i = 0; i < room_count; i++)
  {
    if (i != 0)
    {
      tile_count += rooms[i - 1].getTileCount();
    }

    Room new_room = Room(map_config["rooms"][i], &room_config, &tile_config);
    new_room.build(room_x, room_y, renderer, tile_count);
    rooms.push_back(new_room);

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

  std::string debug_string = "MAP FINISHED GENERATING WITH " + to_string(tile_count) + " TILES";
  debug_text.print(debug_string);
}

/* Render our map */
void GameMap::render(double delta_time)
{
  for (int i = 0; i < room_count; i++)
  {
    for (int x = 0; x < rooms[i].getTileCount(); x++)
    {
      vector<Tile> tiles_to_render = rooms[i].getTiles();
      if (tiles_to_render[x].getSprite() != nullptr)
      {
        game_camera->renderSprite(tiles_to_render[x].getSprite(), delta_time);
      }
    }
  }
}

/* Return all rooms in the current map */
vector<Room> GameMap::getRooms()
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