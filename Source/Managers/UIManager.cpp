#include "UIManager.h"

void UIManager::render(double delta_time)
{

}

/* Checks all Buttons to see if the passed click lands on any of them */
bool UIManager::checkForClick(Point click)
{
    for(Button& button : buttons)
    {
        if(button.checkForClick(click))
        {
            // Store a reference to the clicked button to un-click it later
            clicked_button = &button;
            return  true;
        }
    }
    return false;
}

/* 'un-clicks' the currently clicked button (if any) and triggers its click function */
void UIManager::releaseClick()
{
    if(clicked_button)
    {
        clicked_button->releaseClick();
        clicked_button = nullptr;
    }
}