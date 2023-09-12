#include "sblock.h"

#include <string>
#include <vector>

#include "block.h"
using namespace std;

Sblock::Sblock(bool isHeavy) : Block{"S", isHeavy} {}

vector<vector<int>> Sblock::getBlockPosition(int overrideOrientation) {
  int returnOrientation;
  (overrideOrientation == -1) ? returnOrientation = orientation
                              : returnOrientation = overrideOrientation;
  if (returnOrientation == 0) {
    return {{1, 2}, {2, 2}, {0, 3}, {1, 3}};
  } else if (returnOrientation == 1) {
    return {{0, 1}, {0, 2}, {1, 2}, {1, 3}};
  } else if (returnOrientation == 2) {
    return {{1, 1}, {2, 1}, {0, 2}, {1, 2}};
  } else {
    return {{1, 1}, {1, 2}, {2, 2}, {2, 3}};
  }
}