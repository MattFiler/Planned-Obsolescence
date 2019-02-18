#include "GameMap.h"

GameMap::GameMap()
{
  importJSON();
}

/* Import map JSON data */
void GameMap::importJSON()
{
  // -- CONFIGURED MAP CONFIG --
  std::string map_name = "TEST" + std::to_string((rand() % 5) + 1); // TODO: Vary this by number of
                                                                    // configs.
  map_config = file_handler.loadConfig("map_core.json", map_name);
  debug_text.print("LOADING MAP " + map_name);

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
  float room_x = 0.0f;
  float room_y = 0.0f;
  float map_width = 0.0f;
  float map_height = 0.0f;
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
      if (room_x > map_width)
      {
        map_width = room_x;
      }
      room_x = 0.0f;
      room_y += rooms[i].getHeight();
      map_height = room_y;
    }
    else
    {
      room_x += rooms[i].getWidth();
    }
  }
  map_width += rooms[rooms.size()-1].getWidth();

  // Set map sprite and resize
  ASGE::Sprite* map_sprite = renderer->createRawSprite();
  map_sprite->loadTexture(map_config["sprite"]);
  sprite = std::make_shared<ScaledSpriteArray>(1);
  sprite->addSprite(*map_sprite);
  sprite->setWidth(map_width);
  sprite->setHeight(map_height);

  debug_text.print("MAP FINISHED GENERATING WITH " + std::to_string(tile_count) + " TILES");
}

/* Render our map */
void GameMap::render(double delta_time)
{
  // Render map
  game_camera->renderSprite(sprite.get(), delta_time, render_index::MAP_LAYER);

  for (Room& room_to_render : rooms)
  {
    if (room_to_render.getPositionX() < (SCREEN_WIDTH * ScaledSpriteArray::width_scale) &&
        room_to_render.getPositionY() < (SCREEN_HEIGHT * ScaledSpriteArray::width_scale))
    {
      for (Tile& tile_to_render : room_to_render.getTiles())
      {
        if (tile_to_render.hasAnyPointOfInterest())
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
  return sprite;
}

/* Return all rooms in the current map */
std::vector<Room> GameMap::getRooms()
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