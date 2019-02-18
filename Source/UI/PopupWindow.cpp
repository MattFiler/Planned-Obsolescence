#include "PopupWindow.h"

PopupWindow::PopupWindow(Point pos,
                         ASGE::Renderer* rend,
                         const std::string& background_sprite_texture_path,
                         float _width,
                         float _height) :
  UI(pos, rend)
{
  width = _width;
  height = _height;
  background_sprite = createSprite(background_sprite_texture_path);
  background_sprite->setHeight(height);
  background_sprite->setWidth(width);
  background_sprite->xPos(position.x_pos);
  background_sprite->yPos(position.y_pos);

  Button* close_button = new Button(
    position + Point(width - 15, 0), rend, "data/UI/cross.png", "data/UI/cross.png", 15, 15);
  bool* active_p = &active;
  close_button->click_function = [active_p] { *active_p = false; };
  buttons.push_back(close_button);
}

PopupWindow::~PopupWindow()
{
  for (Button* button : buttons)
  {
    delete button;
    button = nullptr;
  }
  for (TextBox* text : text_boxes)
  {
    delete text;
    text = nullptr;
  }
  for (ProgressBar* progress : progress_bars)
  {
    delete progress;
    progress = nullptr;
  }
}

void PopupWindow::render(double delta_time)
{
  renderer->renderSprite(background_sprite->returnNextSprite(delta_time));
  for (Button* button : buttons)
  {
    button->render(delta_time);
  }
  for (TextBox* text : text_boxes)
  {
    text->render(delta_time);
  }
  for (ProgressBar* progress : progress_bars)
  {
    progress->render(delta_time);
  }
}

void PopupWindow::moveTo(Point point)
{
  position = point;
  background_sprite->xPos(point.x_pos);
  background_sprite->yPos(point.y_pos);
  for (Button* button : buttons)
  {
    button->moveTo(point);
  }
  for (TextBox* text : text_boxes)
  {
    text->moveTo(point);
  }
  for (ProgressBar* progress : progress_bars)
  {
    progress->moveTo(point);
  }
}

void PopupWindow::addButton(Button* new_button)
{
  buttons.push_back(new_button);
}

void PopupWindow::addTextBox(TextBox* new_text_box)
{
  text_boxes.push_back(new_text_box);
}

void PopupWindow::addProgressBar(ProgressBar* new_progress_bar)
{
  progress_bars.push_back(new_progress_bar);
}

/* Returns a pointer to the button that was clicked (nullptr if none) */
Button* PopupWindow::checkForClick(Point click_location)
{
  for (Button* button : buttons)
  {
    if (button->checkForClick(click_location))
    {
      return button;
    }
  }
  return nullptr;
}