#include "Source/PlannedObsolescence.h"
#include <iostream>
int main()
{
  PlannedObsolescence game;
  if (!game.init())
  {
    return -1;
  }

  game.run();

  std::cout << "Exiting Game!" << std::endl;
  return 0;
}