#include "Security.h"

Security::~Security()
{
  delete game_map;
  game_map = nullptr;
}

void Security::setupPatrolRoute()
{
  std::vector<Room>* all_rooms = game_map->getRooms();
  patrol_route.reserve(4);

  // Top left
  patrol_route.push_back(getMiddleTilePosition(all_rooms->at(0)));
  // Top right
  patrol_route.push_back(getMiddleTilePosition(all_rooms->at(game_map->getRoomsX())));
  // Bottom left
  patrol_route.push_back(
    getMiddleTilePosition(all_rooms->at(game_map->getRoomCount() - game_map->getRoomsX() - 1)));
  // Bottom right
  patrol_route.push_back(getMiddleTilePosition(all_rooms->at(game_map->getRoomCount() - 1)));
}

Point Security::getMiddleTilePosition(Room& this_room)
{
  Tile& middle_tile = this_room.getTiles()->at(this_room.getTileCount() / 2);
  return Point(middle_tile.getPositionX(), middle_tile.getPositionY());
}