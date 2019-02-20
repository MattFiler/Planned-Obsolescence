#include "CharacterManager.h"

/* Deallocate memory */
CharacterManager::~CharacterManager()
{
  if (boss_count > 0)
  {
    delete[] boss_instances;
    boss_instances = nullptr;
  }
  if (goon_count > 0)
  {
    delete[] goon_instances;
    goon_instances = nullptr;
  }
  if (technician_count > 0)
  {
    delete[] technician_instances;
    technician_instances = nullptr;
  }
  if (security_count > 0)
  {
    delete[] security_instances;
    security_instances = nullptr;
  }
}

/* Check we can spawn a character type */
bool CharacterManager::canSpawn(character_type type)
{
  int min_case = 0;
  int max_case = 0;
  switch (type)
  {
    case character_type::BOSS:
    {
      min_case = boss_count;
      max_case = sizeof(boss_instances);
      break;
    }
    case character_type::GOON:
    {
      min_case = goon_count;
      max_case = sizeof(goon_instances);
      break;
    }
    case character_type::TECHNICIAN:
    {
      min_case = technician_count;
      max_case = sizeof(technician_instances);
      break;
    }
    case character_type::SECURITY:
    {
      min_case = security_count;
      max_case = sizeof(security_instances);
      break;
    }
    default:
    {
      return false;
    }
  }
  return (min_case < max_case);
}

/* Spawn a character */
bool CharacterManager::spawnCharacter(Boss* new_boss)
{
  // Create our array if it doesn't exist
  if (boss_instances == nullptr)
  {
    boss_instances = new Boss*[new_boss->getSpawnCap()];
  }

  // Spawn if we haven't exceeded our limits
  if (boss_count < new_boss->getSpawnCap())
  {
    boss_instances[boss_count] = new_boss;
    boss_instances[boss_count]->wake(renderer);
    boss_instances[boss_count]->setCharacterID(boss_count);
    boss_instances[boss_count]->generatePathfindingMap(game_map);

    boss_count++;
    return true;
  }

  // We've exceeded our spawn limits...
  return false;
}
bool CharacterManager::spawnCharacter(Goon* new_goon)
{
  // Create our array if it doesn't exist
  if (goon_instances == nullptr)
  {
    goon_instances = new Goon*[new_goon->getSpawnCap()];
  }

  // Spawn if we haven't exceeded our limits
  if (goon_count < new_goon->getSpawnCap())
  {
    goon_instances[goon_count] = new_goon;
    goon_instances[goon_count]->wake(renderer);
    goon_instances[goon_count]->setCharacterID(goon_count);
    goon_instances[goon_count]->generatePathfindingMap(game_map);
    goon_instances[goon_count]->registerRepairRequest = [&](Tile* tile) {
      this->registerRepairRequest(tile);
    };

    goon_count++;
    return true;
  }

  // We've exceeded our spawn limits...
  return false;
}
bool CharacterManager::spawnCharacter(LabTechnician* new_technician)
{
  // Create our array if it doesn't exist
  if (technician_instances == nullptr)
  {
    technician_instances = new LabTechnician*[new_technician->getSpawnCap()];
  }

  // Spawn if we haven't exceeded our limits
  if (technician_count < new_technician->getSpawnCap())
  {
    technician_instances[technician_count] = new_technician;
    technician_instances[technician_count]->wake(renderer);
    technician_instances[technician_count]->setCharacterID(technician_count);
    technician_instances[technician_count]->generatePathfindingMap(game_map);

    technician_count++;
    return true;
  }

  // We've exceeded our spawn limits...
  return false;
}
bool CharacterManager::spawnCharacter(Security* new_security)
{
  // Create our array if it doesn't exist
  if (security_instances == nullptr)
  {
    security_instances = new Security*[new_security->getSpawnCap()];
  }

  // Spawn if we haven't exceeded our limits
  if (security_count < new_security->getSpawnCap())
  {
    security_instances[security_count] = new_security;
    security_instances[security_count]->wake(renderer);
    security_instances[security_count]->setCharacterID(security_count);
    security_instances[security_count]->generatePathfindingMap(game_map);
    security_instances[security_count]->setupPatrolRoute();
    security_instances[security_count]->registerRepairRequest = [&](Tile* tile) {
      this->registerRepairRequest(tile);
    };
    security_count++;
    return true;
  }

  // We've exceeded our spawn limits...
  return false;
}

/* Render all visible characters */
void CharacterManager::render(double delta_time)
{
  renderCharacter(boss_instances, boss_count, delta_time);
  renderCharacter(goon_instances, goon_count, delta_time);
  renderCharacter(technician_instances, technician_count, delta_time);
  renderCharacter(security_instances, security_count, delta_time);
}

/* Render our specific character definition */
template<class CharacterArray>
void CharacterManager::renderCharacter(CharacterArray character,
                                       int& character_count,
                                       double& delta_time)
{
  for (int i = 0; i < character_count; i++)
  {
    if (character[i]->isVisible())
    {
      camera->renderSprite(character[i]->getSprite(), delta_time, render_index::CHARACTER_LAYER);
    }
  }
}

