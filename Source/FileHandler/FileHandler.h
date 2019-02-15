#ifndef PO_FILEHANDLER
#define PO_FILEHANDLER

#include "../Debug/DebugText.h"
#include <Engine/FileIO.h>
#include <json.hpp>
#include <soloud.h>
#include <soloud_wavstream.h>
#include <sstream>
#include <string>
using json = nlohmann::json;

class FileHandler
{
 public:
  json openAsJSON(std::string& filename);
  json loadConfig(std::string& config, std::string request = "DEFAULT");
  json loadConfigFromExisting(json temp_config,
                              std::string& request,
                              const std::string& original_filename = "");
  std::string openAsString(std::string& filename);
  SoLoud::WavStream loadSound(std::string& filename);

 private:
  DebugText debug_text;
};

#endif