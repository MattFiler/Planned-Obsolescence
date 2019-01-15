//
// Created by tobyj on 15/01/2019.
//

#ifndef PLANNEDOBSOLESCENCE_SCENE_H
#define PLANNEDOBSOLESCENCE_SCENE_H
#include "Geometry.h"
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine\Colours.h>
#include <memory>

namespace ASGE
{
class Renderer;
struct EventData;
}

/**
 *  Holds all of the data and update code for a scene
 */
class Scene
{
  public:
  Scene() = default;
  virtual ~Scene() = default;
  virtual bool load(ASGE::Renderer* renderer, ASGE::Input* input) = 0;
  virtual int update(double delta_time) = 0;
  virtual void render(double delta_time) = 0;
  virtual void keyHandler(const ASGE::SharedEventData data) = 0;
  virtual void mouseHandler(const ASGE::SharedEventData data, Vector mouse_position) = 0;

  protected:
  int next_scene = -1;
  ASGE::Colour clear_colour = ASGE::COLOURS::BLACK;
  ASGE::Renderer* rend = nullptr;
};
#endif // PLANNEDOBSOLESCENCE_SCENE_H
