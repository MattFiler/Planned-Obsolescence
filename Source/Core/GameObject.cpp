//
// Created by tobyj on 15/01/2019.
//

#include "GameObject.h"

/**
 *   @brief   Default Deconstructor.
 *   @param   The renderer for the game
 */
GameObject::GameObject() {}

/**
 *   @brief   Default Deconstructor.
 */
GameObject::~GameObject()
{
  if (sprite)
  {
    delete sprite;
    sprite = nullptr;
  }
}

/**
 *   @brief   Setter for should_destroy
 *   @param   New flag for should_destroy
 */
void GameObject::shouldDestroy(bool flag)
{
  should_destroy = flag;
}

/**
 *   @brief   Getter for should_destroy
 *   @return  value for should_destroy
 */
bool GameObject::shouldDestroy()
{
  return should_destroy;
}

/**
 *   @brief   Setter for name
 *   @param   New name for this object
 */
void GameObject::setName(std::string new_name)
{
  name = new_name;
}

/**
 *   @brief   Getter for name
 *   @return  The name for this object
 */
std::string GameObject::getName()
{
  return name;
}

/**
 *   @brief   Getter for position.x
 *   @return  The x position of this object
 */
float GameObject::xPos()
{
  return position.x;
}

/**
 *   @brief   Setter for position.x
 *   @details Sets the x position for attached sprites (if any)
 *            with correct resolution scaling
 *   @param   New x position for object
 */
void GameObject::xPos(float new_x)
{
  position.x = new_x;
  center.x = new_x - ((width * scale) / 2);
  // If there is a sprite component, update its position too
  if (sprite != nullptr)
  {
    sprite->xPos(new_x * AnimatedSprite::width_scale);
  }
}

/**
 *   @brief   Getter for position.y
 *   @return  The y position of this object
 */
float GameObject::yPos()
{
  return position.y;
}

/**
 *   @brief   Setter for position.y
 *   @details Sets the y position for attached sprites (if any)
 *            with correct resolution scaling
 *   @param   New y position for object
 */
void GameObject::yPos(float new_y)
{
  position.y = new_y;
  center.y = new_y - ((height * scale) / 2);
  // If there is a sprite component, update its position too
  if (sprite != nullptr)
  {
    sprite->yPos(new_y * AnimatedSprite::width_scale);
  }
}

/**
 *   @brief   Moves the object
 *   @param   x/y how much to move in x/y
 */
void GameObject::move(float x, float y)
{
  xPos(position.x + x);
  yPos(position.y + y);
}

/**
 *   @brief   Moves this object so that its center is at (x,y)
 *   @details Requires a sprite component to function
 *   @param   x is the x position in cartesian co-ordinates
 *            y is the y position in cartesian co-ordinates
 */
void GameObject::CenterSpriteOnPoint(float x, float y)
{
  if (sprite != nullptr)
  {
    center.x = x;
    center.y = y;

    float new_x = x - ((width * scale) / 2);
    float new_y = y - ((height * scale) / 2);

    xPos(new_x);
    yPos(new_y);
  }
}

/**
 *   @brief   Setter for scale
 *   @details Sets the scale for attached sprites (if any)
 *            with correct resolution scaling
 *   @param   New y position for object
 */
void GameObject::setScale(float new_scale)
{
  scale = new_scale;
  if (sprite != nullptr)
  {
    sprite->scale(scale * AnimatedSprite::width_scale);
  }
}

/**
 *   @brief   Getter for scale
 *   @return  The scale of this object
 */
float GameObject::getScale()
{
  return scale;
}

/**
 *   @brief   Scales the object to a width (requires AnimatedSprite)
 *   @details This function scales an object down in both axis
 *			 to the desired width based on the width of
 *			 the first sprite in the attached AnimatedSprite
 *   @param   The desired width of the object
 */
void GameObject::scaleToWidth(float target_width)
{
  if (sprite != nullptr)
  {
    // Calcualte the new scale factor
    float scale_difference = target_width / width;
    setScale(scale_difference);
  }
}

/**
 *   @brief   Scales the object to a height (requires AnimatedSprite)
 *   @details This function scales an object down in both axis
 *			  to the desired height based on the height of
 *			  the first sprite in the attached AnimatedSprite
 *   @param   The desired width of the object
 */
void GameObject::scaleToHeight(float target_height)
{
  if (sprite != nullptr)
  {
    // Calcualte the new scale factor
    float scale_difference = target_height / height;
    setScale(scale_difference);
  }
}

/**
 *   @brief   Sets the animated sprite
 *   @details Deletes any existing animated sprite and replaces with the passed
 *            sprite
 *   @param   Pointer to the new sprite
 */
void GameObject::setAnimatedSprite(AnimatedSprite* new_sprite)
{
  delete (sprite);
  sprite = new_sprite;
  // Store the unmodified width, height and scale
  width = sprite->width();
  height = sprite->height();
  scale = sprite->scale();
  // Modify the ASGE::Sprites scale and position with width_scale
  sprite->scale(scale * AnimatedSprite::width_scale);
  sprite->xPos(position.x * AnimatedSprite::width_scale);
  sprite->yPos(position.y * AnimatedSprite::width_scale);
}

/**
 *   @brief   Getter for the AnimatedSprite
 *   @return  The AnimatedSprite attached to this object
 */
AnimatedSprite* GameObject::getAnimatedSprite()
{
  return sprite;
}