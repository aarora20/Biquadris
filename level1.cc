
#include "level1.h"

#include <iostream>
#include <memory>
#include <random>
#include <string>

#include "block.h"
#include "iblock.h"
#include "jblock.h"
#include "lblock.h"
#include "level.h"
#include "oblock.h"
#include "sblock.h"
#include "tblock.h"
#include "zblock.h"
using namespace std;

Level1::Level1(int seed) : Level{1, seed} { srand(static_cast<int>(seed)); }

std::unique_ptr<Block> Level1::generateBlock() {
  int randInt = (rand() % 100) + 1;     // random int from [1, 100]
  double randDouble = randInt / 100.0;  // random double from [0.01, 1]
  if (randDouble <= 0.083333) {
    return make_unique<Sblock>(false);  // 1/12
  } else if (randDouble <= 0.1666666) {
    return make_unique<Zblock>(false);  // 1/12
  } else if (randDouble <= 0.33333333) {
    return make_unique<Iblock>(false);  // 1/6
  } else if (randDouble <= 0.5) {
    return make_unique<Jblock>(false);  // 1/6
  } else if (randDouble <= 0.66666666) {
    return make_unique<Lblock>(false);  // 1/6
  } else if (randDouble <= 0.8333333) {
    return make_unique<Oblock>(false);  // 1/6
  } else {
    return make_unique<Tblock>(false);  // 1/6
  }
}

unique_ptr<Block> Level1::generateUpdatedBlock(string type) {
if (type != " ") {
    if (type == "I") {
    return make_unique<Iblock>(false);
  } else if (type == "J") {
    return make_unique<Jblock>(false);
  } else if (type == "L") {
    return make_unique<Lblock>(false);
  } else if (type == "O") {
    return make_unique<Oblock>(false);
  } else if (type == "S") {
    return make_unique<Sblock>(false);
  } else if (type == "T") {
    return make_unique<Tblock>(false);
  } else if (type == "Z") {
    return make_unique<Zblock>(false);
  } else {
    return nullptr;  // Ideally this situation should not occur
  }
  }
  else {
    return nullptr; // Ideally this situation should not occur
  }
}

void Level1::setNoRandomFile(string file) {
  cout << "Not applicable" << endl; // Ideally this shouldn't happen
}