#include "Character.h"
using namespace std;

/* Load config on instantiation */
Character::Character()
{
  // Load default config
  updateCoreConfig();
  current_route.resize(10);
}

Character::~Character()
{
  delete internal_map;
  internal_map = nullptr;
}

/* Catch the renderer, then we can load our sprite */
void Character::wake(ASGE::Renderer* passed_renderer)
{
  renderer = passed_renderer;
  updateSprite();
}

/* Allow character variations to update the config to suit their needs */
void Character::updateCoreConfig(std::string character_type)
{
  // Load our config and assign default values.
  string config_file("CONFIGS/characters_core.json");
  json temp_config = file_handler.openAsJSON(config_file);
  character_config = temp_config["DEFAULT"];

  // If we're requesting default, we can stop here.
  if (character_type == "DEFAULT")
  {
    return;
  }

  // If not, continue to override the selected character's details.
  temp_config = temp_config[character_type];
  for (json::iterator i = temp_config.begin(); i != temp_config.end(); ++i)
  {
    if (!temp_config[i.key()].is_null())
    {
      character_config[i.key()] = i.value();
    }
  }
}

/* Update our sprite */
void Character::updateSprite()
{
  delete my_sprite;
  my_sprite = new DynamicSprite(1);
  ASGE::Sprite* new_sprite = renderer->createRawSprite();
  new_sprite->loadTexture(getSpritePath());
  my_sprite->addSprite(*new_sprite);
}

/* Update the position of the character based on current route and speed */
void Character::updatePosition(double delta_time)
{
  // Store the current distance to the next node
  float previous_distance = distance_to_next_node;
  // Add to the current position based on speed and delta_time
  position.x_pos += direction.x_mag * static_cast<float>(delta_time) *
                    static_cast<float>(character_config["character_speed"]);
  position.y_pos += direction.x_mag * static_cast<float>(delta_time) *
                    static_cast<float>(character_config["character_speed"]);

  // Calculate the new distance to the next node
  distance_to_next_node = Point::distanceBetween(position, current_route[route_index]->position);
  // If the distance increased, then we have over-shot
  if (previous_distance < distance_to_next_node)
  {
    route_index++;
    // Set the position to that of the current node being pathed to
    position = current_route[route_index]->position;
    // If this was the last node
    if (current_route.size() == route_index - 1)
    {
      direction.set(0, 0);
    }
    else
    {
      // Calculate the new direction
      float x_diff = current_route[route_index + 1]->position.x_pos - position.x_pos;
      float y_diff = current_route[route_index + 1]->position.y_pos - position.y_pos;
      direction.set(x_diff, y_diff);
    }
  }
}

/* Generate the internal map that this character will use to pathfind */
void Character::generatePathfindingMap()
{
  // Need tile info to make this function properly, for now, here is a sample
  internal_map = new PathfindingMap;
  internal_map->nodes = new PathNode[11];
  internal_map->number_of_nodes = 11;
  internal_map->nodes[0].position.set(0, 0);
  internal_map->nodes[1].position.set(0, 100);
  internal_map->nodes[2].position.set(100, 100);
  internal_map->nodes[3].position.set(100, 0);
  internal_map->nodes[4].position.set(100, 200);
  internal_map->nodes[5].position.set(200, 100);
  internal_map->nodes[6].position.set(200, 0);
  internal_map->nodes[7].position.set(300, 0);
  internal_map->nodes[8].position.set(300, 100);
  internal_map->nodes[9].position.set(300, 200);
  internal_map->nodes[10].position.set(200, 200);

  internal_map->nodes[0].connections[3].node = &internal_map->nodes[1];

  internal_map->nodes[1].connections[1].node = &internal_map->nodes[2];
  internal_map->nodes[1].connections[2].node = &internal_map->nodes[0];

  internal_map->nodes[2].connections[0].node = &internal_map->nodes[1];
  internal_map->nodes[2].connections[1].node = &internal_map->nodes[5];
  internal_map->nodes[2].connections[2].node = &internal_map->nodes[3];
  internal_map->nodes[2].connections[3].node = &internal_map->nodes[4];

  internal_map->nodes[3].connections[3].node = &internal_map->nodes[2];

  internal_map->nodes[4].connections[2].node = &internal_map->nodes[2];

  internal_map->nodes[5].connections[0].node = &internal_map->nodes[2];
  internal_map->nodes[5].connections[1].node = &internal_map->nodes[8];
  internal_map->nodes[5].connections[2].node = &internal_map->nodes[6];

  internal_map->nodes[6].connections[1].node = &internal_map->nodes[7];
  internal_map->nodes[6].connections[3].node = &internal_map->nodes[5];

  internal_map->nodes[7].connections[0].node = &internal_map->nodes[6];
  internal_map->nodes[7].connections[3].node = &internal_map->nodes[8];

  internal_map->nodes[8].connections[0].node = &internal_map->nodes[5];
  internal_map->nodes[8].connections[2].node = &internal_map->nodes[7];
  internal_map->nodes[8].connections[3].node = &internal_map->nodes[9];

  internal_map->nodes[9].connections[0].node = &internal_map->nodes[10];
  internal_map->nodes[9].connections[2].node = &internal_map->nodes[8];

  internal_map->nodes[10].connections[1].node = &internal_map->nodes[9];

  // Find the node that this character is currently at
  for (int i = 0; i < internal_map->number_of_nodes; i++)
  {
    if (position == internal_map->nodes[i].position)
    {
      current_route[0] = &internal_map->nodes[i];
    }
  }
}

