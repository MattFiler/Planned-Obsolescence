#ifndef PLANNEDOBSOLESCENCE_GETLOCALISEDSTRING_H
#define PLANNEDOBSOLESCENCE_GETLOCALISEDSTRING_H

#include "../Debug/DebugText.h"
#include "../FileHandler/FileHandler.h"
#include <json.hpp>
using json = nlohmann::json;

struct GetLocalisedString
{
  void configure(const std::string& language)
  {
    language_definition = language;
    language_config = file_handler.loadConfig("ui_localised.json", language);
  }
  std::string getString(const std::string& id)
  {
    if (language_config[id].is_string())
    {
      return language_config[id];
    }
    debug_text.print("COULDN'T FIND A LOCALISATION FOR '" + id + "'");
    return id;
  }
  std::string getLanguage() { return language_definition; }

 private:
  FileHandler file_handler;
  static json language_config;
  static std::string language_definition;
  DebugText debug_text;
};

#endif // PLANNEDOBSOLESCENCE_GETLOCALISEDSTRING_H
