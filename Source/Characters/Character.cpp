#include "Character.h"

/* Load config on instantiation */
Character::Character(character_type type)
{
  config.load(type);
  current_route.resize(1);
}

/* Delete all dynamic data when destroyed */
Character::~Character()
{
  delete internal_map;
  internal_map = nullptr;
}

/* Catch the renderer, then we can load our sprite */
void Character::wake(ASGE::Renderer* passed_renderer)
{
  // Save renderer
  renderer = passed_renderer;

  // Create new
  config.configureSprites(renderer);

  // Resize click area and set position
  click_area.setWidth(config.width);
  click_area.setHeight(config.height);
  click_area.setPosition(position);
}

/* Update the position of the character based on current route and speed, returns true if it moved
 */
bool Character::updatePosition(double delta_time)
{
  // Check if at the end of a route, if so there is no point checking for movement
  if (route_index != current_route.size() - 1)
  {
    if(direction.x_mag > 0)
    {
      setDirection(direction::RIGHT);
    }
    else if(direction.x_mag < 0)
    {
      setDirection(direction::LEFT);
    }
    else if(direction.y_mag > 0)
    {
      setDirection(direction::DOWN);
    }
    else
    {
      setDirection(direction::UP);
    }
    // Store the current distance to the next node
    float previous_distance = distance_to_next_node;
    // Add to the current position based on speed and delta_time
    position.x_pos += direction.x_mag * static_cast<float>(delta_time) * 0.01f *
                      static_cast<float>(config.movement_speed) * speed_multiplier;
    position.y_pos += direction.y_mag * static_cast<float>(delta_time) * 0.01f *
                      static_cast<float>(config.movement_speed) * speed_multiplier;

    for (int i = 0; i < direction::DIRECTION_COUNT; i++)
    {
      config.sprites.at(i)->xPos(position.x_pos);
      config.sprites.at(i)->yPos(position.y_pos);
    }

    click_area.setPosition(position);

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
        resetPathfindingMap();
      }
      else
      {
        // Check to see if we have hit a closed door
        Tile* tile = global_map->getTileAtPoint(current_route[route_index + 1]->position);
        if (tile->getPointOfInterestState() != poi_state::POI_IS_FUNCTIONAL &&
            tile->getPointOfInterestState() != poi_state::UNINITIALISED_POI)
        {
          lockedDoorFound();
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
    return true;
  }
  return false;
}

/* Generate the internal map that this character will use to pathfind */
void Character::generatePathfindingMap(GameMap* game_map)
{
  global_map = game_map;
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
  // Don't bother calculating a path if its already at the destination
  if (point == position)
  {
    return true;
  }

  current_route[0] = current_route[route_index];
  route_index = 0;

  // Reset the current scores on the map
  clearPathfindingMapScores();

  // Loop until the node is found, or all nodes have been visited
  float best_score = 100000;
  iteration_count = 0;

  while (best_score > 0)
  {
    best_score = 100000;
    best_score = calculateScoresOfNextDepth(current_route[0], 1, best_score, point);
    if (best_score == 100000)
    {
      current_route.resize(1);
      debug_text.print(config.id + " COULD NOT ROUTE TO TARGET!");
      resetPathfindingMap();
      return false;
    }
  }

  // Finally loop through the route to find where it ends
  debug_text.print("PATH FOUND AFTER " + std::to_string(iteration_count) + " ITERATIONS");
  for (unsigned long long i = 0; i < current_route.size(); i++)
  {
    if (current_route[i]->position == point)
    {
      current_route.resize(i + 1);
      debug_text.print(config.id + " CALCULATED PATH TO TARGET ACROSS " + std::to_string(i) +
                       " TILES");
      float x_diff = current_route[1]->position.x_pos - position.x_pos;
      float y_diff = current_route[1]->position.y_pos - position.y_pos;
      direction.set(x_diff, y_diff);
      direction.normalise();
      distance_to_next_node = Point::distanceBetween(position, current_route[1]->position);
      // Check to see if the first node is a closed door
      Tile* tile = global_map->getTileAtPoint(current_route[route_index + 1]->position);
      if (tile->getPointOfInterestState() != poi_state::POI_IS_FUNCTIONAL &&
          tile->getPointOfInterestState() != poi_state::UNINITIALISED_POI)
      {
        lockedDoorFound();
      }
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
  iteration_count++;
  int best_score_index = -1;
  float best_score_at_depth = 100000;

  // If this node was reached in fewer moves than its previous best, update

  // Check each connection of the node
  for (int i = 0; i < 4; i++)
  {
    // If the node already has a shorter path, block this direction
    if (node->connections[i].node != nullptr && node->connections[i].node->pathable &&
        depth > node->connections[i].node->shortest_path_to_here)
    {
      node->connections[i].score = 10000;
    }
    else if (node->connections[i].node != nullptr && !node->connections[i].node->visited &&
             node->connections[i].node->pathable)
    {
      node->connections[i].node->shortest_path_to_here = depth + 1;
      // If this connection has not been scored yet
      if (node->connections[i].score == -1)
      {
        // Calculate a score based on the distance between this node and the
        // target point
        node->connections[i].score =
          Point::distanceBetween(node->connections[i].node->position, point);
        // Set this depth as the shortest path
      }

      // Check if this connection is better than any other option currently available
      if (node->connections[i].score <= best_score)
      {
        best_score = node->connections[i].score;
        best_score_index = i;
      }
      // Continue exploring the area even if a better score isn't found
      else if (best_score_index == -1 && node->connections[i].score <= best_score * 1.3f)
      {
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

    // Check through all scores again with the new updated one
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

/* Loops through and resets the scores on every connection */
void Character::clearPathfindingMapScores()
{
  for (int i = 0; i < internal_map->number_of_nodes; i++)
  {
    internal_map->nodes[i].visited = false;
    internal_map->nodes[i].shortest_path_to_here = 10000;
    for (int j = 0; j < 4; j++)
    {
      internal_map->nodes[i].connections[j].score = -1;
    }
  }
}

/* Resets the pathfinding map to have all connections open, and no nodes scored */
void Character::resetPathfindingMap()
{
  for (int i = 0; i < internal_map->number_of_nodes; i++)
  {
    internal_map->nodes[i].visited = false;
    internal_map->nodes[i].pathable = true;
    internal_map->nodes[i].shortest_path_to_here = 10000;
    for (int j = 0; j < 4; j++)
    {
      internal_map->nodes[i].connections[j].score = -1;
      internal_map->nodes[i].connections[j].open = true;
    }
  }
}

/* Adjust spawn position */
void Character::setSpawnPositionX(float x_pos)
{
  config.spawn_pos.x_pos = x_pos;
  position.x_pos = x_pos;
  for (int i = 0; i < direction::DIRECTION_COUNT; i++)
  {
    config.sprites.at(i)->xPos(position.x_pos);
  }
  click_area.setPosition(position);
}
void Character::setSpawnPositionY(float y_pos)
{
  config.spawn_pos.y_pos = y_pos;
  position.y_pos = y_pos;
  for (int i = 0; i < direction::DIRECTION_COUNT; i++)
  {
    config.sprites.at(i)->yPos(position.y_pos);
  }
  click_area.setPosition(position);
}
void Character::setSpawnPosition(float x_pos, float y_pos)
{
  config.spawn_pos = Point(x_pos, y_pos);
  position.x_pos = x_pos;
  position.y_pos = y_pos;
  for (int i = 0; i < direction::DIRECTION_COUNT; i++)
  {
    config.sprites.at(i)->xPos(position.x_pos);
    config.sprites.at(i)->yPos(position.y_pos);
  }
  click_area.setPosition(position);
}

/* Toggle visibility */
void Character::setVisible(bool is_visible)
{
  config.is_visible = is_visible;
}

/* Adjust movement speed */
void Character::setSpeed(int speed)
{
  config.movement_speed = speed;
}

/* Return the spawn limit for this character class */
int Character::getSpawnCap()
{
  return config.spawn_cap;
}

/* Check that we are visible for rendering */
bool Character::isVisible()
{
  return config.is_visible;
}

/* Return sprite */
ScaledSpriteArray* Character::getSprite()
{
  return config.sprites.at(getDirection());
}

/* Return renderer */
ASGE::Renderer* Character::getRenderer()
{
  return renderer;
}

/* Set the character ID */
void Character::setCharacterID(int index)
{
  config.id = "CV" + std::to_string(config.variant) + "I" + std::to_string(index);
  config.index = index;

  debug_text.print("SPAWNED NEW CHARACTER WITH ID " + config.id);
}

/* Get the character ID */
std::string Character::getCharacterID()
{
  return config.id;
}

/* Return the character index */
int Character::getIndex()
{
  return config.index;
}

/* Return the character type */
character_type Character::getCharacterType()
{
  return config.variant;
}

/* Get the character's current gauge */
float Character::getInternalGauge()
{
  return config.internal_gauge;
}

/* Reduce the character's current gauge */
void Character::reduceInternalGauge(float reduce_by)
{
  config.internal_gauge -= reduce_by;
}

/* Description of the internal gauge */
std::string Character::getInternalGaugeDesc()
{
  return config.internal_gauge_name;
}

/* Get display name */
std::string Character::getDisplayName()
{
  return config.display_name;
}

/* Finds the position to stand on to access the point of interest */
Point Character::findPositionForPOI(Point point, Room* room)
{
  float tile_size = (*room->getTiles())[0].getWidth();

  for (Tile& tile : *room->getTiles())
  {
    if (tile.getTileAccessibility() == tile_accessibility::TILE_IS_TRAVERSABLE)
    {
      // Check to see if this tile matches the position of up, down, left or right of the POI
      if ((tile.getTileAccessibility() == tile_accessibility::TILE_IS_TRAVERSABLE) &&
          ((tile.getPositionX() == point.x_pos && tile.getPositionY() == point.y_pos - tile_size) ||
           (tile.getPositionX() == point.x_pos && tile.getPositionY() == point.y_pos + tile_size) ||
           (tile.getPositionX() == point.x_pos + tile_size && tile.getPositionY() == point.y_pos) ||
           (tile.getPositionX() == point.x_pos - tile_size && tile.getPositionY() == point.y_pos)))
      {
        return Point(tile.getPositionX(), tile.getPositionY());
      }
    }
  }
  return Point(-1, -1);
}

Point Character::findPositionForPOI(Point point)
{
  for (Room& room : *global_map->getRooms())
  {
    for (Tile& tile : *room.getTiles())
    {
      float tile_size = tile.getWidth();
      if (tile.getTileAccessibility() == tile_accessibility::TILE_IS_TRAVERSABLE)
      {
        // Check to see if this tile matches the position of up, down, left or right of the POI
        if ((tile.getTileAccessibility() == tile_accessibility::TILE_IS_TRAVERSABLE) &&
            ((tile.getPositionX() == point.x_pos &&
              tile.getPositionY() == point.y_pos - tile_size) ||
             (tile.getPositionX() == point.x_pos &&
              tile.getPositionY() == point.y_pos + tile_size) ||
             (tile.getPositionX() == point.x_pos + tile_size &&
              tile.getPositionY() == point.y_pos) ||
             (tile.getPositionX() == point.x_pos - tile_size && tile.getPositionY() == point.y_pos)))
        {
          return Point(tile.getPositionX(), tile.getPositionY());
        }
      }
    }
  }
  return Point(-1, -1);
}

void Character::updateTimeBetweenFrames(double new_time)
{
    for (int i = 0; i < direction::DIRECTION_COUNT; i++)
    {
        config.sprites[i]->timeBetweenFrames(new_time);
    }
}