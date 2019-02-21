#ifndef PO_LABTECHIE
#define PO_LABTECHIE

#include "Character.h"
#include <deque>

class LabTechnician : public Character
{
 public:
  LabTechnician() : Character(character_type::TECHNICIAN){};
  ~LabTechnician() override = default;

  void lockedDoorFound() override;
  void update(double delta_time) override;
  void addRepairRequest(Tile* tile) { broken_pois.push_back(tile); };

  void setHomePosition(float x_pos, float y_pos) { idle_position = Point(x_pos, y_pos); };
  unsigned long long int getRepairQueueLength() { return broken_pois.size(); }

 private:
  Point idle_position = Point(0, 0);

  double time_elapsed = 0;
  bool repairing = false;

  std::deque<Tile*> broken_pois;
};

#endif