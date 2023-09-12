#include "iblock.h"

#include <string>
#include <vector>

#include "block.h"
using namespace std;

Iblock::Iblock(bool isHeavy) : Block{"I", isHeavy} {}

vector<vector<int>> Iblock::getBlockPosition(int overrideOrientation) {
  int returnOrientation;
  (overrideOrientation == -1) ? returnOrientation = orientation
                              : returnOrientation = overrideOrientation;
  if (returnOrientation == 0) {
    return {{0, 3}, {1, 3}, {2, 3}, {3, 3}};
  } else if (returnOrientation == 1) {
    return {{0, 0}, {0, 1}, {0, 2}, {0, 3}};
  } else if (returnOrientation == 2) {
    return {{0, 0}, {1, 0}, {2, 0}, {3, 0}};
  } else {
    return {{3, 0}, {3, 1}, {3, 2}, {3, 3}};
  }
}