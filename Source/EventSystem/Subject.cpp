//
// Created by kpo2-tooley on 08/02/2019.
//

#include "Subject.h"

// cppcheck-suppress *
void Subject::addObserver(Observer* observer)
{
  observer->next_ = head_;
  head_ = observer;
}

// cppcheck-suppress *
void Subject::removeObserver(Observer* observer)
{
  if (observer == head_)
  {
    head_ = observer->next_;
    observer->next_ = nullptr;
    return;
  }

  Observer* current = head_;
  while (current != nullptr)
  {
    if (current->next_ == observer)
    {
      current->next_ = observer->next_;
      observer->next_ = nullptr;
      return;
    }
    current = current->next_;
  }
}

// cppcheck-suppress *
void Subject::notify(Event event)
{
  Observer* observer = head_;
  while (observer != nullptr)
  {
    observer->onNotify(event);
    observer = observer->next_;
  }
}