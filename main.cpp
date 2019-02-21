#include "Source/PlannedObsolescence.h"
#include <iostream>
#include <string>

#ifdef NDEBUG
#  define SHOULD_RUN_GAME false
#else
#  define SHOULD_RUN_GAME true
#endif

int main(int argc, char* argv[])
{
  /* Check we've been opened through the launcher (or are in debug mode). */
  bool should_launch = SHOULD_RUN_GAME;
  for (int i = 0; i < argc; i++)
  {
    std::string launch_option = argv[i];
    if (launch_option == "PO_Launcher_Auth")
    {
      should_launch = true;
      break;
    }
  }

  /* Run game if so */
  if (should_launch)
  {
    PlannedObsolescence game;
    if (!game.init())
    {
      return -1;
    }

    game.run();
  }
  else
  {
    std::cout << "Must be run through launcher!" << std::endl;
  }

  return 0;
}