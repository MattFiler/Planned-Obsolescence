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
  if (min_case < max_case)
  {
    return true;
  }
  else
  {
    return false;
  }
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
    new_goon->wake(renderer);
    new_goon->setCharacterID(goon_count);
    new_goon->generatePathfindingMap(game_map);
    goon_instances[goon_count] = new_goon;
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
    new_technician->wake(renderer);
    new_technician->setCharacterID(technician_count);
    new_technician->generatePathfindingMap(game_map);
    technician_instances[technician_count] = new_technician;
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
    new_security->wake(renderer);
    new_security->setCharacterID(security_count);
    new_security->generatePathfindingMap(game_map);
    security_instances[security_count] = new_security;
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
      camera->renderSprite(character[i]->getSprite(), delta_time);
    }
  }
}

/* Update all characters */
void CharacterManager::update(double delta_time)
{
  updateCharacter(boss_instances, boss_count, delta_time);
  updateCharacter(goon_instances, goon_count, delta_time);
  updateCharacter(technician_instances, technician_count, delta_time);
  updateCharacter(security_instances, security_count, delta_time);
}

/* Update a specific character definition */
template<class CharacterArray>
void CharacterManager::updateCharacter(CharacterArray character,
                                       int& character_count,
                                       double& delta_time)
{
  for (int i = 0; i < character_count; i++)
  {
    if (character[i]->isVisible()) // Only bother updating if visible?
    {
      character[i]->updatePosition(delta_time);
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