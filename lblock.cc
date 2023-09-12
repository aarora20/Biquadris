#include "lblock.h"

#include <string>
#include <vector>

#include "block.h"
using namespace std;

Lblock::Lblock(bool isHeavy) : Block{"L", isHeavy} {}

vector<vector<int>> Lblock::getBlockPosition(int overrideOrientation) {
  int returnOrientation;
  (overrideOrientation == -1) ? returnOrientation = orientation
                              : returnOrientation = overrideOrientation;
  if (returnOrientation == 0) {
    return {{2, 2}, {0, 3}, {1, 3}, {2, 3}};
  } else if (returnOrientation == 1) {
    return {{0, 1}, {0, 2}, {0, 3}, {1, 3}};
  } else if (returnOrientation == 2) {
    return {{0, 1}, {1, 1}, {2, 1}, {0, 2}};
  } else {
    return {{1, 1}, {2, 1}, {2, 2}, {2, 3}};
  }
}