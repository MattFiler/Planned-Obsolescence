#include "DebugText.h"
#include "../Constants.h"

#ifdef NDEBUG
#  define IS_IN_DEBUG_MODE false
#else
#  define IS_IN_DEBUG_MODE true
#endif

/* Print a string if debug outputs are enabled */
void DebugText::print(const std::string& debug_string)
{
  if (enabled && IS_IN_DEBUG_MODE)
  {
    ASGE::DebugPrinter{} << "PO_DEBUG: " << debug_string << std::endl;
  }
}

/* This value is modified to config definition at runtime */
bool DebugText::enabled = false;