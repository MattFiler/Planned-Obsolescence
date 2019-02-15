#include "Character.h"

class Security : public Character
{
 public:
  Security() : Character(character_type::SECURITY){};
  ~Security() = default;
};