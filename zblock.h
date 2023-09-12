#ifndef _ZBLOCK_H_
#define _ZBLOCK_H_
#include <string>
#include <vector>

#include "block.h"
using namespace std;

class Zblock : public Block {
 public:
  Zblock(bool isHeavy);
  vector<vector<int>> getBlockPosition(int overrideOrientation = -1) override;
};

#endif