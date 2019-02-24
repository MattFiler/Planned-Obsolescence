#ifndef PLANNEDOBSOLESCENCE_TUTORIALCORE_H
#define PLANNEDOBSOLESCENCE_TUTORIALCORE_H

#include "../Sprites/ScaledSpriteArray.h"
#include "../UI/Menu.h"
#include "Scene.h"

namespace ASGE
{
class Renderer;
}

/**
 **   The first scene of the game, displays logos
 */
class TutorialCore : public Scene
{
 public:
  TutorialCore() = default;
  ~TutorialCore() = default;
  bool load(ASGE::Renderer* renderer, ASGE::Input* input, SoLoud::Soloud& player) override;
  scenes update(double delta_time) override;
  void render(double delta_time) override;
  void keyHandler(const ASGE::SharedEventData data) override;
  void mouseHandler(const ASGE::SharedEventData data, Point mouse_position) override;

 private:
  ScaledSpriteArray* tutorial_slides = nullptr;
  GetLocalisedString localiser;
  int tutorial_index = 0;
  int tutorial_slide_count = 29;
};

#endif // PLANNEDOBSOLESCENCE_TUTORIALCORE_H
