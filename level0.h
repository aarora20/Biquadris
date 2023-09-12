#ifndef _LEVEL0_H_
#define _LEVEL0_H_
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "block.h"
#include "level.h"
using namespace std;

class Level0 : public Level {
  vector<string> sequence = {};
  vector<string>::iterator it = sequence.begin();

 public:
  Level0(const string& filename);
  std::unique_ptr<Block> generateBlock() override;
  std::unique_ptr<Block> generateUpdatedBlock(string oBlock = " ") override;
  void setNoRandomFile(string file) override;
};

#endif
