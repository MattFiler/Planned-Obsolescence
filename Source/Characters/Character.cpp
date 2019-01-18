#include "Character.h"
#include <Engine/DebugPrinter.h>
using namespace std;

/* Load config on instantiation */
Character::Character()
{
  updateCoreConfig();
}

/* Allow character variations to update the config to suit their needs */
void Character::updateCoreConfig(std::string character_type)
{
  // Load our config and assign default values.
  string config_file("CONFIGS/characters_core.json");
  json temp_config = file_handler.openAsJSON(config_file);
  core_config = temp_config["DEFAULT"];

  // If we're requesting default, we can stop here.
  if (character_type == "DEFAULT")
  {
    return;
  }

  // If not, continue to override the selected character's details.
  temp_config = temp_config[character_type];
  for (json::iterator it = temp_config.begin(); it != temp_config.end(); ++it) {
    if (!temp_config[it.key()].is_null()) {
      core_config[it.key()] = it.value();
    }
  }
}

/* Check that we are visible for rendering */
bool Character::isVisible()
{
  return true;
}