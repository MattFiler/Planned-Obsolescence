#ifndef PO_LVL100BOSS
#define PO_LVL100BOSS

#include "Character.h"

class Boss : public Character
{
 public:
  Boss() : Character(character_type::BOSS){};
  ~Boss() = default;
};

#endif