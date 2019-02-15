#include "Character.h"

class LabTechnician : public Character
{
 public:
  LabTechnician() : Character(character_type::TECHNICIAN){};
  ~LabTechnician() = default;
};