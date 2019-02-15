#ifndef PLANNEDOBSOLESCENCE_PROGRESSBAR_H
#define PLANNEDOBSOLESCENCE_PROGRESSBAR_H

#include "../Constants.h"
#include "../Sprites/ScaledSpriteArray.h"
#include "UI.h"

/* A self contained progress bar that once set only needs render to be called and progress to be
 * updated */
class ProgressBar : public UI
{
 public:
  ProgressBar() = default;
  explicit ProgressBar(Point pos,
                       ASGE::Renderer* rend,
                       float bar_width = 100,
                       float bar_height = 20,
                       int direction = rotation::LEFT_TO_RIGHT,
                       Point _fill_padding = Point(5, 5));
  ~ProgressBar() override = default;

  void render(double delta_time) override;

  void addBackgroundSprite(ScaledSpriteArray* sprite);
  void addFillSprite(ScaledSpriteArray* sprite);

  void addProgress(float delta);
  float getProgress() { return bar_progress; };

 private:
  float width = 0;
  float height = 0;
  float bar_progress = 0; // Represents a percentage between 0 and 1
  Point fill_padding = Point(0, 0);
  bool horizontal = true;

  ScaledSpriteArray* background_sprite = nullptr;
  ScaledSpriteArray* fill_sprite = nullptr;
};

#endif // PLANNEDOBSOLESCENCE_PROGRESSBAR_H
