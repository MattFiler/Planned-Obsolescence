#include "Camera.h"

/* Get/set our renderer */
void Camera::setRenderer(ASGE::Renderer* rend)
{
  renderer = rend;
}
ASGE::Renderer* Camera::getRenderer()
{
  return renderer;
}

/* Renders the passed sprite with the camera offset applied */
void Camera::renderSprite(ScaledSpriteArray* sprite,
                          double delta_time,
                          render_index index,
                          bool should_flipbook)
{
  // Add the camera offset to the sprite
  sprite->addX(-position.x_pos);
  sprite->addY(-position.y_pos);
  // Render ths sprite
  if (should_flipbook)
  {
    renderer->renderSprite(sprite->returnNextSprite(delta_time), static_cast<float>(index));
  }
  else
  {
    renderer->renderSprite(sprite->returnCurrentSprite(), static_cast<float>(index));
  }
  // Restore the sprite to the previous position
  sprite->addX(position.x_pos);
  sprite->addY(position.y_pos);
}

/* Returns the current position of the camera */
Point Camera::getCameraPosition()
{
  return position / ScaledSpriteArray::width_scale;
}

/* Converts a point in screen space to simulated world space, applying both camera offset and
 * scaling */
Point Camera::displayedToSimulatedWorld(Point point)
{
  point = point + position;
  point = point / ScaledSpriteArray::width_scale;
  return point;
}

/* Move the camera by the passed amount*/
void Camera::moveCamera(float x_amount, float y_amount)
{
  position.x_pos += x_amount;
  position.y_pos += y_amount;
}