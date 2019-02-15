#include "DebugText.h"
#include "../Constants.h"
using namespace std;

/* Print a string if debug outputs are enabled */
void DebugText::print(const string& debug_string)
{
  if (enabled)
  {
    ASGE::DebugPrinter{} << "PO_DEBUG: " << debug_string << endl;
  }
}

/* This value is modified to config definition at runtime */
bool DebugText::enabled = false;