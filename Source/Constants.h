#ifndef PO_CONSTANTS
#define PO_CONSTANTS

/*
 *
 * All values in this file are configured alongside their respective code.
 * DO NOT MODIFY ANY CONSTANTS UNLESS AUTHORISED!
 *
 */

/* --- Character --- */

// Character types are hard-coded into everything. Do not modify this list!
enum character_type
{
  BOSS,
  GOON,
  TECHNICIAN,
  SECURITY
};

// The character's currently active job.
enum character_job
{
  JUST_SPAWNED_IN,
  IDLE,
  LOOKING_BUSY,
  SUSPICIOUS,
  CHILLING_OUT,
  GETTING_ANGRY,
  REALLY_ANGRY
};

/* --- Map --- */

// Potential movement directions from tile. Do not modify unless you want to break something!
enum direction
{
  LEFT,
  RIGHT,
  UP,
  DOWN
};

// Points of interest are hard-coded into everything. Do not modify this list!
enum point_of_interest
{
  COMPUTER,
  DOOR
};

/* --- Game --- */

// Enable debug output if required - this option is set at runtime, do not modify!
struct debug
{
  // cppcheck-suppress unusedStructMember
  static bool enabled;
};

// Our native resolution which we will scale from to the resolution specified in the game config.
const float SCREEN_WIDTH = 1280;
const float SCREEN_HEIGHT = 720;

#endif