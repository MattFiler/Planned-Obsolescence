#include "GameCore.h"
#include "../Constants.h"
#include "../Core/DynamicSprite.h"
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Renderer.h>

#include "../Map/Room.h"

/**
 *   @brief   Loads all variables and sprites for this scene
 *   @details Initialises all variables and creates all the new
                         sprites for the scene
 */
bool GameCore::load(ASGE::Renderer* renderer, ASGE::Input* input, json core_config)
{
  renderer->setClearColour(ASGE::COLOURS::BLACK);
  rend = renderer;

  game_map.load(renderer);

  // generatePathfindingMap();

  spawnCharacters(renderer);

  return true;
}

void GameCore::generatePathfindingMap()
{
  int total_tiles = 0;
  for (int i = 0; i < game_map.getRoomCount(); i++)
  {
    total_tiles += game_map.getRooms()[i].getTileCount();
  }

  pathfinding_map.nodes = new PathNode[total_tiles];

  // First populate the map with the positions of each node
  int tile_count = 0;
  for (int i = 0; i < game_map.getRoomCount(); i++)
  {
    for (int j = 0; j < game_map.getRooms()[i].getTileCount(); j++)
    {
      pathfinding_map.nodes[tile_count].position =
        Point(game_map.getRooms()[i].getTiles()[j].getPositionX(),
              game_map.getRooms()[i].getTiles()[j].getPositionY());
      tile_count++;
    }
  }

  // Then loop through a second time to add the connections between nodes
  tile_count = 0;
  float tile_size = game_map.getRooms()[0].getTiles()[0].getWidth();
  for (int i = 0; i < game_map.getRoomCount(); i++)
  {
    for (int j = 0; j < game_map.getRooms()[i].getTileCount(); j++)
    {
      if (game_map.getRooms()[i].getTiles()[j].exitIsValid(direction::LEFT))
      {
        pathfinding_map.nodes[tile_count].connections[0].node =
          findNodeAtPoint(pathfinding_map.nodes[tile_count].position - Point(tile_size, 0));
      }
      else if (game_map.getRooms()[i].getTiles()[j].exitIsValid(direction::RIGHT))
      {
        pathfinding_map.nodes[tile_count].connections[0].node =
          findNodeAtPoint(pathfinding_map.nodes[tile_count].position + Point(tile_size, 0));
      }
      else if (game_map.getRooms()[i].getTiles()[j].exitIsValid(direction::UP))
      {
        pathfinding_map.nodes[tile_count].connections[0].node =
          findNodeAtPoint(pathfinding_map.nodes[tile_count].position - Point(0, tile_size));
      }
      else if (game_map.getRooms()[i].getTiles()[j].exitIsValid(direction::DOWN))
      {
        pathfinding_map.nodes[tile_count].connections[0].node =
          findNodeAtPoint(pathfinding_map.nodes[tile_count].position + Point(0, tile_size));
      }
      tile_count++;
    }
  }
}

/* Returns the node in the PathfindingMap that is at the given point */
PathNode* GameCore::findNodeAtPoint(Point point)
{
  for (int i = 0; i < pathfinding_map.number_of_nodes; i++)
  {
    if (pathfinding_map.nodes[i].position == point)
    {
      return &pathfinding_map.nodes[i];
    }
  }
  return nullptr;
}

/* Spawn all characters */
void GameCore::spawnCharacters(ASGE::Renderer* renderer)
{
  Boss boss_demo;
  boss_demo.wake(renderer);
  boss_demo.setSpawnPosition(0, 0);
  // boss_demo.calculateRouteToPoint(Point(300, 300));
  character_manager.spawn(boss_demo);
}

/**
 *   @brief   Changes game state based on inputs
 *   @details Is called for every input event and will change
 *   @details the game state / variables etc depending
 *   @param   data is the event
 */
void GameCore::keyHandler(const ASGE::SharedEventData data) {}

/**
 *   @brief   Changes game state based on mouse inputs
 *   @details Is called for every input event and will change
 *            the game state / variables etc depending
 *   @param   data is the event, mouse_position the position of the cursor
 */
void GameCore::mouseHandler(const ASGE::SharedEventData data, Vector mouse_position) {}

/**
 *   @brief   Updates all variables for this scene
 *   @details Runs every frame and handles all the logic and updates
 *			 of the active scene
 *   @param  delta_time is time since last update
 *   @return  number of the scene to switch to, -1 no change, -2 exit game
 */
int GameCore::update(double delta_time)
{
  return next_scene;
}

/**
 *   @brief   Renders all sprites for this scene
 *   @details Runs every frame and draws all the sprites in
 * 			 order
 */
void GameCore::render(double delta_time)
{
  rend->renderText("THE GAME", 100, 100, ASGE::COLOURS::RED);

  // Render Map
  game_map.render();

  // Render Characters
  character_manager.render(delta_time, rend);
}