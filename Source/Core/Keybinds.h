#ifndef PLANNEDOBSOLESCENCE_KEYBINDS_H
#define PLANNEDOBSOLESCENCE_KEYBINDS_H

#include "DebugText.h"
#include <Engine/InputEvents.h>
#include <json.hpp>
using json = nlohmann::json;

/* User-defined keybinds (and handling for local use) */
struct Keybinds
{
 public:
  // Initial setup of keybind values
  void setup(json& keybind_config) { config = keybind_config; };
  // Initialisation of key event handler
  void registerEvent(const ASGE::KeyEvent* new_event) { key_event = new_event; }
  // Check of specific key being released
  bool keyReleased(std::string keybind)
  {
    if (config[keybind].is_null())
    {
      std::string debug_log = "WARNING: ATTEMPTED TO ACCESS UNINITIALISED KEYBIND - " + keybind;
      debug_text.print(debug_log);
    }
    return (key_event->key == config[keybind] && key_event->action == ASGE::KEYS::KEY_RELEASED);
  }

 private:
  const ASGE::KeyEvent* key_event;
  static json config;
  DebugText debug_text;
};

#endif // PLANNEDOBSOLESCENCE_KEYBINDS_H
