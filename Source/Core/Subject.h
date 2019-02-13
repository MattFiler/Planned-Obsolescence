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
 public:
  Subject() : head_(nullptr) {}
  void addObserver(Observer* observer);
  void removeObserver(Observer* observer);
  void notify(Event event);
  // void notify(Entity& entity, Event event);

 private:
  Observer* head_;
};

#endif // PLANNEDOBSOLESCENCE_SUBJECT_H
