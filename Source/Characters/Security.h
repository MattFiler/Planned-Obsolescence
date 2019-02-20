#ifndef PO_SECURITYGUARD
#define PO_SECURITYGUARD

#include "Character.h"

class Security : public Character
{
 public:
  Security() : Character(character_type::SECURITY){};
  ~Security() override = default;

  std::vector<Point>* getPatrolRoute() { return &patrol_route; };

 private:
  std::vector<Point> patrol_route;
};

#endif