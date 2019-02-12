#include "DebugText.h"
#include "../Constants.h"
using namespace std;

/* Print a string if debug outputs are enabled */
void DebugText::print(string& debug_string)
{
  if (enabled)
  {
    ASGE::DebugPrinter{} << "PO_DEBUG: " << debug_string << endl;
  }
}

// This value is actually set on game load!
bool DebugText::enabled = false;