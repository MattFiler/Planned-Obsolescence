#include "LabTechnician.h"

void LabTechnician::update(double delta_time)
{
  float multiplier =
          1 + (gauge_rates ::TECHIE_STRESS_QUEUE_MULTIPLIER * static_cast<float>(broken_pois.size()));
  if (position == idle_position)
  {
    // Decay stress while at idle position
    config.internal_gauge -=
      gauge_rates ::TECHIE_STRESS_RELEIF * (static_cast<float>(delta_time) / 1000);
    if (config.internal_gauge < 0)
    {
      config.internal_gauge = 0;
    }
  }
  else
  {
    config.internal_gauge +=
      ((static_cast<float>(gauge_rates ::TECHIE_STRESS_GAIN)/5) * multiplier) * (static_cast<float>(delta_time) / 1000);
    if (config.internal_gauge > 100)
    {
      config.internal_gauge = 100;
    }
  }
  if (repairing)
  {
      config.internal_gauge +=
              ((static_cast<float>(gauge_rates ::TECHIE_STRESS_GAIN)/5) * multiplier) * (static_cast<float>(delta_time) / 1000);
    time_elapsed += delta_time;
    broken_pois.front()->setPointOfInterestState(poi_state::POI_IS_BEING_FIXED);
    auto adjusted_time = static_cast<float>(gauge_rates::TECHIE_REPAIR_TIME);
    adjusted_time *= 1 + ((config.internal_gauge / 100) * gauge_rates::TECHIE_STRESS_SLOW);
    if (time_elapsed > adjusted_time)
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
    else if (Point::distanceBetween(
               Point(broken_pois.front()->getPositionX(), broken_pois.front()->getPositionY()),
               position) < 100)
    {
      if(broken_pois.front()->getPointOfInterestState() == poi_state::POI_IS_BROKEN || broken_pois.front()->getPointOfInterestState() == poi_state::POI_REPAIR_PENDING)
      {
        repairing = true;
      }
      else
      {
        broken_pois.pop_front();
      }
    }
    else
    {
        calculateRouteToPoint(findPositionForPOI(
                Point(broken_pois.front()->getPositionX(), broken_pois.front()->getPositionY())));
    }
  }
}

void LabTechnician::lockedDoorFound()
{
  if(global_map->getTileAtPoint(current_route[route_index + 1]->position)->getPointOfInterestState() != poi_state ::POI_IS_BEING_FIXED)
  {
    // Add fixing this door to the front of the queue
    broken_pois.push_front(global_map->getTileAtPoint(current_route[route_index + 1]->position));
    repairing = true;
  }
  else
  {
      current_route[route_index + 1]->pathable = false;
      calculateRouteToPoint(findPositionForPOI(
              Point(broken_pois.front()->getPositionX(), broken_pois.front()->getPositionY())));
  }
    float x_diff = current_route[route_index + 1]->position.x_pos - position.x_pos;
    float y_diff = current_route[route_index + 1]->position.y_pos - position.y_pos;
    direction.set(x_diff, y_diff);
    direction.normalise();
    distance_to_next_node =
            Point::distanceBetween(position, current_route[route_index + 1]->position);

}