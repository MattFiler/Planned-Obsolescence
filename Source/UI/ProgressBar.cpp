#include "ProgressBar.h"

ProgressBar::ProgressBar(Point pos,
                         ASGE::Renderer* rend,
                         float bar_width,
                         float bar_height,
                         int direction,
                         Point _fill_padding) :
  UI(pos, rend),
  fill_padding(_fill_padding)
{
  width = bar_width;
  height = bar_height;
  if (direction == 1)
  {
    horizontal = false;
  }
}

ProgressBar::~ProgressBar()
{
  delete background_sprite;
  background_sprite = nullptr;
  delete fill_sprite;
  fill_sprite = nullptr;
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

void ProgressBar::moveTo(Point point)
{
  position = point;
  background_sprite->xPos(point.x_pos);
  background_sprite->yPos(point.y_pos);
  fill_sprite->xPos(point.x_pos);
  fill_sprite->yPos(point.y_pos);
}

/* Adds a background sprite to this object, then scales and rotates it fit the progress bar */
void ProgressBar::addBackgroundSprite(const std::string& sprite_texture_path)
{
  background_sprite = createSprite(sprite_texture_path);
  background_sprite->xPos(position.x_pos);
  background_sprite->yPos(position.y_pos);
  background_sprite->setWidth(width);
  background_sprite->setHeight(height);
}

/* Adds a fill sprite to this object, then scales and rotates it fit the progress bar */
void ProgressBar::addFillSprite(const std::string& sprite_texture_path)
{
  fill_sprite = createSprite(sprite_texture_path);
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