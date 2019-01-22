#include "Tile.h"
using namespace std;

Tile::Tile(string tile_type)
{
  tile_data = file_handler.loadConfig("tiles_core.json", tile_type);
}

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