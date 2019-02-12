#include "CharacterManager.h"

/* Deallocate memory */
CharacterManager::~CharacterManager()
{
  if (boss_count > 0)
  {
    delete[] bosses;
    bosses = nullptr;
  }
  if (goon_count > 0)
  {
    delete[] goons;
    goons = nullptr;
  }
  if (techie_count > 0)
  {
    delete[] techies;
    techies = nullptr;
  }
  if (guard_count > 0)
  {
    delete[] guards;
    guards = nullptr;
  }
}

/* Spawn a boss */
bool CharacterManager::spawn(Boss& new_boss)
{
  // Set up our array length
  if (bosses == nullptr)
  {
    bosses = new Boss[new_boss.getSpawnCap()];
  }

  // Spawn a boss if we haven't exceeded our limits
  if (boss_count < new_boss.getSpawnCapAsInt())
  {
    new_boss.setCharacterID(boss_count);
    bosses[boss_count] = new_boss;
    bosses[boss_count].generatePathfindingMap(game_map);
    bosses[boss_count].calculateRouteToPoint(Point(300, 300)); // TEMP CODE FOR TESTING
    boss_count++;
    return true;
  }

  // We've exceeded our spawn limits...
  return false;
}

/* Spawn a goon */
bool CharacterManager::spawn(Goon& new_goon)
{
  // Set up our array length
  if (goons == nullptr)
  {
    goons = new Goon[new_goon.getSpawnCap()];
  }

  // Spawn a goon if we haven't exceeded our limits
  if (goon_count < new_goon.getSpawnCapAsInt())
  {
    new_goon.setCharacterID(goon_count);
    goons[goon_count] = new_goon;
    goon_count++;
    return true;
  }

  // We've exceeded our spawn limits...
  return false;
}

/* Spawn a technician */
bool CharacterManager::spawn(LabTechnician& new_techie)
{
  // Set up our array length
  if (techies == nullptr)
  {
    techies = new LabTechnician[new_techie.getSpawnCap()];
  }

  // Spawn a technician if we haven't exceeded our limits
  if (techie_count < new_techie.getSpawnCapAsInt())
  {
    new_techie.setCharacterID(techie_count);
    techies[techie_count] = new_techie;
    techie_count++;
    return true;
  }

  // We've exceeded our spawn limits...
  return false;
}

/* Spawn a security guard */
bool CharacterManager::spawn(Security& new_guard)
{
  // Set up our array length
  if (guards == nullptr)
  {
    guards = new Security[new_guard.getSpawnCap()];
  }

  // Spawn a guard if we haven't exceeded our limits
  if (guard_count < new_guard.getSpawnCapAsInt())
  {
    new_guard.setCharacterID(guard_count);
    guards[guard_count] = new_guard;
    guard_count++;
    return true;
  }

  // We've exceeded our spawn limits...
  return false;
}

/* Render all visible characters */
void CharacterManager::render(double delta_time)
{
  renderBosses(delta_time);
  renderGoons(delta_time);
  renderTechnicians(delta_time);
  renderSecurity(delta_time);
}

/* Render our bosses */
void CharacterManager::renderBosses(double delta_time)
{
  for (int i = 0; i < boss_count; i++)
  {
    if (bosses[i].isVisible())
    {
      camera->renderSprite(bosses[i].getSprite(), delta_time);
    }
  }
}

/* Render our goons */
void CharacterManager::renderGoons(double delta_time)
{
  for (int i = 0; i < goon_count; i++)
  {
    if (goons[i].isVisible())
    {
      camera->renderSprite(goons[i].getSprite(), delta_time);
    }
  }
}

/* Render our technicians */
void CharacterManager::renderTechnicians(double delta_time)
{
  for (int i = 0; i < techie_count; i++)
  {
    if (techies[i].isVisible())
    {
      camera->renderSprite(techies[i].getSprite(), delta_time);
    }
  }
}

/* Render our security guards */
void CharacterManager::renderSecurity(double delta_time)
{
  for (int i = 0; i < guard_count; i++)
  {
    if (guards[i].isVisible())
    {
      camera->renderSprite(guards[i].getSprite(), delta_time);
    }
  }
}

/* Update all characters */
void CharacterManager::update(double delta_time)
{
  // TODO: Add all update ticks, much like for render, just adding this one here to test
  bosses[0].updatePosition(delta_time);
}

/* Save a reference to the games current map */
void CharacterManager::setMap(GameMap* current_map)
{
  game_map = current_map;
}

/* Save a reference to the games camera */
void CharacterManager::setCamera(Camera* scene_camera)
{
  camera = scene_camera;
}
