#ifndef PO_LABTECHIE
#define PO_LABTECHIE

#include "Character.h"
#include <queue>

class LabTechnician : public Character
{
 public:
  LabTechnician() : Character(character_type::TECHNICIAN){};
  ~LabTechnician() override = default;

  void lockedDoorFound() override;
  void update(double delta_time) override;
  void addRepairRequest(Point point) { broken_pois.push(point); };

  unsigned long long int getRepairQueueLength() { return broken_pois.size(); }

 private:
  Point idle_position = Point(0, 0);

  double repair_time = 10000;
  double time_elapsed = 0;
  bool repairing = false;

  std::queue<Point> broken_pois;
};

#endif