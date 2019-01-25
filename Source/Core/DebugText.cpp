#include "DebugText.h"
#include "../Constants.h"
using namespace std;

/* Print a string if debug outputs are enabled */
void DebugText::print(string debug_string)
{
  if (debug::enabled)
  {
    ASGE::DebugPrinter{} << debug_string << endl;
  }
  else
  {
    ASGE::DebugPrinter{} << "debug disabled" << endl;
  }
}