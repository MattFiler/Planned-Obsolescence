#include "FileHandler.h"
using namespace std;

/* Open the file as a JSON data structure */
json FileHandler::openAsJSON(string& filename)
{
  json json_file;
  auto file = ASGE::FILEIO::File();
  if (file.open("data/" + filename))
  {
    auto buffer = file.read();
    if (buffer.length > 0)
    {
      stringstream(string(buffer.as_char(), buffer.length)) >> json_file;
    }
  }
  return json_file;
}

/* Load a requested portion of a game config */
json FileHandler::loadConfig(std::string& config, std::string request)
{
  // Load our config and assign default values.
  string config_file("CONFIGS/" + config);
  json temp_config = openAsJSON(config_file);
  json final_config = temp_config["DEFAULT"];

  // If we're requesting default, we can stop here.
  if (request == "DEFAULT")
  {
    return final_config;
  }

  // If not, continue to override the selected character's details.
  temp_config = temp_config[request];
  for (json::iterator i = temp_config.begin(); i != temp_config.end(); ++i)
  {
    if (!temp_config[i.key()].is_null())
    {
      final_config[i.key()] = i.value();
    }
  }
  return final_config;
}

/* Open the file as a buffer */
string FileHandler::openAsString(string& filename)
{
  auto file = ASGE::FILEIO::File();
  if (file.open("data/" + filename))
  {
    auto buffer = file.read();
    if (buffer.length > 0)
    {
      return string(buffer.as_char(), buffer.length);
    }
  }
  return "";
}

/* Load a sound into a SoLoud WavStream */
WavStream FileHandler::loadSound(std::string& filename)
{
  WavStream sound;
  auto file = ASGE::FILEIO::File();
  if (file.open("/data/" + filename))
  {
    auto buffer = file.read();
    if (buffer.length > 0)
    {
      sound.loadMem(
        buffer.as_unsigned_char(), static_cast<unsigned int>(buffer.length), false, false);
    }
  }
  return sound;
}