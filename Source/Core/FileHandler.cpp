#include "FileHandler.h"
using namespace std;
using namespace SoLoud;

/* Open the file as a JSON data structure */
json FileHandler::openAsJSON(string& filename)
{
  std::string debug_log = "ACCESSING FILE AS JSON (openAsJSON) - " + filename;
  debug_text.print(debug_log);

  // Load file into json structure and return
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
  std::string debug_log = "ACCESSING FILE AS JSON (loadConfig) - CONFIGS/" + config;
  debug_text.print(debug_log);

  // Load our config and assign default values.
  string config_file("CONFIGS/" + config);
  json temp_config = openAsJSON(config_file);

  return loadConfigFromExisting(temp_config, request, config);
}

/* Load required JSON from an existing JSON object */
json FileHandler::loadConfigFromExisting(json temp_config,
                                         std::string& request,
                                         const std::string& original_filename)
{
  // TODO: This is an ugly temp fix for DEFAULT enum. Improve!
  std::string default_text = "DEFAULT";
  if (original_filename == "characters_core.json")
  {
    default_text = "0";
  }
  json final_config = temp_config[default_text];

  // If we're requesting default, we can stop here.
  if (request == default_text)
  {
    return final_config;
  }

  // If not, continue to override the selected character's details.
  // Please note: only supports ONE layer of recursion into objects.
  temp_config = temp_config[request];
  for (json::iterator i = temp_config.begin(); i != temp_config.end(); ++i)
  {
    if (!temp_config[i.key()].is_null() && !temp_config[i.key()].is_object())
    {
      final_config[i.key()] = i.value();
    }
    else if (temp_config[i.key()].is_object())
    {
      for (json::iterator x = temp_config[i.key()].begin(); x != temp_config[i.key()].end(); ++x)
      {
        if (!temp_config[i.key()][x.key()].is_null())
        {
          final_config[i.key()][x.key()] = x.value();
        }
      }
    }
  }
  return final_config;
}

/* Open the file as a buffer */
string FileHandler::openAsString(string& filename)
{
  std::string debug_log = "ACCESSING FILE AS STRING - " + filename;
  debug_text.print(debug_log);

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
  std::string debug_log = "ACCESSING FILE FOR AUDIO - " + filename;
  debug_text.print(debug_log);

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