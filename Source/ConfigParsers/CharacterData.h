#ifndef PLANNEDOBSOLESCENCE_CHARACTERDATA_H
#define PLANNEDOBSOLESCENCE_CHARACTERDATA_H

#include "../../Libs/nlohmann/json.hpp"
#include "../Constants.h"
#include "../FileHandler/FileHandler.h"
#include "../Math/Point.h"
using json = nlohmann::json;

/* Character Data */
struct CharacterData
{
  void load(character_type type)
  {
    // Define our instances here so they go out of scope asap!
    json character_config;
    FileHandler file_handler;

    // Get the data from our config file
    character_config = file_handler.loadConfig("characters_core.json", std::to_string(type));

    // Our character variant
    variant = type;

    // ID and Index are handled by the character manager and set upon being spawned!

    // Visual configs
    width = character_config["width"];
    height = character_config["width"];
    is_visible = character_config["is_visible"];

    // Spawning configs
    spawn_pos = Point(character_config["spawn_pos"][0], character_config["spawn_pos"][1]);
    spawn_cap = character_config["spawn_cap"];

    // Speed and health
    movement_speed = character_config["movement_speed"];
    max_health = character_config["max_health"];

    // Our internal gauge
    internal_gauge_name = character_config["gauge_desc"];
    internal_gauge = character_config["gauge_value"];

    // Our display name
    display_name = character_config["display_name"];

    // Our sprites - this is gonna be refactored!!
    sprite_walking = character_config["sprites"]["walking"][0];
    sprite_idle = character_config["sprites"]["idle"][0];
  };

  character_type variant = character_type::DEFAULT;
  std::string id = "";
  int index = 0;

  float width = 0;
  float height = 0;
  bool is_visible = false;

  Point spawn_pos = Point(0, 0);
  int spawn_cap = 0;

  int movement_speed = 0;
  int max_health = 0;

  std::string display_name = "";

  std::string internal_gauge_name = "";
  float internal_gauge = 0.0f;

  std::string sprite_walking = "";
  std::string sprite_idle = "";
};

#endif // PLANNEDOBSOLESCENCE_CHARACTERDATA_H
