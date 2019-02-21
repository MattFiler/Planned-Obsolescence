#ifndef PO_FILEHANDLER
#define PO_FILEHANDLER

#include "../Debug/DebugText.h"
#include <Engine/FileIO.h>
#include <json.hpp>
#include <soloud.h>
#include <soloud_wav.h>
#include <sstream>
#include <string>
using json = nlohmann::json;

class FileHandler
{
 public:
  json openAsJSON(const std::string& filename);
  json loadConfig(const std::string& config, const std::string& request = "DEFAULT");
  json loadConfigFromExisting(json temp_config,
                              const std::string& request,
                              const std::string& original_filename = "");

  std::string openAsString(const std::string& filename);
  SoLoud::Wav loadSound(const std::string& filename);

  ASGE::FILEIO::IOBuffer openAsBuffer(const std::string& filename);

 private:
  DebugText debug_text;
};

#endif