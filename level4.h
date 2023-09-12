#ifndef _LEVEL4_H_
#define _LEVEL4_H_
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>

#include "block.h"
#include "level.h"
using namespace std;

class Level4 : public Level {
  string noRandomFile = "";
  vector<string> sequence = {};
  vector<string>::iterator it = sequence.begin();
 public:
  Level4(int seed);
  std::unique_ptr<Block> generateBlock() override;
  std::unique_ptr<Block> generateUpdatedBlock(string oBlock = " ") override;
  void setNoRandomFile(string file) override;
};

#endif