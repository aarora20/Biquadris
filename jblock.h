#ifndef _JBLOCK_H_
#define _JBLOCK_H_
#include <string>
#include <vector>

#include "block.h"
using namespace std;

class Jblock : public Block {
 public:
  Jblock(bool isHeavy);
  vector<vector<int>> getBlockPosition(int overrideOrientation = -1) override;
};

#endif