/* Find the quickest route from current position to target point, return false
 * if a route could not be found */
bool Character::calculateRouteToPoint(Point point)
{
  current_route[0] = current_route[route_index];

  // Loop until the node is found, or all nodes have been visited
  float best_score = 100000;

  while (best_score > 0)
  {
    best_score = 100000;
    best_score = calculateScoresOfNextDepth(current_route[0], 1, best_score, point);
    if (best_score == 100000)
    {
      return false;
    }
  }

  // Finally loop through the route to find where it ends
  for (unsigned long long i = 0; i < current_route.size(); i++)
  {
    if (current_route[i]->position == point)
    {
      current_route.resize(i + 1);
      return true;
    }
  }
  // Should never reach here, problems with the recursive algorithm if it does
  return false;
}

/* Calculate the scores of all connections, calls itself again if any score
 * is less than the best_score. Returns the best score found at lowest depth */
float Character::calculateScoresOfNextDepth(PathNode* node,
                                            unsigned long long int depth,
                                            float best_score,
                                            Point point)
{
  int best_score_index = -1;
  float best_score_at_depth = 100000;
  // Check each connection of the node
  for (int i = 0; i < 4; i++)
  {
    if (node->connections[i].node != nullptr && !node->connections[i].node->visited)
    {
      // Calculate a score based on the distance between this node and the
      // target point
      node->connections[i].score =
        Point::distanceBetween(node->connections[i].node->position, point);
      if (node->connections[i].score < best_score)
      {
        best_score = node->connections[i].score;
        best_score_index = i;
      }
      if (node->connections[i].score < best_score_at_depth)
      {
        best_score_at_depth = node->connections[i].score;
      }
    }
  }

  // If a better score was found
  if (best_score_index != -1)
  {
    // Add more space to the vector in case we exceed its limit
    if (current_route.size() == depth)
    {
      current_route.resize(depth + 5);
    }
    current_route[depth] = node->connections[best_score_index].node;
    // Setting visited to true before recurring the algorithm will prevent
    // this node from being visited again until the next iteration.
    node->visited = true;
    float return_score = calculateScoresOfNextDepth(
      node->connections[best_score_index].node, depth + 1, best_score, point);
    // Update the score to this connection to indicate the lowest score this
    // path currently finds
    node->connections[best_score_index].score = return_score;
    node->visited = false;
    if (return_score < best_score_at_depth)
    {
      return return_score;
    }
  }
  return best_score_at_depth;
}

/* Adjust spawn position */
void Character::setSpawnPosition(int x, int y)
{
  character_config["spawn_pos"][0] = x;
  character_config["spawn_pos"][1] = y;
}

/* Toggle visibility */
void Character::setVisible(bool isVisible)
{
  character_config["is_visible"] = isVisible;
}

/* Adjust dimensions */
void Character::setDimensions(int w, int h)
{
  character_config["width"] = w;
  character_config["height"] = h;
}

/* Adjust movement speed */
void Character::setSpeed(int speed)
{
  character_config["movement_speed"] = speed;
}

/* Return the spawn limit for this character class */
int Character::getSpawnCap()
{
  return character_config["spawn_cap"];
}

/* Check that we are visible for rendering */
bool Character::isVisible()
{
  return character_config["is_visible"];
}

/* Return the path to our character's sprite */
string Character::getSpritePath()
{
  return character_config["sprites"]["walking"][0];
}

/* Return sprite */
DynamicSprite* Character::getSprite()
{
  return my_sprite;
}

/* Return renderer */
ASGE::Renderer* Character::getRenderer()
{
  return renderer;
}