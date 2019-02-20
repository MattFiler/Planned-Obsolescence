#include "LabTechnician.h"

void LabTechnician::update(double delta_time)
{
  if (repairing)
  {
    time_elapsed += delta_time;
    broken_pois.front()->setPointOfInterestState(poi_state::POI_IS_BEING_FIXED);
    if (time_elapsed > repair_time)
    {
      time_elapsed = 0;
      repairing = false;
      broken_pois.front()->setPointOfInterestState(poi_state::POI_IS_FUNCTIONAL);
      broken_pois.pop_front();
    }
  }
  else if (!updatePosition(delta_time))
  {

    if (broken_pois.empty())
    {
      calculateRouteToPoint(idle_position);
    }
    // If after pathing has stopped, we are next to the broken POI at the front of the queue
    else if(Point::distanceBetween(Point(broken_pois.front()->getPositionX(), broken_pois.front()->getPositionY()), position) < 100)
    {
      repairing = true;
    }
    else
    {
      calculateRouteToPoint(findPositionForPOI(Point(broken_pois.front()->getPositionX(), broken_pois.front()->getPositionY())));
    }
  }
}

void LabTechnician::lockedDoorFound()
{
  // Add fixing this door to the front of the queue
  broken_pois.push_front(global_map->getTileAtPoint(current_route[route_index + 1]->position));
  repairing = true;
}