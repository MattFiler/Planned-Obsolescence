#ifndef PLANNEDOBSOLESCENCE_MAPDATA_H
#define PLANNEDOBSOLESCENCE_MAPDATA_H

#include "../Map/Room.h"
#include "../Sprites/ScaledSpriteArray.h"
#include <Engine/Renderer.h>
#include <vector>

struct MapData
{
  // Load config data in
  void load(json& passed_map_config)
  {
    // Select a map set
    for (json::iterator maps = passed_map_config.begin(); maps != passed_map_config.end(); ++maps)
    {
      available_roomsets.push_back(maps.key());
    }
    std::string map_name = available_roomsets[static_cast<size_t>(
      rand() % static_cast<int>(available_roomsets.size()) + 1)];

    // Debug log our map name
    DebugText debug_text;
    debug_text.print("LOADING MAP " + map_name);

    // Load correct config
    FileHandler file_handler;
    json map_config = file_handler.loadConfigFromExisting(passed_map_config, map_name);

    // Path to sprite
    sprite_path = map_config["sprite"];

    // Get room count and reserve space
    room_count = static_cast<int>(map_config["rooms"].size());
    rooms.reserve(static_cast<size_t>(room_count));
    room_names.reserve(static_cast<size_t>(room_count));

    // Map room dimensions
    rooms_x = map_config["rooms_w"];
    rooms_y = map_config["rooms_h"];

    // Room names
    for (int i = 0; i < room_count; i++)
    {
      room_names.push_back(map_config["rooms"][i]);
    }
  }

  // Set map sprite
  void loadMapSprite(ASGE::Renderer* renderer)
  {
    ASGE::Sprite* map_sprite = renderer->createRawSprite();
    map_sprite->loadTexture(sprite_path);
    sprite = std::make_shared<ScaledSpriteArray>(1);
    sprite->addSprite(*map_sprite);
  }

  // Resize map sprite
  void resizeMap(float width = 0, float height = 0)
  {
    if (width != 0 && height != 0)
    {
      map_width = width;
      map_height = height;
    }
    sprite->setWidth(map_width);
    sprite->setHeight(map_height);
  }

  // Map sprite
  std::shared_ptr<ScaledSpriteArray> sprite = nullptr;
  std::string sprite_path = "";

  // Rooms in map
  std::vector<Room> rooms;
  std::vector<std::string> room_names;

  // Map element counts
  int room_count = 0;
  int tile_count = 0;

  // Map room dimensions
  int rooms_x = 0;
  int rooms_y = 0;

  // Map size
  float map_width = 0.0f;
  float map_height = 0.0f;

 private:
  std::vector<std::string> available_roomsets;
};

#endif // PLANNEDOBSOLESCENCE_MAPDATA_H
