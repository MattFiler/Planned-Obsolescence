#ifndef PO_CONSTANTS
#define PO_CONSTANTS

/*
 *
 * All values in this file are configured alongside their respective code.
 * DO NOT MODIFY ANY CONSTANTS UNLESS AUTHORISED!
 *
 */

/* --- Character --- */

// Our character types
enum character_type
{
  DEFAULT,
  SECURITY, // Also referred to as "GUARD" sometimes... trying to depreciate that!
  GOON,
  BOSS,
  TECHNICIAN,
};

// The character's currently active job
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

// Potential movement directions from tile
enum direction
{
  LEFT,
  RIGHT,
  UP,
  DOWN
};

// Points of interest are either doors (open/close) or "computers" (working/broken)
enum point_of_interest
{
  NONE_ON_THIS_TILE,
  COMPUTER,
  DOOR
};

// POI state (affected by interaction)
enum poi_state
{
  POI_IS_BROKEN,             // POI is broken and unused
  POI_IS_FUNCTIONAL,         // POI is functional and unused
  POI_IS_BEING_USED_BY_GOON, // POI is in use, can't interact
  POI_REPAIR_PENDING,        // A repair is queued up
  POI_IS_BEING_FIXED,        // POI is being repaired by technician
  UNINITIALISED_POI          // Tile is not a POI
};

// Accessibility - can we traverse this tile?
enum tile_accessibility
{
  TILE_IS_TRAVERSABLE,
  TILE_IS_NON_TRAVERSABLE
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

// Cursor variants
enum cursor_variant
{
  CURSOR_DEFAULT,
  CURSOR_POINTER
};

/* --- Game --- */

// Scenes
enum scenes
{
  NO_CHANGE,
  SPLASHSCREEN,
  MAIN_MENU,
  GAME_CORE,
  QUIT_GAME,
  GAME_OVER
};

// Render index
enum render_index
{
  BASE_LAYER,
  MAP_LAYER,
  TILE_LAYER,
  CHARACTER_LAYER,
  UI_SPRITE_LAYER,
  UI_TEXT_LAYER,
  UI_TOP_LAYER_BASE,
  UI_TOP_LAYER_ANIMATED,
  UI_TOP_LAYER_CAP
};

// Hud gauges
enum hud_gauge_types
{
  YOUR_DETECTION,
  PROJECT_PROGRESS,
  TIME_REMAINING,
  PLAYER_POWER
};

// Gauge levels
enum gauge_levels
{
  GAUGE_FULL = 100,
  GAUGE_HALF = 50,
  GAUGE_EMPTY = 0
};

// Gauge tick-rates
enum gauge_rates
{
  PROJECT_TIMER = 1000,      // deltatime (ms) divided by THIS
  POWER = 400,               // deltatime (ms) divided by THIS
  TOTAL_PROGRESS = 700,      // deltatime (ms) divided by THIS multiplied by normalised productivity
                             // average
  GOON_PRODUCTIVTIY = 10000, // defines how often productivity is modified and by how much
  SECURITY_AWARENESS = 1,    // TO BE IMPLEMENTED
  TECHIE_STRESS = 1,         // TO BE IMPLEMENTED
  BOSS_FAITH = 1,            // TO BE IMPLEMENTED
};

// Game over definitions
enum game_over_type
{
  PLAYER_WON,
  PLAYER_LOST,
  NOT_YET_DECIDED
};

// Our native resolution which we will scale from to the resolution specified in the game config.
const float SCREEN_WIDTH = 1280;
const float SCREEN_HEIGHT = 720;

#endif