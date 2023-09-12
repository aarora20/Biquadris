#ifndef _TBLOCK_H_
#define _TBLOCK_H_
#include <string>
#include <vector>

#include "block.h"
using namespace std;

class Tblock : public Block {
 public:
  Tblock(bool isHeavy);
  vector<vector<int>> getBlockPosition(int overrideOrientation = -1) override;
};

#endif