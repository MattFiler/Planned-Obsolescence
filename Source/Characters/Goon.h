#include "Character.h"

class Goon : public Character
{
 public:
  Goon() : Character(character_type::GOON){};
  ~Goon() = default;
};