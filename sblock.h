#ifndef _SBLOCK_H_
#define _SBLOCK_H_
#include <string>
#include <vector>

#include "block.h"
using namespace std;

class Sblock : public Block {
 public:
  Sblock(bool isHeavy);
  vector<vector<int>> getBlockPosition(int overrideOrientation = -1) override;
};

#endif