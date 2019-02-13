#include "Source/PlannedObsolescence.h"
#include <iostream>
#include <string>

#ifdef NDEBUG
bool shouldRun()
{
  return false;
}
#else
bool shouldRun()
{
  return true;
}
#endif

int main(int argc, char* argv[])
{
  /* Check we've been opened through the launcher (or are in debug mode). */
  bool should_launch = shouldRun();
  if (!should_launch)
  {
    for (int i = 0; i < argc; i++)
    {
      std::string launch_option = argv[i];
      if (launch_option == "PO_Launcher_Auth")
      {
        should_launch = true;
        break;
      }
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

    std::cout << "\n Exiting Game!" << std::endl;
  }
  else
  {
    std::cout << "Must be run through launcher!" << std::endl;
  }

  return 0;
}