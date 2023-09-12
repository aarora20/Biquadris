#ifndef _LEVEL2_H_
#define _LEVEL2_H_
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>

#include "block.h"
#include "level.h"
using namespace std;

class Level2 : public Level {
 public:
  Level2(int seed);
  std::unique_ptr<Block> generateBlock() override;
  std::unique_ptr<Block> generateUpdatedBlock(string oBlock = " ") override;
  void setNoRandomFile(string file) override;
};

#endif