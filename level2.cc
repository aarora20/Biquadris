
#include "level2.h"

#include <iostream>
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

Level2::Level2(int seed) : Level{2, seed} { srand(static_cast<int>(seed)); }

std::unique_ptr<Block> Level2::generateBlock() {
  int randInt = (rand() % 100) + 1;     // random int from [1, 100]
  double randDouble = randInt / 100.0;  // random double from [0.01, 1]
  if (randDouble <= 0.142857) {
    return make_unique<Sblock>(false);  // 1/7
  } else if (randDouble <= 0.285714) {
    return make_unique<Zblock>(false);  // 1/7
  } else if (randDouble <= 0.428571) {
    return make_unique<Iblock>(false);  // 1/7
  } else if (randDouble <= 0.571428) {
    return make_unique<Jblock>(false);  // 1/7
  } else if (randDouble <= 0.714285) {
    return make_unique<Oblock>(false);  // 1/7
  } else if (randDouble <= 0.857142) {
    return make_unique<Lblock>(false);  // 1/7
  } else {
    return make_unique<Tblock>(false);  // 1/7
  }
}

unique_ptr<Block> Level2::generateUpdatedBlock(string type) {
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

void Level2::setNoRandomFile(string file) {
  cout << "Not applicable" << endl; // Ideally this shouldn't happen
}