#include "CharacterManager.h"

/* Deallocate memory */
CharacterManager::~CharacterManager()
{
  /*
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
   */
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
      min_case = AllCharacterData<Boss>::data.count;
      max_case = sizeof(AllCharacterData<Boss>::data.instances);
      break;
    }
    case character_type::GOON:
    {
      min_case = AllCharacterData<Goon>::data.count;
      max_case = sizeof(AllCharacterData<Goon>::data.instances);
      break;
    }
    case character_type::TECHNICIAN:
    {
      min_case = AllCharacterData<LabTechnician>::data.count;
      max_case = sizeof(AllCharacterData<LabTechnician>::data.instances);
      break;
    }
    case character_type::SECURITY:
    {
      min_case = AllCharacterData<Security>::data.count;
      max_case = sizeof(AllCharacterData<Security>::data.instances);
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

/* Render all visible characters */
void CharacterManager::render(double delta_time)
{
  /*
  renderCharacter(boss_instances, boss_count, delta_time);
  renderCharacter(goon_instances, goon_count, delta_time);
  renderCharacter(technician_instances, technician_count, delta_time);
  renderCharacter(security_instances, security_count, delta_time);
   */
}
/* Render our specific character definition */
template<class CharacterArray>
void CharacterManager::renderCharacter(CharacterArray character,
                                       int& character_count,
                                       double& delta_time)
{
  for (int i = 0; i < character_count; i++)
  {
    if (character[i].isVisible())
    {
      camera->renderSprite(character[i].getSprite(), delta_time);
    }
  }
}

/* Update all characters */
void CharacterManager::update(double delta_time)
{
  /*
  updateCharacter(boss_instances, boss_count, delta_time);
  updateCharacter(goon_instances, goon_count, delta_time);
  updateCharacter(technician_instances, technician_count, delta_time);
  updateCharacter(security_instances, security_count, delta_time);
   */
}

/* Update a specific character definition */
template<class CharacterArray>
void CharacterManager::updateCharacter(CharacterArray character,
                                       int& character_count,
                                       double& delta_time)
{
  for (int i = 0; i < character_count; i++)
  {
    if (character[i].isVisible()) // Only bother updating if visible?
    {
      character[i].updatePosition(delta_time);
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



template<>
struct CharacterManager::AllCharacterData<Goon>
{
    typedef GoonData data;
};
template<>
struct CharacterManager::AllCharacterData<Boss>
{
    typedef BossData data;
};
template<>
struct CharacterManager::AllCharacterData<LabTechnician>
{
    typedef TechnicianData data;
};
template<>
struct CharacterManager::AllCharacterData<Security>
{
    typedef SecurityData data;
};