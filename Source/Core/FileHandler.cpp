#include "FileHandler.h"

/* Open the file as a JSON data structure */
json FileHandler::openAsJSON(std::string& filename)
{
  json json_file;
  auto file = ASGE::FILEIO::File();
  file.open("data/" + filename);
  auto buffer = file.read();
  if (buffer.length > 0)
  {
    std::stringstream(std::string(buffer.as_char(), buffer.length)) >> json_file;
  }
  return json_file;
}

/* Open the file as a buffer */
std::string FileHandler::openAsString(std::string& filename)
{
  auto file = ASGE::FILEIO::File();
  file.open("data/" + filename);
  auto buffer = file.read();
  if (buffer.length > 0)
  {
    return std::string(buffer.as_char(), buffer.length);
  }
  return "";
}