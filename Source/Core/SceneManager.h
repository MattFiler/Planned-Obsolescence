//
// Created by tobyj on 15/01/2019.
//

#ifndef PLANNEDOBSOLESCENCE_SCENEMANAGER_H
#define PLANNEDOBSOLESCENCE_SCENEMANAGER_H
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <memory>

#include "Geometry.h"
#include "Scene.h"

namespace ASGE
{
class Renderer;
struct EventData;
}

/**
 *  Stores all of the games scenes and handles loading and unloading them
 */
class SceneManager
{
  public:
  SceneManager();
  ~SceneManager();

  // Changes the active scene to the passed scene
  bool loadCurrentScene(ASGE::Renderer* renderer, ASGE::Input* input);
  int updateCurrentScene(double delta_time);
  void renderCurrentScene(double delta_time);
  void sceneKeyHandler(const ASGE::SharedEventData data);
  void sceneMouseHandler(const ASGE::SharedEventData data, Vector mouse_position);

  Scene* current_scene = nullptr;
};

#endif // PLANNEDOBSOLESCENCE_SCENEMANAGER_H
