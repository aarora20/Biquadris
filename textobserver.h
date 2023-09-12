#ifndef _TEXTOBSERVER_H_
#define _TEXTOBSERVER_H_

#include "observer.h"

class Game;

class TextObserver : public Observer {
 public:
  TextObserver(Game *game);
  ~TextObserver() override;

  void notify() override;
  void printPlayerInfo();
  void printBoards();
  void printNextBlocks();
};

#endif