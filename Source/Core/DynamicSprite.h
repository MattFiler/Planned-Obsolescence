#ifndef PO_ANIMSPRITE
#define PO_ANIMSPRITE

#include "Geometry.h"
#include <Engine/Sprite.h>

/**
 *  Component which contains an array of sprites which can be animated with its
 *  methods. Also contains other useful functionality such as scaling
 *  Animated sprites have their position and scale set to the base game
 *  resolution, this is referred to as the simulated world
 *  When retrieving the ASGE::Sprite from the AnimatedSprite it will give the
 *  position and scale based on what the set screen resolution is, this is
 *  referred to as the displayed world. No manual conversion is necessary,
 *  just set the static field width_scale at run time and only use
 *  ASGE::Sprites through an AnimatedSprite component
 *  Position is automatically updated with the GameObjects position that
 *  this is attached to.
 */
class DynamicSprite
{
 public:
  DynamicSprite(int num_of_sprites = 1, bool should_flipbook = true);
  ~DynamicSprite();

  // TODO: Does your memory shallow copy correctly?
  DynamicSprite(const DynamicSprite&) = delete;
  DynamicSprite& operator=(const DynamicSprite&) = delete;

  void xPos(float new_x);
  float xPos();
  void yPos(float new_y);
  float yPos();
  float scale();
  void scale(float new_scale);
  float width();
  float height();

  void setFadeColour(ASGE::Colour col);

  void addSprite(ASGE::Sprite& new_sprite);
  bool fadeToColour(double time_to_fade, double delta_time, bool inverse_fade = false);
  ASGE::Sprite& returnNextSprite(double delta_time);

  static float width_scale; /**< The scale difference between actual and base width */

 private:
  float sprite_width = 50;
  float sprite_height = 50;
  float scale_factor = 1;
  float fade_percent = 0;
  double time_passed = 0;
  double time_between_frames = 0;
  bool auto_anim = false;
  int number_of_sprites = 0;
  int current_sprite = 0;

  ASGE::Colour fade_colour = ASGE::COLOURS::WHITE;
  ASGE::Sprite** my_sprites = nullptr;
};

#endif