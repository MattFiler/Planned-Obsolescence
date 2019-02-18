#include "Goon.h"

/* Get the goon's current productivity level */
float Goon::getProductivity()
{
  return current_productivity;
}

/* Reduce the goon's productivity by an amount */
void Goon::reduceProductivity(float reduce_by) {
  current_productivity -= 1;
}