#include "Character.h"
using namespace std;

/* Load config on instantiation */
Character::Character()
{
  // Load default config
  updateCoreConfig();
  current_route.resize(1);
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

  string debug_string = "SPAWNED NEW " + character_variant;
  debug_text.print(debug_string);
}

/* Allow character variations to update the config to suit their needs */
void Character::updateCoreConfig(std::string character_type)
{
  string config_file = "characters_core.json";
  character_config = file_handler.loadConfig(config_file, character_type);
  character_variant = character_type;
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
  // Check if at the end of a route, if so there is no point checking for movement
  if (route_index != current_route.size() - 1)
  {
    // Store the current distance to the next node
    float previous_distance = distance_to_next_node;
    // Add to the current position based on speed and delta_time
    position.x_pos += direction.x_mag * static_cast<float>(delta_time) * 0.01f *
                      static_cast<float>(character_config["movement_speed"]);
    position.y_pos += direction.y_mag * static_cast<float>(delta_time) * 0.01f *
                      static_cast<float>(character_config["movement_speed"]);

    my_sprite->xPos(position.x_pos);
    my_sprite->yPos(position.y_pos);

    // Calculate the new distance to the next node
    distance_to_next_node =
      Point::distanceBetween(position, current_route[route_index + 1]->position);
    // If the distance increased, then we have over-shot
    if (previous_distance < distance_to_next_node)
    {
      route_index++;
      // Set the position to that of the node just reached
      position = current_route[route_index]->position;
      // If this was the last node
      if (current_route.size() - 1 == route_index)
      {
        direction.set(0, 0);
      }
      else
      {
        // Calculate the new direction
        float x_diff = current_route[route_index + 1]->position.x_pos - position.x_pos;
        float y_diff = current_route[route_index + 1]->position.y_pos - position.y_pos;
        direction.set(x_diff, y_diff);
        direction.normalise();
        distance_to_next_node =
          Point::distanceBetween(position, current_route[route_index + 1]->position);
      }
    }
  }
}

/* Generate the internal map that this character will use to pathfind */
void Character::generatePathfindingMap(GameMap* game_map)
{
  internal_map = new PathfindingMap(game_map);
  // Find the node that this character is currently at
  for (int i = 0; i < internal_map->number_of_nodes; i++)
  {
    if (position == internal_map->nodes[i].position)
    {
      current_route[0] = &internal_map->nodes[i];
      return;
    }
  }
  // If no node was found, then assign to the first node to avoid errors
  if (current_route[0] == nullptr)
  {
    current_route[0] = &internal_map->nodes[0];
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
      current_route.resize(1);
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
      // If this node has not been scored yet
      if (node->connections[i].score == -1)
      {
        // Calculate a score based on the distance between this node and the
        // target point
        node->connections[i].score =
          Point::distanceBetween(node->connections[i].node->position, point);
      }
      if (node->connections[i].score <= best_score)
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

    // Score is 0 when the node is found
    if (best_score_at_depth < 0.01f)
    {
      current_route.push_back(node->connections[best_score_index].node);
      return 0;
    }

    // Setting visited to true before recurring the algorithm will prevent
    // this node from being visited again until the next iteration.
    node->visited = true;
    best_score_at_depth = calculateScoresOfNextDepth(
      node->connections[best_score_index].node, depth + 1, best_score, point);
    // Update the score to this connection to indicate the lowest score this
    // path currently finds
    node->connections[best_score_index].score = best_score_at_depth;
    node->visited = false;

    // Check through all score again with the new updated one
    for (int i = 0; i < 4; i++)
    {
      if (node->connections[i].score < best_score_at_depth && node->connections[i].score != -1 &&
          node->connections[i].node != nullptr)
      {
        best_score_at_depth = node->connections[i].score;
      }
    }
  }
  return best_score_at_depth;
}

/* Adjust spawn position */
void Character::setSpawnPosition(int x_pos, int y_pos)
{
  character_config["spawn_pos"][0] = x_pos;
  character_config["spawn_pos"][1] = y_pos;
}

/* Toggle visibility */
void Character::setVisible(bool isVisible)
{
  character_config["is_visible"] = isVisible;
}

/* Adjust dimensions */
void Character::setDimensions(int new_width, int new_height)
{
  character_config["width"] = new_width;
  character_config["height"] = new_height;
}

/* Adjust movement speed */
void Character::setSpeed(int speed)
{
  character_config["movement_speed"] = speed;
}

/* Return the spawn limit for this character class */
unsigned long long Character::getSpawnCap()
{
  return character_config["spawn_cap"];
}
int Character::getSpawnCapAsInt()
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

/* Set the character ID */
void Character::setCharacterID(int index)
{
  character_id = character_variant + to_string(index);
  character_index = index;
}

/* Get the character ID */
string Character::getCharacterID()
{
  return character_id;
}

/* Return the character index */
int Character::getIndex()
{
  return character_index;
}