#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>

class Observer;

class Subject {
  std::vector<Observer *> subscribers;

 public:
  void attach(Observer *o);
  void detach(Observer *o);
  void notifyObservers();
  virtual ~Subject() = default;
};

#endif