#ifndef _IBLOCK_H_
#define _IBLOCK_H_
#include <string>
#include <vector>

#include "block.h"
using namespace std;

class Iblock : public Block {
 public:
  Iblock(bool isHeavy);
  vector<vector<int>> getBlockPosition(int overrideOrientation = -1) override;
};

#endif