#include "ScaledSpriteArray.h"

/**
 *   @brief   Creates an DynamicSprite with set size
 *   @details num_of_sprites is the number of contained ASGE::Sprite's
 */
ScaledSpriteArray::ScaledSpriteArray(unsigned int num_of_sprites, bool should_flipbook)
{
  my_sprites = new ASGE::Sprite*[num_of_sprites];
  auto_anim = should_flipbook;
}

/**
 *   @brief   Default Deconstructor.
 */
ScaledSpriteArray::~ScaledSpriteArray()
{
  delete[] my_sprites;
  my_sprites = nullptr;
}

/**
 *   @brief   Adds a sprite to the object
 *   @details Adds a new ASGE::Sprite to this DynamicSprite,
 *            also intializes the position, height and width
 *            if this is the first sprite to be added
 *   @param	 Adress of new sprite
 */
void ScaledSpriteArray::addSprite(ASGE::Sprite& new_sprite)
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
float ScaledSpriteArray::xPos()
{
  return my_sprites[0]->xPos();
}

/**
 *   @brief   Get the y position of sprite
 *   @details Gets the y position of ASGE::Sprite,
 *			 this should be in the displayed world position
 *   @return  The y position of sprite
 */
float ScaledSpriteArray::yPos()
{
  return my_sprites[0]->yPos();
}

/**
 *   @brief   Sets the x position of sprite(s)
 *   @details Sets the x position of all attached sprites
 *   @param   The new x position for the sprite(s)
 */
void ScaledSpriteArray::xPos(float new_x)
{
  for (int i = 0; i < number_of_sprites; i++)
  {
    my_sprites[i]->xPos(new_x * width_scale);
  }
}

/* Adds an amount to the current x_position contained sprites */
void ScaledSpriteArray::addX(float x_amount)
{
  for (int i = 0; i < number_of_sprites; i++)
  {
    my_sprites[i]->xPos(my_sprites[i]->xPos() + x_amount);
  }
}

/* Adds an amount to the current y_position contained sprites */
void ScaledSpriteArray::addY(float y_amount)
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
void ScaledSpriteArray::yPos(float new_y)
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
float ScaledSpriteArray::scale()
{
  return scale_factor;
}

/**
 *   @brief   Get the width of sprite
 *   @details Gets the width of the DynamicSprite,
 *			 read only - use scale to alter size
 *   @return  The width of sprite
 */
float ScaledSpriteArray::width()
{
  return sprite_width * scale_factor;
}

/**
 *   @brief   Get the height of sprite
 *   @details Gets the height of the DynamicSprite,
 *			 read only - use scale to alter size
 *   @return  The height of sprite
 */
float ScaledSpriteArray::height()
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
void ScaledSpriteArray::scale(float scale_amount)
{
  scale_factor = scale_amount * width_scale;
  for (int i = 0; i < number_of_sprites; i++)
  {
    my_sprites[i]->scale(scale_factor);
  }
}

/**
 *   @brief   Sets the width of sprite(s)
 *   @details Sets the width of DynamicSprite,
 *			 this width is automatically applied
 *			 to the width of all contained sprites
 *   @param   The new width for the sprite(s)
 */
void ScaledSpriteArray::setWidth(float new_width)
{
  sprite_width = new_width;
  for (int i = 0; i < number_of_sprites; ++i)
  {
    my_sprites[i]->width(sprite_width * scale_factor);
  }
}

/**
 *   @brief   Sets the height of sprite(s)
 *   @details Sets the height of DynamicSprite,
 *			 this height is automatically applied
 *			 to the height of all contained sprites
 *   @param   The new height for the sprite(s)
 */
void ScaledSpriteArray::setHeight(float new_height)
{
  sprite_height = new_height;
  for (int i = 0; i < number_of_sprites; ++i)
  {
    my_sprites[i]->height(sprite_height * scale_factor);
  }
}

/* Sets the rotation of this sprite to the passed argument (in radians) */
void ScaledSpriteArray::setRotation(float new_rotation)
{
  rotation = new_rotation;
  for (int i = 0; i < number_of_sprites; ++i)
  {
    my_sprites[i]->rotationInRadians(rotation);
  }
}

/* Sets the current index for which sprite is returned */
void ScaledSpriteArray::setCurrentSprite(int new_sprite_index)
{
  if (new_sprite_index >= number_of_sprites)
  {
    current_sprite = number_of_sprites - 1;
  }
  else
  {
    current_sprite = new_sprite_index;
  }
}

/**
 *   @brief   Sets the fade colour
 *   @details Sets the fade colour of DynamicSprite,
 *			 this is the colour of tint applied when using fadeToColour
 *   @param   The new fade colour
 */
void ScaledSpriteArray::setFadeColour(ASGE::Colour col)
{
  fade_colour = col;
}

