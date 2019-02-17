#include "UIManager.h"

UIManager& UIManager::getInstance()
{
  static UIManager instance;
  return instance;
}

UIManager::~UIManager()
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

/* Creates all the UI */
void UIManager::buildUI()
{
  next_scene = scenes ::NO_CHANGE;
  if (!loaded)
  {
    Button* button = new Button(
      Point(SCREEN_WIDTH - 50, 0), renderer, "data/UI/cross.png", "data/UI/cross.png", 50, 50);
    scenes* next = &next_scene;
    button->click_function = [next] { *next = scenes::MAIN_MENU; };
    buttons.push_back(button);
  }
}

void UIManager::render(double delta_time)
{
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

/* Checks all Buttons to see if the passed click lands on any of them */
bool UIManager::checkForClick(Point click)
{
  for (Button* button : buttons)
  {
    if (button->checkForClick(click))
    {
      // Store a reference to the clicked button to un-click it later
      clicked_button = button;
      return true;
    }
  }
  return false;
}

/* 'un-clicks' the currently clicked button (if any) and triggers its click function */
scenes UIManager::releaseClick()
{
  if (clicked_button)
  {
    clicked_button->releaseClick();
    clicked_button = nullptr;
  }
  return next_scene;
}