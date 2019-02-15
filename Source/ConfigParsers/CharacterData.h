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
    std::string config_file = "characters_core.json";
    character_config = file_handler.loadConfig(config_file, std::to_string(type));

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

    // Our internal gauges
    gauge_suspicion = character_config["gauge"]["suspicion"];
    gauge_stress = character_config["gauge"]["stress"];
    gauge_productivity = character_config["gauge"]["productivity"];
    gauge_faith = character_config["gauge"]["faith"];

    // Our sprites - this is gonna be refactored!!
    sprite_walking = character_config["sprites"]["walking"][0];
    sprite_idle = character_config["sprites"]["idle"][0];
  };

  character_type variant = character_type::DEFAULT;
  std::string id = "";
  int index = 0;

  int width = 0;
  int height = 0;
  bool is_visible = false;

  Point spawn_pos = Point(0, 0);
  int spawn_cap = 0;

  int movement_speed = 0;
  int max_health = 0;

  int gauge_suspicion = 0;
  int gauge_stress = 0;
  int gauge_productivity = 0;
  int gauge_faith = 0;

  std::string sprite_walking = "";
  std::string sprite_idle = "";
};

#endif // PLANNEDOBSOLESCENCE_CHARACTERDATA_H