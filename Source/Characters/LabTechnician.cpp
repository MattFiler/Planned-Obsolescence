#include "LabTechnician.h"

void LabTechnician::update(double delta_time)
{
  if (repairing)
  {
    time_elapsed += delta_time;
    if (time_elapsed > repair_time)
    {
      time_elapsed = 0;
      repairing = false;
    }
  }
  else if (!updatePosition(delta_time))
  {
    if (broken_pois.empty())
    {
      calculateRouteToPoint(idle_position);
    }
    else
    {
      calculateRouteToPoint(broken_pois.front());
      broken_pois.pop();
    }
  }
}

void LabTechnician::lockedDoorFound()
{
  repairing = true;
}