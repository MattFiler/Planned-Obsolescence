#ifndef PO_FILEHANDLER
#define PO_FILEHANDLER

#include <Engine/FileIO.h>
#include <json.hpp>
#include <soloud.h>
#include <soloud_wavstream.h>
#include <sstream>
#include <string>
using json = nlohmann::json;
using namespace SoLoud;

class FileHandler
{
 public:
  json openAsJSON(std::string& filename);
  json loadConfig(std::string config, std::string request = "DEFAULT");
  std::string openAsString(std::string& filename);
  WavStream loadSound(std::string& filename);
};

#endif