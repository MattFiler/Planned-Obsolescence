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
WavStream FileHandler::loadSound(std::string &filename)
{
  WavStream sound;
  auto file = ASGE::FILEIO::File();
  if (file.open("/data/" + filename))
  {
    auto buffer = file.read();
    if (buffer.length > 0)
    {
      sound.loadMem(buffer.as_unsigned_char(), static_cast<unsigned int>(buffer.length), false, false);
    }
  }
  return sound;
}