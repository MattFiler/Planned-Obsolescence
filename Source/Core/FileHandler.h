#ifndef PO_FILEHANDLER
#define PO_FILEHANDLER

#include <Engine/FileIO.h>
#include <json.hpp>
#include <sstream>
#include <string>
#include <soloud.h>
#include <soloud_wavstream.h>
using json = nlohmann::json;
using namespace SoLoud;

class FileHandler
{
 public:
  json openAsJSON(std::string& filename);
  std::string openAsString(std::string& filename);
  WavStream loadSound(std::string& filename);
};

#endif