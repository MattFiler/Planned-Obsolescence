#include "Tile.h"
using namespace std;

/* Load our config on instantiation */
Tile::Tile(string tile_type)
{
  // Load tile config
  string config_file = "tiles_core.json";
  tile_data = file_handler.loadConfig(config_file, tile_type);
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

/* Configure our sprite and set position */
void Tile::configure(float x_pos, float y_pos, ASGE::Renderer* renderer)
{
  // Set tile sprite
  sprite = renderer->createRawSprite();
  sprite->loadTexture(tile_data["sprite"]);

  // Set position
  sprite->xPos(x_pos);
  sprite->yPos(y_pos);

  // Set dimensions
  sprite->width(getWidth());
  sprite->height(getHeight());
}

/* Return the X position of the tile */
float Tile::getPositionX()
{
  return sprite->xPos();
}

/* Get the Y position of the tile */
float Tile::getPositionY()
{
  return sprite->yPos();
}

/* Return our sprite */
ASGE::Sprite* Tile::getSprite()
{
  return sprite;
}

/* Get the width of the tile */
float Tile::getWidth()
{
  return tile_data["width"];
}

/* Get the height of the tile */
float Tile::getHeight()
{
  return tile_data["height"];
}