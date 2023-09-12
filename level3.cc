
#include "level3.h"

#include <fstream>
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

Level3::Level3(int seed) : Level{3, seed} {
  srand(static_cast<int>(seed));
  isHeavy = true;
}

std::unique_ptr<Block> Level3::generateBlock() {
  if (noRandomFile != "") {
    if (it == sequence.end()) {
      it = sequence.begin();
    }
    string blockType = *it;
    ++it;
    cout << "Generating block from " << noRandomFile << endl;
    return generateUpdatedBlock(blockType);
  }
  int randInt = (rand() % 100) + 1;     // random int from [1, 100]
  double randDouble = randInt / 100.0;  // random double from [0.01, 1]
  if (randDouble <= 0.222222) {
    return make_unique<Sblock>(true);  // 2/9
  } else if (randDouble <= 0.444444444) {
    return make_unique<Zblock>(true);  // 2/9
  } else if (randDouble <= 0.555555555) {
    return make_unique<Iblock>(true);  // 1/9
  } else if (randDouble <= 0.666666666) {
    return make_unique<Jblock>(true);  // 1/9
  } else if (randDouble <= 0.777777777) {
    return make_unique<Lblock>(true);  // 1/9
  } else if (randDouble <= 0.888888888) {
    return make_unique<Oblock>(true);  // 1/9
  } else {
    return make_unique<Tblock>(true);  // 1/9
  }
}

unique_ptr<Block> Level3::generateUpdatedBlock(string type) {
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

void Level3::setNoRandomFile(string file) {
  noRandomFile = file;
  if (noRandomFile != "") {
    ifstream inFile(noRandomFile);
    string blockType;
    while (inFile >> blockType) {
      sequence.push_back(blockType);
    }
    it = sequence.begin();
  } else { sequence.clear(); }
}