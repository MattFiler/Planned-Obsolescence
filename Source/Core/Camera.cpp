#include "Camera.h"

void Camera::setRenderer(ASGE::Renderer* rend)
{
  renderer = rend;
}


/* Renders the passed sprite with the camera offset applied */
void Camera::renderSprite(DynamicSprite* sprite, double delta_time)
{
  // Add the camera offset to the sprite
  sprite->addX(position.x_pos);
  sprite->addY(position.y_pos);
  // Render ths sprite
  renderer->renderSprite(sprite->returnNextSprite(delta_time));
  // Restore the sprite to the previous position
  sprite->addX(-position.x_pos);
  sprite->addY(-position.y_pos);
}

/* Returns the current position of the camera */
Point Camera::getCameraPosition()
{
  return position;
}

/* Converts a point in screen space to simulated world space, applying both camera offset and scaling */
Point Camera::displayedToSimulatedWorld(Point point)
{
  point = point - position;
  point = point / DynamicSprite::width_scale;
  return  point;
}

/* Move the camera by the passed amount*/
void Camera::moveCamera(float x_amount, float y_amount)
{
  position.x_pos += x_amount;
  position.y_pos += y_amount;
}