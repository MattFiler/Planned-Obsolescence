#include "GameMap.h"

GameMap::GameMap()
{
  importJSON();
}

/* Import all map JSON data */
void GameMap::importJSON()
{
  // MAP CONFIG
  map_config = file_handler.openAsJSON("CONFIGS/map_core.json");

  // ROOM CONFIG
  room_config = file_handler.openAsJSON("CONFIGS/rooms_core.json");

  // TILE CONFIG
  tile_config = file_handler.openAsJSON("CONFIGS/tiles_core.json");
}

/* Load our map */
void GameMap::load(ASGE::Renderer* renderer_instance, Camera* camera)
{
  // Load map and its initial data
  map_data.load(map_config);

  // Save renderer/camera for use later
  renderer = renderer_instance;
  game_camera = camera;

  // Load all rooms into the map and work out map size
  float room_x = 0.0f;
  float room_y = 0.0f;
  for (int i = 0; i < map_data.room_count; i++)
  {
    if (i != 0)
    {
      map_data.tile_count += map_data.rooms[i - 1].getTileCount();
    }

    map_data.rooms.emplace_back(map_data.room_names[i], &room_config, &tile_config);
    map_data.rooms[i].build(room_x, room_y, renderer, map_data.tile_count);

    if ((i + 1) % map_data.rooms_x == 0)
    {
      if (room_x > map_data.map_width)
      {
        map_data.map_width = room_x;
      }
      room_x = 0.0f;
      room_y += map_data.rooms[i].getHeight();
      map_data.map_height = room_y;
    }
    else
    {
      room_x += map_data.rooms[i].getWidth();
    }
  }
  map_data.map_width += map_data.rooms[map_data.rooms.size() - 1].getWidth();

  // Load map sprite and resize it
  map_data.loadMapSprite(renderer);
  map_data.resizeMap();

  // Debug log now we're done
  debug_text.print("MAP FINISHED GENERATING WITH " + std::to_string(map_data.tile_count) +
                   " TILES");
}

/* Render our map */
void GameMap::render(double delta_time)
{
  // Render map
  game_camera->renderSprite(map_data.sprite.get(), delta_time, render_index::MAP_LAYER);

  for (Room& room_to_render : map_data.rooms)
  {
    if (room_to_render.getPositionX() < (SCREEN_WIDTH * ScaledSpriteArray::width_scale) &&
        room_to_render.getPositionY() < (SCREEN_HEIGHT * ScaledSpriteArray::width_scale))
    {
      for (Tile& tile_to_render : *room_to_render.getTiles())
      {
        if (tile_to_render.hasAnyPointOfInterest() && tile_to_render.getSprite()->isVisible())
        {
          // Render POI
          game_camera->renderSprite(
            tile_to_render.getSprite().get(), delta_time, render_index::TILE_LAYER);
        }
      }
    }
  }
}

/* Return our sprite */
std::shared_ptr<ScaledSpriteArray> GameMap::getSprite()
{
  return map_data.sprite;
}

/* Return all rooms in the current map */
std::vector<Room>* GameMap::getRooms()
{
  return &map_data.rooms;
}

/* Return the number of rooms in the current map */
int GameMap::getRoomCount()
{
  return map_data.room_count;
}

/* Return the number of tiles in the map */
int GameMap::getTileCount()
{
  return map_data.tile_count;
}

/* Checks to see if there is a tile at the passed position that is in the passed state */
bool GameMap::isPOIStateAtPoint(poi_state poi_state, Point point)
{
  for (Room& room : map_data.rooms)
  {
    for (Tile& tile : *room.getTiles())
    {
      if (tile.getPositionX() == point.x_pos && tile.getPositionY() == point.y_pos)
      {
        return (tile.getPointOfInterestState() == poi_state);
      }
    }
  }
  return false;
}

/* Check to see if we clicked a POI */
bool GameMap::clickedPointCheck(Point click, bool act_on_click)
{
  for (Room& room : map_data.rooms)
  {
    for (Tile& tile : *room.getTiles())
    {
      if (tile.hasAnyPointOfInterest())
      {
        if (tile.isPointOnTile(click))
        {
          if (act_on_click)
          {
            // do stuff
            ui_manager->updateAndShowPointInfo(tile.getTileDescription());
          }
          return true;
        }
      }
    }
  }
  return false;
}