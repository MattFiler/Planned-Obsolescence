#include "GameMap.h"
using namespace std;

GameMap::GameMap()
{
  importJSON();
}

/* Import map JSON data */
void GameMap::importJSON()
{
  // -- CONFIGURED MAP CONFIG --
  string map_name = "TEST" + to_string((rand() % 5) + 1); // TODO: Vary this by number of configs.
  map_config = file_handler.loadConfig("map_core.json", map_name);
  debug_text.print("LOADING MAP - " + map_name);

  // -- BASIC ROOM CONFIG --
  room_config = file_handler.openAsJSON("CONFIGS/rooms_core.json");

  // -- BASIC TILE CONFIG --
  tile_config = file_handler.openAsJSON("CONFIGS/tiles_core.json");
}

/* Load our map */
void GameMap::load(ASGE::Renderer* renderer_instance, Camera* camera)
{
  // Save renderer location
  renderer = renderer_instance;
  game_camera = camera;

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

    rooms.emplace_back(map_config["rooms"][i], &room_config, &tile_config);
    rooms[i].build(room_x, room_y, renderer, tile_count);

    if ((i + 1) % static_cast<int>(map_config["rooms_w"]) == 0)
    {
      room_x = 0.0f; // TODO: Update base position
      room_y += rooms[i].getHeight();
    }
    else
    {
      room_x += rooms[i].getWidth();
    }
  }

  debug_text.print("MAP FINISHED GENERATING WITH TILE COUNT - " + to_string(tile_count));
}

/* Render our map */
void GameMap::render(double delta_time)
{
  for (Room& room_to_render : rooms)
  {
    if (room_to_render.getPositionX() < (SCREEN_WIDTH * dynamic_sprite.width_scale) &&
        room_to_render.getPositionY() < (SCREEN_HEIGHT * dynamic_sprite.width_scale))
    {
      // Render room
      game_camera->renderSprite(
        room_to_render.getSprite().get(), delta_time, render_index::ROOM_LAYER);

      // Check for any POIs to render
      for (Tile& tile_to_render : room_to_render.getTiles())
      {
        if (tile_to_render.hasAnyPointOfInterest())
        {
          game_camera->renderSprite(
            tile_to_render.getSprite().get(), delta_time, render_index::SPECIAL_TILE_LAYER);
        }
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