#include "Tile.h"
using namespace std;

/* Load our config on instantiation */
Tile::Tile(string tile_type, ASGE::Renderer* renderer)
{
  // Load tile config
  tile_data = file_handler.loadConfig("tiles_core.json", tile_type);

  // Set tile sprite if we've been given a renderer
  if (renderer != nullptr)
  {
    my_sprite = new DynamicSprite(1);
    ASGE::Sprite* new_sprite = renderer->createRawSprite();
    new_sprite->loadTexture(tile_data["sprite"]);
    my_sprite->addSprite(*new_sprite);
  }
}

/* Work out if we have the requested exit on this tile */
bool Tile::exitIsValid(room_exits exit)
{
  switch (exit)
  {
    case room_exits::LEFT:
    {
      return tile_data["available_exits"]["left"];
    }
    case room_exits::RIGHT:
    {
      return tile_data["available_exits"]["right"];
    }
    case room_exits::UP:
    {
      return tile_data["available_exits"]["up"];
    }
    case room_exits::DOWN:
    {
      return tile_data["available_exits"]["down"];
    }
    default:
    {
      return false;
    }
  }
}

/* Duplicate of exitIsValid */
bool Tile::entryIsValid(room_exits exit)
{
  return exitIsValid(exit);
}

/* Work out if we have a specified point of interest on this tile */
bool Tile::hasPointOfInterest(point_of_interest poi)
{
  switch (poi)
  {
    case point_of_interest::COMPUTER:
    {
      return tile_data["has_point_of_interest"]["computer"];
    }
    case point_of_interest::DOOR:
    {
      return tile_data["has_point_of_interest"]["door"];
    }
    default:
    {
      return false;
    }
  }
}

/* Return our sprite */
DynamicSprite* Tile::getSprite()
{
  return my_sprite;
}