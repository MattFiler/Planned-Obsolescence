#ifndef PO_GOONDEF
#define PO_GOONDEF

#include "Character.h"
#include <functional>

class Goon : public Character
{
 public:
  Goon();

  void update(double delta_time) override;
  void lockedDoorFound() override;
  void findNewPOI();

  std::function<void(Tile*)> registerRepairRequest;

 private:
  void getAllPOIInRoom(std::vector<Tile*>* all_poi, Room* room, bool ignore_functionality);

  Tile* point_of_interest_tile = nullptr;
  Point poi_position = Point(0, 0);

  double total_time_for_poi = 0;
  double time_elapsed_at_poi = 0;

  double productivity_average[20] = {}; // A 20 point moving average of productivity
  int average_index = 0;
  double time_since_last_interval = 0;
  double time_working = 0; // Time spent working since last interval
  bool at_valid_poi = false;
};

#endif