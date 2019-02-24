#include "Goon.h"
#include "../Managers/Gauges.h"

Goon::Goon() : Character(character_type::GOON)
{
  for (int i = 0; i < 10; i++)
  {
    productivity_average[i] = gauge_rates ::GOON_PRODUCTIVTIY;
  }
}

void Goon::update(double delta_time)
{
  speed_multiplier = 1 + ((100 - PO_Gauges::time_remaining) / 100);

  // If the Goon didn't move
  updateTimeBetweenFrames(static_cast<float>(config.movement_speed) * 10.0f / speed_multiplier);
  if (!updatePosition(delta_time))
  {
    updateTimeBetweenFrames(1000000);

    // Check if the POI is valid the first time only
    if (!at_valid_poi && point_of_interest_tile != nullptr &&
        point_of_interest_tile->getPointOfInterestState() == poi_state::POI_IS_FUNCTIONAL &&
        (poi_position == position))
    {
      // Setting to true also prevents the previous check on future update ticks
      at_valid_poi = true;
    }

    if (!at_valid_poi)
    {
      findNewPOI();
      time_elapsed_at_poi = 0;

      at_valid_poi = false;
      if (point_of_interest_tile != nullptr &&
          point_of_interest_tile->getPointOfInterestState() == poi_state::POI_IS_BROKEN)
      {
        registerRepairRequest(point_of_interest_tile);
      }
    }
    else
    {
      // If the allotted time is spent at the POI, find a new one
      time_elapsed_at_poi += delta_time;
      time_working += delta_time;

      if (time_elapsed_at_poi > total_time_for_poi ||
          point_of_interest_tile->getPointOfInterestState() == poi_state::POI_IS_BROKEN)
      {
        poi_iteration_count++;
        if (point_of_interest_tile->getPointOfInterestState() != poi_state::POI_IS_BROKEN)
        {
          point_of_interest_tile->setPointOfInterestState(poi_state::POI_IS_FUNCTIONAL);
        }
        findNewPOI();

        time_elapsed_at_poi = 0;
        at_valid_poi = false;
      }
      else
      {
        point_of_interest_tile->setPointOfInterestState(poi_state::POI_IS_BEING_USED_BY_GOON);
      }
    }
  }
  time_since_last_interval += delta_time;
  if (time_since_last_interval > gauge_rates::GOON_PRODUCTIVTIY)
  {
    time_since_last_interval = 0;
    productivity_average[average_index] = time_working;
    time_working = 0;

    average_index++;
    // Wrap the index around if gets to 10
    if (average_index == 10)
    {
      average_index = 0;
    }

    // Re-calculate the average
    double total = 0;
    for (int i = 0; i < 10; i++)
    {
      total += productivity_average[i];
    }
    config.internal_gauge =
      static_cast<float>((total / 10) / (gauge_rates::GOON_PRODUCTIVTIY / 100));
  }
}

/* Specific implementation for when a goon paths into a locked door */
void Goon::lockedDoorFound()
{
  // Re-calculate the route
  current_route[route_index + 1]->pathable = false;
  registerRepairRequest(global_map->getTileAtPoint(current_route[route_index + 1]->position));
  calculateRouteToPoint(current_route[current_route.size() - 1]->position);
}

/* Finds a new point of interest in the room, or in a random room if there are none */
void Goon::findNewPOI()
{
  // Generate a random time for the Goon to stay at this POI
  total_time_for_poi =
    gauge_rates ::GOON_MIN_TIME_AT_POI + (rand() % gauge_rates::GOON_MAX_TIME_AT_POI);

  // Find which room the goon is in
  Room* our_room = nullptr;
  for (Room& room : *global_map->getRooms())
  {
    if (our_room)
    {
      break;
    }

    for (Tile& tile : *room.getTiles())
    {
      if (tile.getPositionX() == position.x_pos && tile.getPositionY() == position.y_pos)
      {
        our_room = &room;
        break;
      }
    }
  }

  // Loop through and find all POI's
  std::vector<Tile*> all_pois;
  getAllPOIInRoom(&all_pois, our_room, false);

  // If there are any, then choose a random POI to go to
  if (!all_pois.empty() && poi_iteration_count < gauge_rates::GOON_MAX_ROOM_ITER)
  {
    auto random_index =
      static_cast<unsigned long long>((rand() % (static_cast<int>(all_pois.size()))));
    Point tile_point =
      Point(all_pois[random_index]->getPositionX(), all_pois[random_index]->getPositionY());

    point_of_interest_tile = all_pois[random_index];
    poi_position = findPositionForPOI(tile_point, our_room);
    calculateRouteToPoint(poi_position);
  }
  else
  {
    auto random_room = static_cast<unsigned long long int>(
      rand() & static_cast<int>((*global_map->getRooms()).size() - 1));
    our_room = &(*global_map->getRooms())[random_room];
    all_pois.clear();
    getAllPOIInRoom(&all_pois, our_room, true);

    auto random_index =
      static_cast<unsigned long long>((rand() % (static_cast<int>(all_pois.size()))));
    Point tile_point =
      Point(all_pois[random_index]->getPositionX(), all_pois[random_index]->getPositionY());
    point_of_interest_tile = all_pois[random_index];
    poi_position = findPositionForPOI(tile_point, our_room);
    calculateRouteToPoint(poi_position);
  }
}

/* Gets every point of interest in the given room and places it in the vector */
void Goon::getAllPOIInRoom(std::vector<Tile*>* all_poi, Room* room, bool ignore_functionality)
{
  for (Tile& tile : *room->getTiles())
  {
    if (tile.hasSpecificPointOfInterest(point_of_interest::COMPUTER))
    {
      // If Goon is leaving the room, then they don't know if the other rooms POIs are functional
      if (tile.getPointOfInterestState() == poi_state::POI_IS_FUNCTIONAL || ignore_functionality)
      {
        all_poi->push_back(&tile);
      }
      else if (tile.getPointOfInterestState() == poi_state::POI_IS_BROKEN)
      {
        registerRepairRequest(&tile);
      }
    }
  }
}
