//
// Created by kpo2-tooley on 08/02/2019.
//

#include "Subject.h"


Subject::~Subject()
{
    notify(*this, Defult);
}


void Subject::addObserver(Observer *observer)
{
    observer->next_= head_;
    head_ = observer;
}

void Subject::removeObserver(Observer *observer)
{
    if (observer == head_)
    {
        head_ = observer->next_;
        observer->next_= nullptr;
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

void Subject::notify(Subject &entity, Event event)
{
    Observer* observer = head_;
    while (observer != nullptr)
    {
        observer->onNotify(nullptr);
        observer = observer->next_;
    }
}