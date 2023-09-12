#ifndef _LBLOCK_H_
#define _LBLOCK_H_
#include <string>
#include <vector>

#include "block.h"
using namespace std;

class Lblock : public Block {
 public:
  Lblock(bool isHeavy);
  vector<vector<int>> getBlockPosition(int overrideOrientation = -1) override;
};

#endif