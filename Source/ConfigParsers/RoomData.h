#ifndef PLANNEDOBSOLESCENCE_ROOMDATA_H
#define PLANNEDOBSOLESCENCE_ROOMDATA_H

#include "../Map/Tile.h"
#include "../Sprites/ScaledSpriteArray.h"
#include <Engine/Renderer.h>
#include <vector>

struct RoomData
{
  // Load config data in
  void load(json* room_global_config, const std::string& room_name)
  {
    FileHandler file_handler;
    json room_config = file_handler.loadConfigFromExisting(*room_global_config, room_name);

    // Path to sprite
    sprite_path = room_config["sprite"];

    // Room tile dimensions
    tile_w = room_config["tile_w"];
    tile_h = room_config["tile_h"];

    // Get tile count and reserve space to load in
    tile_count = static_cast<int>(room_config["tiles"].size());
    tiles.reserve(static_cast<size_t>(tile_count));
    tile_names.reserve(static_cast<size_t>(tile_count));

    // Tile names
    for (int i = 0; i < tile_count; i++)
    {
      tile_names.push_back(room_config["tiles"][i]);
    }
  }

  // Load sprite in
  void loadSprite(ASGE::Renderer* renderer)
  {
    // Set room sprite
    ASGE::Sprite* new_sprite = renderer->createRawSprite();
    new_sprite->loadTexture(sprite_path);
    sprite = std::make_shared<ScaledSpriteArray>(1);
    sprite->addSprite(*new_sprite);
  }

  // Refresh sprite size
  void refreshSpriteSize()
  {
    sprite->setWidth(room_w);
    sprite->setHeight(room_h);
  }

  // Update our room's position
  void updatePosition(float x, float y)
  {
    base_x = x;
    base_y = y;
    sprite->xPos(base_x);
    sprite->yPos(base_y);
  }

  // Tiles in room
  std::vector<Tile> tiles;
  std::vector<std::string> tile_names;
  int tile_count = 0;

  // Room tile dimensions
  int tile_w = 0;
  int tile_h = 0;

  // Room sprite
  std::string sprite_path = "";
  std::shared_ptr<ScaledSpriteArray> sprite = nullptr;

  // Positions
  float base_x = 0.0f;
  float base_y = 0.0f;
  float room_h = 0.0f;
  float room_w = 0.0f;
};

#endif // PLANNEDOBSOLESCENCE_ROOMDATA_H
