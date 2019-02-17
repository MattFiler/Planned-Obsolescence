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
  DEFAULT,
  SECURITY, // Also referred to as "GUARD" sometimes... trying to depreciate that!
  GOON,
  BOSS,
  TECHNICIAN,
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
  NONE_ON_THIS_TILE,
  COMPUTER,
  DOOR
};

enum Event
{
  DEFAULTE
};

/* --- UI --- */

// Rotation used for progress bars
enum rotation
{
  LEFT_TO_RIGHT = 0,
  UP_TO_DOWN = 1,
};

/* --- Game --- */

// Scenes
enum scenes
{
  NO_CHANGE = -1,
  SPLASHSCREEN = 0,
  MAIN_MENU = 1,
  GAME_CORE = 2
};

// Render index
enum render_index
{
  ROOM_LAYER,
  SPECIAL_TILE_LAYER,
  CHARACTER_LAYER,
  UI_LAYER
};

// Our native resolution which we will scale from to the resolution specified in the game config.
const float SCREEN_WIDTH = 1280;
const float SCREEN_HEIGHT = 720;

#endif