#ifndef _LEVEL_H_
#define _LEVEL_H_
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "block.h"
using namespace std;

class Level {
 protected:
  int level, seed;
  bool isHeavy;

 public:
  Level(int level, int seed);
  virtual ~Level();
  int getLevel();
  bool getHeavy();
  virtual std::unique_ptr<Block> generateBlock() = 0; // Pure virtual function
  virtual std::unique_ptr<Block> generateUpdatedBlock(string oBlock = " ") = 0; // Pure virtual function
  virtual void setNoRandomFile(string file) = 0;
};

#endif