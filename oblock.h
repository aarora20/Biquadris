#ifndef _OBLOCK_H_
#define _OBLOCK_H_
#include <string>
#include <vector>

#include "block.h"
using namespace std;

class Oblock : public Block {
 public:
  Oblock(bool isHeavy);
  vector<vector<int>> getBlockPosition(int overrideOrientation = -1) override;
};

#endif