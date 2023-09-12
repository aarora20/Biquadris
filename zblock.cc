#include "zblock.h"

#include <string>
#include <vector>

#include "block.h"
using namespace std;

Zblock::Zblock(bool isHeavy) : Block{"Z", isHeavy} {}

vector<vector<int>> Zblock::getBlockPosition(int overrideOrientation) {
  int returnOrientation;
  (overrideOrientation == -1) ? returnOrientation = orientation
                              : returnOrientation = overrideOrientation;
  if (returnOrientation == 0) {
    return {{0, 2}, {1, 2}, {1, 3}, {2, 3}};
  } else if (returnOrientation == 1) {
    return {{1, 1}, {0, 2}, {1, 2}, {0, 3}};
  } else if (returnOrientation == 2) {
    return {{0, 1}, {1, 1}, {1, 2}, {2, 2}};
  } else {
    return {{2, 1}, {1, 2}, {2, 2}, {1, 3}};
  }
}