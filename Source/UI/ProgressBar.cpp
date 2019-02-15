#include "ProgressBar.h"

ProgressBar::ProgressBar(Point pos,
                         ASGE::Renderer* rend,
                         float bar_width,
                         float bar_height,
                         int direction,
                         Point _fill_padding) :
  UI(pos, rend),
  width(bar_width), height(bar_height), fill_padding(_fill_padding)
{
  if (direction == 1)
  {
    horizontal = false;
  }
}

/* Renders the background sprite then the fill sprite on top */
void ProgressBar::render(double delta_time)
{
  if (background_sprite)
  {
    renderer->renderSprite(background_sprite->returnNextSprite(delta_time));
  }
  if (fill_sprite)
  {
    renderer->renderSprite(fill_sprite->returnNextSprite(delta_time));
  }
}

/* Adds a background sprite to this object, then scales and rotates it fit the progress bar */
void ProgressBar::addBackgroundSprite(ScaledSpriteArray* sprite)
{
  background_sprite = sprite;
  background_sprite->xPos(position.x_pos);
  background_sprite->yPos(position.y_pos);
  background_sprite->setWidth(width);
  background_sprite->setHeight(height);
}

/* Adds a fill sprite to this object, then scales and rotates it fit the progress bar */
void ProgressBar::addFillSprite(ScaledSpriteArray* sprite)
{
  fill_sprite = sprite;
  fill_sprite->xPos(position.x_pos + (fill_padding.x_pos / 2));
  fill_sprite->yPos(position.y_pos + (fill_padding.y_pos / 2));
  if (horizontal)
  {
    fill_sprite->setWidth((width - fill_padding.x_pos) * bar_progress);
    fill_sprite->setHeight(height - fill_padding.y_pos);
  }
  else
  {
    fill_sprite->setWidth((width - fill_padding.x_pos));
    fill_sprite->setHeight((height - fill_padding.y_pos) * bar_progress);
  }
}

void ProgressBar::addProgress(float delta)
{
  bar_progress += delta;
  if (bar_progress > 1)
  {
    bar_progress = 1;
  }
  else if (bar_progress < 0)
  {
    bar_progress = 0;
  }
  if (horizontal)
  {
    fill_sprite->setWidth((width - fill_padding.x_pos) * bar_progress);
  }
  else
  {
    fill_sprite->setHeight((height - fill_padding.y_pos) * bar_progress);
  }
}