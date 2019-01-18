#include "CharacterManager.h"

/* Deallocate memory */
CharacterManager::~CharacterManager()
{
  delete bosses;
  bosses = nullptr;

  delete goons;
  goons = nullptr;

  delete techies;
  techies = nullptr;

  delete guards;
  guards = nullptr;
}

/* Spawn a boss */
bool CharacterManager::spawnBoss(Boss& new_boss)
{
  // Set up our array length
  if (bosses == nullptr)
  {
    bosses = new Boss[new_boss.getSpawnCap()];
  }

  // Spawn a boss if we haven't exceeded our limits
  if (boss_count < new_boss.getSpawnCap())
  {
    bosses[boss_count] = new_boss;
    boss_count++;
    return true;
  }

  // We've exceeded our spawn limits...
  return false;
}

/* Spawn a goon */
bool CharacterManager::spawnGoon(Goon& new_goon)
{
  // Set up our array length
  if (goons == nullptr)
  {
    goons = new Goon[new_goon.getSpawnCap()];
  }

  // Spawn a goon if we haven't exceeded our limits
  if (goon_count < new_goon.getSpawnCap())
  {
    goons[goon_count] = new_goon;
    goon_count++;
    return true;
  }

  // We've exceeded our spawn limits...
  return false;
}

/* Spawn a technician */
bool CharacterManager::spawnTechnician(LabTechnician& new_techie)
{
  // Set up our array length
  if (techies == nullptr)
  {
    techies = new LabTechnician[new_techie.getSpawnCap()];
  }

  // Spawn a technician if we haven't exceeded our limits
  if (techie_count < new_techie.getSpawnCap())
  {
    techies[techie_count] = new_techie;
    techie_count++;
    return true;
  }

  // We've exceeded our spawn limits...
  return false;
}

/* Spawn a security guard */
bool CharacterManager::spawnGuard(Security& new_guard)
{
  // Set up our array length
  if (guards == nullptr)
  {
    guards = new Security[new_guard.getSpawnCap()];
  }

  // Spawn a guard if we haven't exceeded our limits
  if (guard_count < new_guard.getSpawnCap())
  {
    guards[guard_count] = new_guard;
    guard_count++;
    return true;
  }

  // We've exceeded our spawn limits...
  return false;
}

/* Render all visible characters */
void CharacterManager::renderAll(double delta_time, ASGE::Renderer* renderer)
{
  renderBosses(delta_time, renderer);
  renderGoons(delta_time, renderer);
  renderTechnicians(delta_time, renderer);
  renderSecurity(delta_time, renderer);
}

/* Render our bosses */
void CharacterManager::renderBosses(double delta_time, ASGE::Renderer* renderer)
{
  for (int i = 0; i < boss_count; i++)
  {
    if (bosses[i].isVisible())
    {
      renderer->renderSprite(bosses[i].getSprite()->returnNextSprite(delta_time));
    }
  }
}

/* Render our goons */
void CharacterManager::renderGoons(double delta_time, ASGE::Renderer* renderer)
{
  for (int i = 0; i < goon_count; i++)
  {
    if (goons[i].isVisible())
    {
      renderer->renderSprite(goons[i].getSprite()->returnNextSprite(delta_time));
    }
  }
}

/* Render our technicians */
void CharacterManager::renderTechnicians(double delta_time, ASGE::Renderer* renderer)
{
  for (int i = 0; i < techie_count; i++)
  {
    if (techies[i].isVisible())
    {
      renderer->renderSprite(techies[i].getSprite()->returnNextSprite(delta_time));
    }
  }
}

/* Render our security guards */
void CharacterManager::renderSecurity(double delta_time, ASGE::Renderer* renderer)
{
  for (int i = 0; i < guard_count; i++)
  {
    if (guards[i].isVisible())
    {
      renderer->renderSprite(guards[i].getSprite()->returnNextSprite(delta_time));
    }
  }
}
