#include "level0.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

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

Level0::Level0(const string& filename) : Level{0, 0} {
  ifstream inFile(filename);
  string blockType;
  while (inFile >> blockType) {
    sequence.push_back(blockType);
  }
  it = sequence.begin();
}

unique_ptr<Block> Level0::generateBlock() {
  if (it == sequence.end()) {
    it = sequence.begin();
  }
  string blockType = *it;
  ++it;
  if (blockType == "I") {
    return make_unique<Iblock>(false);
  } else if (blockType == "J") {
    return make_unique<Jblock>(false);
  } else if (blockType == "L") {
    return make_unique<Lblock>(false);
  } else if (blockType == "O") {
    return make_unique<Oblock>(false);
  } else if (blockType == "S") {
    return make_unique<Sblock>(false);
  } else if (blockType == "T") {
    return make_unique<Tblock>(false);
  } else if (blockType == "Z") {
    return make_unique<Zblock>(false);
  } else {
    return nullptr;  // Ideally this situation should not occur
  }
}

unique_ptr<Block> Level0::generateUpdatedBlock(string type) {
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

void Level0::setNoRandomFile(string file) {
  cout << "Not applicable" << endl; // Ideally this shouldn't happen
}