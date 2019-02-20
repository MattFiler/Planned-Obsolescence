#ifndef PO_SECURITYGUARD
#define PO_SECURITYGUARD

#include "../Map/GameMap.h"
#include "Character.h"

class Security : public Character
{
 public:
  Security() : Character(character_type::SECURITY){};
  ~Security() override;

  void setMapData(GameMap* map) { game_map = map; };
  std::vector<Point>* getPatrolRoute() { return &patrol_route; };

  void setupPatrolRoute();

 private:
  Point getMiddleTilePosition(Room& this_room);

  std::vector<Point> patrol_route;

  GameMap* game_map = nullptr;
};

#endif