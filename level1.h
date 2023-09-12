#ifndef _LEVEL1_H_
#define _LEVEL1_H_
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "block.h"
#include "level.h"
using namespace std;

class Level1 : public Level {
 public:
  Level1(int seed);
  std::unique_ptr<Block> generateBlock() override;
  std::unique_ptr<Block> generateUpdatedBlock(string oBlock = " ") override;
  void setNoRandomFile(string file) override;
};

#endif
