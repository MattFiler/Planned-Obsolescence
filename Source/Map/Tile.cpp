#include "Tile.h"
using namespace std;

/* Load our config on instantiation */
Tile::Tile(string tile_type)
{
  tile_data = file_handler.loadConfig("tiles_core.json", tile_type);
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
  exitIsValid(exit);
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