#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "board.h"

class Player {
 protected:
  int level, score;
  Board* board;

 public:
  Player(int level, int score, Board* board);
  ~Player();
  Board* getBoard();
  void updateLevel(int setLevel);
  int getLevel();
  int getScore();
  void setScore(int newScore);
};

#endif