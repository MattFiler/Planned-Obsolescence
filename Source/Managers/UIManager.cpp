#include "UIManager.h"

/* destroy! */
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
  for (GenericUI* generic_ui : generic_spriteset)
  {
    delete generic_ui;
    generic_ui = nullptr;
  }
  delete main_hud_element;
  main_hud_element = nullptr;

  delete char_info_popup;
  char_info_popup = nullptr;

  delete poi_interaction_popup;
  poi_interaction_popup = nullptr;

  delete game_cursor;
  game_cursor = nullptr;
}

/* Add a generic UI element set (foreground and background) */
void UIManager::addGenericUI(GenericUI* new_generic_ui)
{
  generic_spriteset.push_back(new_generic_ui);
}

/* Add a button */
void UIManager::addButton(Button* new_button)
{
  buttons.push_back(new_button);
}

/* Add a textbox */
void UIManager::addTextBox(TextBox* new_textbox)
{
  text_boxes.push_back(new_textbox);
}

/* Add a progress bar */
void UIManager::addProgressBar(ProgressBar* new_progressbar)
{
  progress_bars.push_back(new_progressbar);
}

/* Create main hud data element (we only have one of these) */
void UIManager::createMainHUD()
{
  // Create "main hud" element - bottom right stats gauges
  main_hud_element = new MainHUD(renderer);

  // Cursor
  game_cursor = new Cursor();
  game_cursor->setupCursor(renderer);

  // Initialise the bottom left interaction popups
  initCharacterPopup();       // Character interaction
  initPointOfInterestPopup(); // POI interaction
}

/* Initialise the character popup */
void UIManager::initCharacterPopup()
{
  char_info_popup = new CharacterInfoPopup(renderer);
  char_info_popup->setActive(false);
}

/* Initialise the poi interaction popup */
void UIManager::initPointOfInterestPopup()
{
  poi_interaction_popup = new WorldInteractionPopup(renderer);
  poi_interaction_popup->setActive(false);
}

/* Creates all the UI */
void UIManager::updateAndShowCharacterInfo(const std::string& character_type,
                                           float character_gauge,
                                           const std::string& gauge_name)
{
  poi_interaction_popup->setActive(false);

  char_info_popup->setActive(true);
  char_info_popup->setCharacterName(character_type);
  char_info_popup->setGaugeAmount(character_gauge);
  char_info_popup->setGaugeDescription(gauge_name);
}

/* Creates all the UI */
void UIManager::updateAndShowTileData(Tile& clicked_tile)
{
  char_info_popup->setActive(false);

  poi_interaction_popup->setActive(true);
  poi_interaction_popup->getClickedTileReference(clicked_tile);
}

/* render all ui */
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
  for (GenericUI* generic_ui : generic_spriteset)
  {
    generic_ui->render(delta_time);
  }

  if (char_info_popup != nullptr)
  {
    if (char_info_popup->isActive())
    {
      char_info_popup->render(delta_time);
    }
  }
  if (poi_interaction_popup != nullptr)
  {
    if (poi_interaction_popup->isActive())
    {
      poi_interaction_popup->render(delta_time);
    }
  }
  if (main_hud_element != nullptr)
  {
    main_hud_element->render(delta_time);
  }
  if (game_cursor != nullptr)
  {
    game_cursor->render();
  }
}

/* Checks all Buttons to see if the passed click lands on any of them */
bool UIManager::checkForClick(Point click, bool act_on_click)
{
  for (Button* button : buttons)
  {
    if (button->checkForClick(click))
    {
      if (act_on_click)
      {
        // Store a reference to the clicked button to un-click it later
        clicked_button = button;
      }
      return true;
    }
  }

  Button* popup_click_button = char_info_popup->checkForClick(click);
  if (popup_click_button)
  {
    if (act_on_click)
    {
      clicked_button = popup_click_button;
    }
    return true;
  }
  Button* popup_click_button2 = poi_interaction_popup->checkForClick(click);
  if (popup_click_button2)
  {
    if (act_on_click)
    {
      clicked_button = popup_click_button2;
    }
    return true;
  }

  return false;
}

/* 'un-clicks' the currently clicked button (if any) and triggers its click function */
void UIManager::releaseClick()
{
  if (clicked_button)
  {
    clicked_button->releaseClick();
    clicked_button = nullptr;
  }
}

/* Update */
void UIManager::update(double delta_time)
{
  input->getCursorPos(cursor_x, cursor_y);
  game_cursor->updatePosition(cursor_x, cursor_y);
}

/* keep a popup within the window bounds */
void UIManager::keepUIWithinScreen(UI* ui_object)
{
  /*
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
  */
}