#ifndef PO_GOONDEF
#define PO_GOONDEF

#include "Character.h"

class Goon : public Character
{
 public:
  Goon() : Character(character_type::GOON){};
  ~Goon() = default;

  float getProductivity();
  void reduceProductivity(float reduce_by = 1);

 private:
  float current_productivity = 100.0f;
};

#endif