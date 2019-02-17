#ifndef PO_ANIMSPRITE
#define PO_ANIMSPRITE

#include <Engine/Sprite.h>

/**
 *  Component which contains an array of sprites which can be animated with its
 *  methods. Also contains other useful functionality such as scaling
 *  Animated sprites have their position and scale set to the base game
 *  resolution, this is referred to as the simulated world
 *  When retrieving the ASGE::Sprite from the DynamicSprite it will give the
 *  position and scale based on what the set screen resolution is, this is
 *  referred to as the displayed world. No manual conversion is necessary,
 *  just set the static field width_scale at run time and only use
 *  ASGE::Sprites through an DynamicSprite component
 */
class ScaledSpriteArray
{
 public:
  explicit ScaledSpriteArray(unsigned int num_of_sprites = 1, bool should_flipbook = true);
  ~ScaledSpriteArray();

  ScaledSpriteArray(const ScaledSpriteArray&) = delete;
  ScaledSpriteArray& operator=(const ScaledSpriteArray&) = delete;

  void xPos(float new_x);
  float xPos();
  void addX(float x_amount);
  void yPos(float new_y);
  float yPos();
  void addY(float y_amount);
  float scale();
  void scale(float new_scale);
  float width();
  float height();
  void setWidth(float new_width);
  void setHeight(float new_height);
  void setRotation(float new_rotation);
  void timeBetweenFrames(double new_time_between_frames);
  void setFadeColour(ASGE::Colour col);
  void setCurrentSprite(int new_sprite_index);

  void setColour(ASGE::Colour col);

  void setSpriteSheet(float sprite_sheet_width,
                      float sprite_sheet_height,
                      float start_x_pos = 0,
                      float start_y_pos = 0);

  void addSprite(ASGE::Sprite& new_sprite);
  bool fadeToColour(double time_to_fade, double delta_time, bool inverse_fade = false);
  ASGE::Sprite& returnNextSprite(double delta_time);

  bool fadeIn(double time_to_fade, double delta_time);
  bool fadeOut(double time_to_fade, double delta_time);

  static float width_scale; /**< The scale difference between actual and base width */

  int numberOfSprites();

 private:
  float sprite_width = 50;
  float sprite_height = 50;
  float scale_factor = 1;
  float colour_fade_percent = 0;
  float opacity_fade_percent = 0;
  float rotation = 0;
  double time_passed = 0;
  double time_between_frames = 0;
  bool auto_anim = false;
  int number_of_sprites = 0;
  int current_sprite = 0;
  float src_rect[4]{ 0, 0, 0, 0 };

  ASGE::Colour fade_colour = ASGE::COLOURS::WHITE;
  ASGE::Sprite** my_sprites = nullptr;
};

#endif