// Set colour straight away
void ScaledSpriteArray::setColour(ASGE::Colour col)
{
  for (int i = 0; i < number_of_sprites; i++)
  {
    my_sprites[i]->colour(col);
  }
}

/**
 *   @brief   Fades sprite to target colour
 *   @details This function applies a tint to the sprite each time it is called
 *            fully colouring it after time_to_fade ms
 *   @param   time_to_fade is the time it will take to fully tint
 *   @param   delta_time is the time since last tick
 *   @param   inverse_fade will remove tint instead
 */
bool ScaledSpriteArray::fadeToColour(double time_to_fade, double delta_time, bool inverse_fade)
{
  if (inverse_fade)
  {
    if (colour_fade_percent == 0)
    {
      return true;
    }
    if (time_to_fade == 0)
    {
      colour_fade_percent = 0;
    }
    else
    {
      // Calculate the amount of fade to be applied based on time passed
      colour_fade_percent -= static_cast<float>(delta_time) / static_cast<float>(time_to_fade);
    }
    if (colour_fade_percent <= 0)
    {
      colour_fade_percent = 0;
    }
  }
  else
  {
    if (colour_fade_percent == 1)
    {
      return true;
    }
    if (time_to_fade == 0)
    {
      colour_fade_percent = 0;
    }
    else
    {
      // Calculate the amount of fade to be applied based on time passed
      colour_fade_percent += static_cast<float>(delta_time) / static_cast<float>(time_to_fade);
    }
    if (colour_fade_percent >= 1)
    {
      colour_fade_percent = 1;
    }
  }

  ASGE::Colour new_col = ASGE::COLOURS::WHITE;
  new_col.r = (fade_colour.r) * colour_fade_percent;
  new_col.g = (fade_colour.g) * colour_fade_percent;
  new_col.b = (fade_colour.b) * colour_fade_percent;
  for (int i = 0; i < number_of_sprites; i++)
  {
    my_sprites[i]->colour(new_col);
  }
  return false;
}

// Fade in
bool ScaledSpriteArray::fadeIn(double time_to_fade, double delta_time)
{
  if (opacity_fade_percent == 1)
  {
    return true;
  }
  if (time_to_fade == 0)
  {
    opacity_fade_percent = 1;
  }
  else
  {
    // Calculate the amount of fade to be applied based on time passed
    opacity_fade_percent += static_cast<float>(delta_time) / static_cast<float>(time_to_fade);
  }
  if (opacity_fade_percent >= 1)
  {
    opacity_fade_percent = 1;
  }

  for (int i = 0; i < number_of_sprites; i++)
  {
    my_sprites[i]->opacity(opacity_fade_percent);
  }

  return false;
}

// Fade out
bool ScaledSpriteArray::fadeOut(double time_to_fade, double delta_time)
{
  if (opacity_fade_percent == 0)
  {
    return true;
  }
  if (time_to_fade == 0)
  {
    opacity_fade_percent = 1;
  }
  else
  {
    // Calculate the amount of fade to be applied based on time passed
    opacity_fade_percent -= static_cast<float>(delta_time) / static_cast<float>(time_to_fade);
  }
  if (opacity_fade_percent <= 0)
  {
    opacity_fade_percent = 0;
  }

  for (int i = 0; i < number_of_sprites; i++)
  {
    my_sprites[i]->opacity(opacity_fade_percent);
  }

  return false;
}

/**
 *   @brief   Sets the speed at which the sprite is animated
 *   @details Sets the time between animation frames used in returnNextSprite
 *           to calculate when to switch to the next frame
 *   @param   new_time_between_frames how quickly you want
 *           the sprite to animate
 */
void ScaledSpriteArray::timeBetweenFrames(double new_time_between_frames)
{
  time_between_frames = new_time_between_frames;
}

/**
 *   @brief   Gets the next frame of the sprite
 *   @details Sets the current step of animation to next step or the first
 *			 step if the animation is over if enough time has passed
 *   @param   delta_time is time since last call
 *   @return  The next sprite of the animation
 */
ASGE::Sprite& ScaledSpriteArray::returnNextSprite(double delta_time)
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

void ScaledSpriteArray::setSpriteSheet(float sprite_sheet_width,
                                       float sprite_sheet_height,
                                       float start_x_pos,
                                       float start_y_pos)
{
  src_rect[0] = start_x_pos;
  src_rect[1] = start_y_pos;
  src_rect[2] = sprite_sheet_width;
  src_rect[3] = sprite_sheet_height;

  // float* source_rect = my_sprites[0]->srcRect();
}

float ScaledSpriteArray::width_scale = 1;

/* Return number of sprites in object */
int ScaledSpriteArray::numberOfSprites()
{
  return number_of_sprites;
}