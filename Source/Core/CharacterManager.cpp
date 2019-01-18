#include "CharacterManager.h"

CharacterManager::CharacterManager()
{

}

/* Spawn a boss */
bool CharacterManager::spawnBoss(Boss &new_boss)
{
  // Spawn a boss if we haven't exceeded our limits
  if (boss_count < new_boss.getSpawnCap())
  {
    bosses[boss_count] = &new_boss;
    boss_count++;
    return true;
  }
  // We've exceeded our spawn limits...
  return false;
}

/* Spawn a goon */
bool CharacterManager::spawnGoon(Goon &new_goon)
{
  // Spawn a goon if we haven't exceeded our limits
  if (goon_count < new_goon.getSpawnCap())
  {
    goons[goon_count] = &new_goon;
    goon_count++;
    return true;
  }
  // We've exceeded our spawn limits...
  return false;
}

/* Spawn a technician */
bool CharacterManager::spawnTechnician(LabTechnician &new_techie)
{
  // Spawn a technician if we haven't exceeded our limits
  if (techie_count < new_techie.getSpawnCap())
  {
    techies[techie_count] = &new_techie;
    techie_count++;
    return true;
  }
  // We've exceeded our spawn limits...
  return false;
}

/* Spawn a security guard */
bool CharacterManager::spawnGuard(Security &new_guard)
{
  // Spawn a guard if we haven't exceeded our limits
  if (guard_count < new_guard.getSpawnCap())
  {
    guards[guard_count] = &new_guard;
    guard_count++;
    return true;
  }
  // We've exceeded our spawn limits...
  return false;
}