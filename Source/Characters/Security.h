#ifndef PO_SECURITYGUARD
#define PO_SECURITYGUARD

#include "../Map/GameMap.h"
#include "Character.h"

class Security : public Character
{
 public:
  Security() : Character(character_type::SECURITY){};
  ~Security() override = default;

  void update(double delta_time) override;
  void lockedDoorFound() override;

  void setupPatrolRoute();

  std::function<void(Tile*)> registerRepairRequest;

 private:
  Point getMiddleTilePosition(Room& this_room);

  std::vector<Point> patrol_route;
  unsigned long long int patrol_index = 0;
};

#endif