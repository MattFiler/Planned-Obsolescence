#ifndef PLANNEDOBSOLESCENCE_TILEDATA_H
#define PLANNEDOBSOLESCENCE_TILEDATA_H

#include "../Constants.h"
#include "../FileHandler/FileHandler.h"
#include "../Sprites/ScaledSpriteArray.h"
#include <Engine/Renderer.h>
#include <Engine/Sprite.h>
#include <json.hpp>
#include <memory>
using json = nlohmann::json;

struct TileData
{
  // Load config data in
  void load(json* tile_global_config, const std::string& tile_type, ASGE::Renderer* renderer)
  {
    FileHandler file_handler;
    json tile_config = file_handler.loadConfigFromExisting(*tile_global_config, tile_type);

    // Size
    width = tile_config["width"];
    height = tile_config["height"];

    // Exit ability
    for (json::iterator tile_data = tile_config["available_exits"].begin();
         tile_data != tile_config["available_exits"].end();
         ++tile_data)
    {
      if (tile_data.key() == "left" && tile_data.value() == true)
      {
        setCanExit(direction::LEFT);
      }
      else if (tile_data.key() == "right" && tile_data.value() == true)
      {
        setCanExit(direction::RIGHT);
      }
      else if (tile_data.key() == "up" && tile_data.value() == true)
      {
        setCanExit(direction::UP);
      }
      else if (tile_data.key() == "down" && tile_data.value() == true)
      {
        setCanExit(direction::DOWN);
      }
    }

    // POIs
    if (tile_config["poi_door"] == true)
    {
      poi = point_of_interest::DOOR;
    }
    else if (tile_config["poi_computer"] == true)
    {
      poi = point_of_interest::COMPUTER;
    }

    // If we have a POI, get alt sprite and description
    if (poi != point_of_interest::NONE_ON_THIS_TILE)
    {
      // We start as a functional POI (not being used, not broken, not being fixed)
      state_of_poi = poi_state::POI_IS_FUNCTIONAL;

      // Set tile sprite
      ASGE::Sprite* tile_sprite = renderer->createRawSprite();
      tile_sprite->loadTexture(tile_config["poi_sprite"]);
      sprite = std::make_shared<ScaledSpriteArray>(1);
      sprite->addSprite(*tile_sprite);
      sprite->hide();

      // Assign repair sprites
      repair_sprites = std::make_shared<ScaledSpriteArray>(3);
      ASGE::Sprite* repair_sprite_1 = renderer->createRawSprite();
      repair_sprite_1->loadTexture("data/UI/IN_GAME_UI/POI_BROKEN.png");
      ASGE::Sprite* repair_sprite_2 = renderer->createRawSprite();
      repair_sprite_2->loadTexture("data/UI/IN_GAME_UI/POI_REPAIR_REQUESTED.png");
      ASGE::Sprite* repair_sprite_3 = renderer->createRawSprite();
      repair_sprite_3->loadTexture("data/UI/IN_GAME_UI/POI_REPAIRING.png");
      repair_sprites->addSprite(*repair_sprite_1);
      repair_sprites->addSprite(*repair_sprite_2);
      repair_sprites->addSprite(*repair_sprite_3);
      repair_sprites->hide();

      // Set dimensions
      sprite->setWidth(width);
      sprite->setHeight(height);

      // Set description
      poi_desc = tile_config["poi_desc"];
    }
  }

  // Update our tile position (and sprite if we have one)
  void updatePosition(float x, float y)
  {
    x_pos = x;
    y_pos = y;

    if (poi != point_of_interest::NONE_ON_THIS_TILE)
    {
      sprite->xPos(x_pos);
      sprite->yPos(y_pos);
      repair_sprites->xPos(x_pos);
      repair_sprites->yPos(y_pos);
    }
  }

  // Index
  int index_in_room = 0;
  int index_in_map = 0;

  // Position
  float x_pos = 0;
  float y_pos = 0;

  // Size
  float width = 0;
  float height = 0;

  // Traverse ability
  tile_accessibility traversal = tile_accessibility::TILE_IS_NON_TRAVERSABLE;

  // Exit Ability (call with enum exit_direction - left/right/up/down)
  bool exits[4] = { false, false, false, false };
  void setCanExit(direction exit_direction)
  {
    exits[exit_direction] = true;
    traversal = tile_accessibility::TILE_IS_TRAVERSABLE;
  }
  bool getCanExit(direction exit_direction) { return exits[exit_direction]; }

  // POI Data
  point_of_interest poi = point_of_interest::NONE_ON_THIS_TILE;
  poi_state state_of_poi = poi_state::UNINITIALISED_POI;
  std::string poi_desc = "";
  std::shared_ptr<ScaledSpriteArray> sprite;
  std::shared_ptr<ScaledSpriteArray> repair_sprites;
};

#endif // PLANNEDOBSOLESCENCE_TILEDATA_H
