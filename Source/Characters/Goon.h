#ifndef PO_GOONDEF
#define PO_GOONDEF

#include "Character.h"

class Goon : public Character
{
 public:
  Goon();

  void update(double delta_time) override;
  void findNewPOI();
  void findPositionForPOI(Point point, Room* room);

 private:
  Tile* point_of_interest_tile = nullptr;
  Point poi_position = Point(0, 0);

  double total_time_for_poi = 0;
  double time_elapsed_at_poi = 0;

  double productivity_average[20] = {}; // A 20 point moving average of productivity
  int average_index = 0;
  double productivity_interval = 10000; // How often the productivity average updates
  double time_since_last_interval = 0;
  double time_working = 0; // Time spent working since last interval
};

#endif