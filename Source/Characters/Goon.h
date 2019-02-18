#ifndef PO_GOONDEF
#define PO_GOONDEF

#include "Character.h"

class Goon : public Character
{
 public:
  Goon() : Character(character_type::GOON){};
  ~Goon() = default;
};

#endif