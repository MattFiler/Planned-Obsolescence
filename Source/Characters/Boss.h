#include "Character.h"

class Boss : public Character
{
 public:
  Boss() : Character(character_type::BOSS){};
  ~Boss() = default;
};