/* Update all characters */
void CharacterManager::update(double delta_time)
{
  updateCharacter(
    boss_instances, boss_count, boss_visible_count, boss_gauge_sum, boss_gauge_highest, delta_time);
  updateCharacter(
    goon_instances, goon_count, goon_visible_count, goon_gauge_sum, goon_gauge_highest, delta_time);
  updateCharacter(technician_instances,
                  technician_count,
                  technician_visible_count,
                  technician_gauge_sum,
                  technician_gauge_highest,
                  delta_time);
  updateCharacter(security_instances,
                  security_count,
                  security_visible_count,
                  security_gauge_sum,
                  security_gauge_highest,
                  delta_time);
}

/* Update a specific character definition */
template<class CharacterArray>
void CharacterManager::updateCharacter(CharacterArray character,
                                       int& char_c,
                                       int& char_visible_c,
                                       float& char_gauge,
                                       float& char_gauge_h,
                                       double& delta_time)
{
  char_visible_c = 0;
  char_gauge = 0;
  char_gauge_h = 0;
  for (int i = 0; i < char_c; i++)
  {
    if (character[i]->isVisible()) // Only bother updating if visible?
    {
      character[i]->update(delta_time);
      char_gauge += character[i]->getInternalGauge();
      if (character[i]->getInternalGauge() > char_gauge_h)
      {
        char_gauge_h = character[i]->getInternalGauge();
      }
      char_visible_c++;
    }
  }
  char_gauge /= static_cast<float>(char_visible_c);
}

/* Get sum gauge value for character */
float CharacterManager::getTotalGaugeValue(character_type character)
{
  switch (character)
  {
    case character_type::BOSS:
    {
      return boss_gauge_sum;
    }
    case character_type::GOON:
    {
      return goon_gauge_sum;
    }
    case character_type::TECHNICIAN:
    {
      return technician_gauge_sum;
    }
    case character_type::SECURITY:
    {
      return security_gauge_sum;
    }
    default:
    {
      return 0.0f;
    }
  }
}

/* Get sum gauge value for character */
float CharacterManager::getHighestGaugeValue(character_type character)
{
  switch (character)
  {
    case character_type::BOSS:
    {
      return boss_gauge_highest;
    }
    case character_type::GOON:
    {
      return goon_gauge_highest;
    }
    case character_type::TECHNICIAN:
    {
      return technician_gauge_highest;
    }
    case character_type::SECURITY:
    {
      return security_gauge_highest;
    }
    default:
    {
      return 0.0f;
    }
  }
}

/* Save a reference to the games current map */
void CharacterManager::setMap(GameMap* current_map)
{
  game_map = current_map;
}

/* Save a reference to the games camera and the renderer */
void CharacterManager::setCamera(Camera* scene_camera)
{
  camera = scene_camera;
  renderer = camera->getRenderer();
}

/* Returns true if any character lies within the passed point */
bool CharacterManager::checkForClick(Point click, bool act_on_click)
{
  bool boss_check = clickedCharacterCheck(boss_instances, boss_count, click, act_on_click);
  bool goon_check = clickedCharacterCheck(goon_instances, goon_count, click, act_on_click);
  bool technician_check =
    clickedCharacterCheck(technician_instances, technician_count, click, act_on_click);
  bool security_check =
    clickedCharacterCheck(security_instances, security_count, click, act_on_click);

  return (boss_check || goon_check || technician_check || security_check);
}

/* Check a set of characters to see if we clicked any */
template<class CharacterArray>
bool CharacterManager::clickedCharacterCheck(CharacterArray character,
                                             int& character_count,
                                             Point click,
                                             bool act_on_click)
{
  for (int i = 0; i < character_count; i++)
  {
    if (character[i]->isVisible())
    {
      if (character[i]->isPointInArea(click))
      {
        if (act_on_click)
        {
          ui_manager->updateAndShowCharacterInfo(character[i]->getDisplayName(),
                                                 character[i]->getInternalGauge(),
                                                 character[i]->getInternalGaugeDesc());
        }
        return true;
      }
    }
  }
  return false;
}

/* Registers a repair request with the technician with the shortest queue */
void CharacterManager::registerRepairRequest(Tile* tile)
{
  if (tile->getPointOfInterestState() == poi_state::POI_IS_BROKEN)
  {
    int index = 0;
    unsigned long long int shortest_queue = 1000;
    for (int i = 0; i < technician_count; i++)
    {
      if (technician_instances[i]->getRepairQueueLength() < shortest_queue)
      {
        index = i;
      }
    }
    technician_instances[index]->addRepairRequest(tile);
    tile->setPointOfInterestState(poi_state::POI_REPAIR_PENDING);
  }
}

/* Checks to see if security notices a sabotage */
void CharacterManager::sabotageAtPoint(Point point)
{
  for (int i = 0; i < security_count; i++)
  {
    // Get the distance between the security member and the sabotage
    float dist = Point::distanceBetween(security_instances[i]->getPosition(), point) / 50;
    // Then apply an amount with a square falloff
    float amount = 50.0f - (dist * dist);
    if (amount > 0)
    {
      if (amount + security_instances[i]->getInternalGauge() > 100)
      {
        amount = 100 - security_instances[i]->getInternalGauge();
      }
      security_instances[i]->reduceInternalGauge(-amount);
    }
  }
}