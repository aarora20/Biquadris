#ifndef _OBSERVER_H_
#define _OBSERVER_H_

class Game;

class Observer {
 protected:
  Game *game;

 public:
  Observer(Game *game);
  virtual void notify() = 0;
  virtual ~Observer() = default;
};

#endif