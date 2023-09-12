#include "tblock.h"

#include <string>
#include <vector>

#include "block.h"
using namespace std;

Tblock::Tblock(bool isHeavy) : Block{"T", isHeavy} {}

vector<vector<int>> Tblock::getBlockPosition(int overrideOrientation) {
  int returnOrientation;
  (overrideOrientation == -1) ? returnOrientation = orientation
                              : returnOrientation = overrideOrientation;
  if (returnOrientation == 0) {
    return {{0, 2}, {1, 2}, {2, 2}, {1, 3}};
  } else if (returnOrientation == 1) {
    return {{2, 1}, {1, 2}, {2, 2}, {2, 3}};
  } else if (returnOrientation == 2) {
    return {{1, 2}, {0, 3}, {1, 3}, {2, 3}};
  } else {
    return {{0, 1}, {0, 2}, {0, 3}, {1, 2}};
  }
}