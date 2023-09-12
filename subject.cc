#include "subject.h"

#include <vector>

#include "observer.h"

void Subject::attach(Observer *o) { subscribers.emplace_back(o); }

void Subject::detach(Observer *o) {
  for (auto it = subscribers.begin(); it != subscribers.end();) {
    if (*it == o)
      it = subscribers.erase(it);
    else
      ++it;
  }
}

void Subject::notifyObservers() {
  for (auto &ob : subscribers) ob->notify();
}