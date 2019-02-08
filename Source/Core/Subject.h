//
// Created by kpo2-tooley on 08/02/2019.
//

#ifndef PLANNEDOBSOLESCENCE_SUBJECT_H
#define PLANNEDOBSOLESCENCE_SUBJECT_H

#include "../Constants.h"
#include "../Entity.h"
#include "Observer.h"

class Subject
{
  Subject() : head_(nullptr) {}
  // cppcheck-suppress unusedFunction
  void addObserver(Observer* observer);
  // cppcheck-suppress unusedFunction
  void removeObserver(Observer* observer);
  // cppcheck-suppress unusedFunction
  void notify(Entity& entity, Event event);

 private:
  Observer* head_;
};

#endif // PLANNEDOBSOLESCENCE_SUBJECT_H
