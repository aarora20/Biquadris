#include "oblock.h"

#include <string>
#include <vector>

#include "block.h"
using namespace std;

Oblock::Oblock(bool isHeavy) : Block{"O", isHeavy} {}

vector<vector<int>> Oblock::getBlockPosition(int overrideOrientation) {
  return {{0, 2}, {1, 2}, {0, 3}, {1, 3}};
}