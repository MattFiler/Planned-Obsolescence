#include "Goon.h"

Goon::Goon() : Character(character_type::GOON)
{
    for(int i = 0; i < 20; i++)
    {
        productivity_average[i] = 10000;
    }
}

void Goon::update(double delta_time)
{
  // If the Goon didn't move
  if (!updatePosition(delta_time))
  {
    // If there is no current PoI, or it's broken, or the current destination was never reached find
    // a new one
    if (point_of_interest_tile == nullptr ||
        point_of_interest_tile->getPointOfInterestState() == poi_state::POI_IS_BROKEN ||
        !(poi_position == position))
    {
      findNewPOI();
      time_elapsed_at_poi = 0;
    }
    else
    {
      // If the allotted time is spent at the POI, find a new one
      time_elapsed_at_poi += delta_time;
      time_working += delta_time;
      if (time_elapsed_at_poi > total_time_for_poi)
      {
        findNewPOI();
        time_elapsed_at_poi = 0;
      }
    }
  }
  time_since_last_interval += delta_time;
  if (time_since_last_interval > productivity_interval)
  {
    time_since_last_interval = 0;
    productivity_average[average_index] = time_working;
    time_working = 0;
    average_index++;
    // Wrap the index around if gets to 20
    if (average_index == 20)
    {
      average_index = 0;
    }
    // Re-calculate the average
    double total = 0;
    for (int i = 0; i < 20; i++)
    {
      total += productivity_average[i];
    }
    config.internal_gauge = static_cast<float>((total / 20) / (productivity_interval/100));
  }
}

/* Finds a new point of interest in the room, or in a random room if there are none */
void Goon::findNewPOI()
{
  // Generate a random time for the Goon to stay at this POI
  total_time_for_poi = rand() % 20000;
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

  // If no room was found, pick a random one
  bool leaving_room = false;
  if (!our_room)
  {
    // Flag that Goon is going to a new room
    leaving_room = true;
    auto random_room = static_cast<unsigned long long int>(
      rand() & static_cast<int>((*global_map->getRooms()).size()));
    our_room = &(*global_map->getRooms())[random_room];
  }

  // Loop through and find all POI's
  std::vector<Tile*> all_pois;
  for (Tile& tile : *our_room->getTiles())
  {
    if (tile.hasSpecificPointOfInterest(point_of_interest::COMPUTER))
    {
      // If Goon is leaving the room, then they don't know if the other rooms POIs are functional
      if (leaving_room || tile.getPointOfInterestState() == poi_state::POI_IS_FUNCTIONAL)
      {
        all_pois.push_back(&tile);
      }
    }
  }
  // If there are any, then choose a random POI to go to
  if (!all_pois.empty())
  {
    auto random_index =
      static_cast<unsigned long long>((rand() % (static_cast<int>(all_pois.size()))));
    Point tile_point =
      Point(all_pois[random_index]->getPositionX(), all_pois[random_index]->getPositionY());
    point_of_interest_tile = all_pois[random_index];
    findPositionForPOI(tile_point, our_room);
    calculateRouteToPoint(poi_position);
  }
  else
  {
    point_of_interest_tile = nullptr;
  }
}

/* Finds the position to stand on to access the point of interest */
void Goon::findPositionForPOI(Point point, Room* room)
{
  float tile_size = (*room->getTiles())[0].getWidth();

  for (Tile& tile : *room->getTiles())
  {
    if (tile.getTileAccessibility() == tile_accessibility::TILE_IS_TRAVERSABLE)
    {
      // Check to see if this tile matches the position of up, down, left or right of the POI
      if ((tile.getPositionX() == point.x_pos && tile.getPositionY() == point.y_pos - tile_size) ||
          (tile.getPositionX() == point.x_pos && tile.getPositionY() == point.y_pos + tile_size) ||
          (tile.getPositionX() == point.x_pos + tile_size && tile.getPositionY() == point.y_pos) ||
          (tile.getPositionX() == point.x_pos - tile_size && tile.getPositionY() == point.y_pos))
      {
        poi_position = Point(tile.getPositionX(), tile.getPositionY());
      }
    }
  }
}