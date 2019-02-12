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
bool Tile::exitIsValid(direction exit)
{
  switch (exit)
  {
    case direction::LEFT:
    {
      return tile_data["available_exits"]["left"];
    }
    case direction::RIGHT:
    {
      return tile_data["available_exits"]["right"];
    }
    case direction::UP:
    {
      return tile_data["available_exits"]["up"];
    }
    case direction::DOWN:
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
bool Tile::entryIsValid(direction exit)
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
void Tile::configure(float x_position, float y_position, ASGE::Renderer* renderer)
{
  x_pos = x_position;
  y_pos = y_position;
  // Set tile sprite
  ASGE::Sprite* new_sprite = renderer->createRawSprite();
  new_sprite->loadTexture(tile_data["sprite"]);

  sprite = new DynamicSprite(1);
  sprite->addSprite(*new_sprite);

  // Set position
  sprite->xPos(x_position);
  sprite->yPos(y_position);

  // Set dimensions // Commented out for now as DynamicSprite doesn't can't alter w/h
  // sprite->width(getWidth());
  // sprite->height(getHeight());
}

/* Return the X position of the tile */
float Tile::getPositionX()
{
  return x_pos;
}

/* Get the Y position of the tile */
float Tile::getPositionY()
{
  return y_pos;
}

/* Return our sprite */
DynamicSprite* Tile::getSprite()
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

/* Set tile index in its room */
void Tile::setIndexInRoom(int index)
{
  tile_index_in_room = index;
}

/* Set tile index in the whole map */
void Tile::setIndexInMap(int index)
{
  tile_index_in_map = index;
}

/* Get tile index in its room */
int Tile::getIndexInRoom()
{
  return tile_index_in_room;
}

/* Get tile index in the whole map */
int Tile::getIndexInMap()
{
  return tile_index_in_map;
}