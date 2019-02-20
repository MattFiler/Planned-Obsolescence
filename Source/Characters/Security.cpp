#include "Security.h"

void Security::setupPatrolRoute()
{
  std::vector<Room>* all_rooms = global_map->getRooms();
  patrol_route.reserve(4);

  // Top left
  patrol_route.push_back(getMiddleTilePosition(all_rooms->at(0)));
  // Top right
  patrol_route.push_back(getMiddleTilePosition(all_rooms->at(global_map->getRoomsX())));
  // Bottom left
  patrol_route.push_back(
    getMiddleTilePosition(all_rooms->at(global_map->getRoomCount() - global_map->getRoomsX() - 1)));
  // Bottom right
  patrol_route.push_back(getMiddleTilePosition(all_rooms->at(global_map->getRoomCount() - 1)));
}

Point Security::getMiddleTilePosition(Room& this_room)
{
  Tile& middle_tile = this_room.getTiles()->at(this_room.getTileCount() / 2);
  return Point(middle_tile.getPositionX(), middle_tile.getPositionY());
}

void Security::update(double delta_time)
{
    config.internal_gauge -= (gauge_rates ::SECURITY_RESET_RATE / static_cast<float>(delta_time));
    if(config.internal_gauge < 0)
    {
        config.internal_gauge = 0;
    }

  if (!updatePosition(delta_time))
  {
    patrol_index++;
    if (patrol_index > patrol_route.size() - 1)
    {
      patrol_index = 0;
    }
    calculateRouteToPoint(patrol_route[patrol_index]);
  }
}

void Security::lockedDoorFound()
{
  // Re-calculate the route
  current_route[route_index + 1]->pathable = false;
  registerRepairRequest(global_map->getTileAtPoint(current_route[route_index + 1]->position));
  calculateRouteToPoint(current_route[current_route.size() - 1]->position);
}