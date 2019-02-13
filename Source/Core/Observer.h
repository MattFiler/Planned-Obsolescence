//
// Created by kpo2-tooley on 29/01/2019.
//

#ifndef PLANNEDOBSOLESCENCE_OBSERVER_H
#define PLANNEDOBSOLESCENCE_OBSERVER_H

#include "../Constants.h"
#include "../Entity.h"

class Subject;

class Observer
{
  friend class Subject;

 public:
  Observer() : next_(nullptr) {}

  virtual ~Observer() = default;
  virtual void onNotify(Event event) = 0;
  // virtual void onNotify(Entity& entity, Event event) = 0;

 private:
  Observer* next_;
};

#endif // PLANNEDOBSOLESCENCE_OBSERVER_H
