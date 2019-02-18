#include "UIManager.h"
#include "../Characters/Boss.h"

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
    buildButtons();
    buildTextBoxes();
    buildProgressBars();
    buildPopupWindows();
  }
}

void UIManager::buildButtons()
{
  Button* button = new Button(
    Point(SCREEN_WIDTH - 50, 0), renderer, "data/UI/cross.png", "data/UI/cross.png", 50, 50);
  scenes* next = &next_scene;
  button->click_function = [next] { *next = scenes::MAIN_MENU; };
  buttons.push_back(button);
}

void UIManager::buildTextBoxes() {}

void UIManager::buildProgressBars()
{
  boss_popup = new PopupWindow(Point(0, 0), renderer, "data/UI/default.png");
  TextBox* text = new TextBox(Point(10, 10), renderer, "The BOSS");
  boss_popup->addTextBox(text);
}

void UIManager::buildPopupWindows() {}

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

  if (boss_popup->isActive())
  {
    boss_popup->render(delta_time);
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

  clicked_button = boss_popup->checkForClick(click);

  return clicked_button != nullptr;
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

void UIManager::enableBossPopup(Boss* boss)
{
  boss_popup->setActive(true);
  boss_popup->moveTo(boss->getPosition() - camera->getCameraPosition() );
  // keepUIWithinScreen(boss_popup);
  // TODO Add info about the boss from the passed ref
}

void UIManager::keepUIWithinScreen(UI* ui_object)
{
  Point new_pos = ui_object->getPosition();
  if (new_pos.x_pos > SCREEN_WIDTH - boss_popup->getWidth())
  {
    new_pos.x_pos = SCREEN_WIDTH - boss_popup->getWidth();
  }
  else if (new_pos.x_pos < 0)
  {
    new_pos.x_pos = 0;
  }
  if (new_pos.y_pos > SCREEN_HEIGHT - boss_popup->getHeight())
  {
    new_pos.y_pos = SCREEN_HEIGHT - boss_popup->getHeight();
  }
  else if (new_pos.y_pos < 0)
  {
    new_pos.y_pos = 0;
  }
  ui_object->moveTo(new_pos);
}