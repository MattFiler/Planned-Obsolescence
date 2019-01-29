#include "DynamicSprite.h"

/**
 *   @brief   Creates an DynamicSprite with set size
 *   @details num_of_sprites is the number of contained ASGE::Sprite's
 */
DynamicSprite::DynamicSprite(int num_of_sprites, bool should_flipbook)
{
  my_sprites = new ASGE::Sprite*[num_of_sprites];
  auto_anim = should_flipbook;
}

/**
 *   @brief   Default Deconstructor.
 */
DynamicSprite::~DynamicSprite()
{
  if (my_sprites)
  {
    for (int i = 0; i < number_of_sprites; i++)
    {
      if (my_sprites[i])
      {
        delete my_sprites[i];
        my_sprites[i] = nullptr;
      }
    }
    my_sprites = nullptr;
  }
}

/**
 *   @brief   Adds a sprite to the object
 *   @details Adds a new ASGE::Sprite to this DynamicSprite,
 *            also intializes the position, height and width
 *            if this is the first sprite to be added
 *   @param	 Adress of new sprite
 */
void DynamicSprite::addSprite(ASGE::Sprite& new_sprite)
{
  my_sprites[number_of_sprites] = &new_sprite;
  if (number_of_sprites == 0)
  {
    sprite_height = new_sprite.height();
    sprite_width = new_sprite.width();
  }
  new_sprite.scale(width_scale);
  number_of_sprites++;
}

/**
 *   @brief   Get the x position of sprite
 *   @details Gets the x position of ASGE::Sprite,
 *			 this should be in the displayed world position
 *   @return  The x position of sprite
 */
float DynamicSprite::xPos()
{
  return my_sprites[0]->xPos();
}

/**
 *   @brief   Get the y position of sprite
 *   @details Gets the y position of ASGE::Sprite,
 *			 this should be in the displayed world position
 *   @return  The y position of sprite
 */
float DynamicSprite::yPos()
{
  return my_sprites[0]->yPos();
}

/**
 *   @brief   Sets the x position of sprite(s)
 *   @details Sets the x position of all attached sprites
 *   @param   The new x position for the sprite(s)
 */
void DynamicSprite::xPos(float new_x)
{
  for (int i = 0; i < number_of_sprites; i++)
  {
    my_sprites[i]->xPos(new_x * width_scale);
  }
}

/* Adds an amount to the current x_position contained sprites */
void DynamicSprite::addX(float x_amount)
{
    for (int i = 0; i < number_of_sprites; i++)
    {
        my_sprites[i]->xPos(my_sprites[i]->xPos() + x_amount);
    }
}

/* Adds an amount to the current y_position contained sprites */
void DynamicSprite::addY(float y_amount)
{
    for (int i = 0; i < number_of_sprites; i++)
    {
        my_sprites[i]->yPos(my_sprites[i]->yPos() + y_amount);
    }
}

/**
 *   @brief   Sets the y position of sprite(s)
 *   @details Sets the y position of all attached sprites
 *   @param  The new y position for the sprite(s)
 */
void DynamicSprite::yPos(float new_y)
{
  for (int i = 0; i < number_of_sprites; i++)
  {
    my_sprites[i]->yPos(new_y * width_scale);
  }
}

/**
 *   @brief   Gets the scale of sprite(s)
 *   @details Gets the scale of the DynamicSprite, this is the scale
 *            of the displayed world
 *   @return  The sprites scale
 */
float DynamicSprite::scale()
{
  return scale_factor;
}

/**
 *   @brief   Get the width of sprite
 *   @details Gets the width of the DynamicSprite,
 *			 read only - use scale to alter size
 *   @return  The width of sprite
 */
float DynamicSprite::width()
{
  return sprite_width * scale_factor;
}

/**
 *   @brief   Get the height of sprite
 *   @details Gets the height of the DynamicSprite,
 *			 read only - use scale to alter size
 *   @return  The height of sprite
 */
float DynamicSprite::height()
{
  return sprite_height * scale_factor;
}

/**
 *   @brief   Sets the scale of sprite(s)
 *   @details Sets the scale of DynamicSprite,
 *			 this scale is automatically applied and
 *			 scaled to the scale of all contained sprites
 *   @param   The new scale for the sprite(s)
 */
void DynamicSprite::scale(float scale_amount)
{
  scale_factor = scale_amount * width_scale;
  for (int i = 0; i < number_of_sprites; i++)
  {
    my_sprites[i]->scale(scale_factor);
  }
}

/**
 *   @brief   Sets the fade colour
 *   @details Sets the fade colour of DynamicSprite,
 *			 this is the colour of tint applied when using fadeToColour
 *   @param   The new fade colour
 */
void DynamicSprite::setFadeColour(ASGE::Colour col)
{
  fade_colour = col;
}

/**
 *   @brief   Fades sprite to target colour
 *   @details This function applies a tint to the sprite each time it is called
 *            fully colouring it after time_to_fade ms
 *   @param   time_to_fade is the time it will take to fully tint
 *   @param   delta_time is the time since last tick
 *   @param   inverse_fade will remove tint instead
 */
bool DynamicSprite::fadeToColour(double time_to_fade, double delta_time, bool inverse_fade)
{
  if (inverse_fade)
  {
    if (fade_percent == 0)
    {
      return true;
    }
    // Calculate the amount of fade to be applied based on time passed
    fade_percent -= static_cast<float>(delta_time) / static_cast<float>(time_to_fade);
    if (fade_percent <= 0)
    {
      fade_percent = 0;
    }
  }
  else
  {
    if (fade_percent == 1)
    {
      return true;
    }
    // Calculate the amount of fade to be applied based on time passed
    fade_percent += static_cast<float>(delta_time) / static_cast<float>(time_to_fade);
    if (fade_percent >= 1)
    {
      fade_percent = 1;
    }
  }

  ASGE::Colour new_col = ASGE::COLOURS::WHITE;
  new_col.r = (fade_colour.r) * fade_percent;
  new_col.g = (fade_colour.g) * fade_percent;
  new_col.b = (fade_colour.b) * fade_percent;
  for (int i = 0; i < number_of_sprites; i++)
  {
    my_sprites[i]->colour(new_col);
  }
  return false;
}

/**
 *   @brief   Gets the next frame of the sprite
 *   @details Sets the current step of animation to next step or the first
 *			 step if the animation is over if enough time has passed
 *   @param   delta_time is time since last call
 *   @return  The next sprite of the animation
 */
ASGE::Sprite& DynamicSprite::returnNextSprite(double delta_time)
{
  if (auto_anim)
  {
    time_passed += delta_time;
    if (time_passed > time_between_frames)
    {
      current_sprite++;
      time_passed -= time_between_frames;
    }

    if (current_sprite == number_of_sprites)
    {
      current_sprite = 0;
    }
  }
  return *my_sprites[current_sprite];
}

float DynamicSprite::width_scale = 1;