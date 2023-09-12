#include "block.h"

#include <string>
#include <vector>

using namespace std;

Block::Block(string type, bool isHeavy) : type{type}, isHeavy{isHeavy} {}

string Block::getType() { return type; }

bool Block::getHeavy() { return isHeavy; }

void Block::rotateCw() {
  if (orientation == 3) {
    orientation = 0;
  } else {
    ++orientation;
  }
};

void Block::rotateCcw() {
  if (orientation == 0) {
    orientation = 3;
  } else {
    --orientation;
  }
};

void Block::left() { --xOffset; }

void Block::down() { ++yOffset; }

void Block::right() { ++xOffset; }

int Block::getOrientation() { return orientation; }

int Block::getXOffset() { return xOffset; }

int Block::getYOffset() { return yOffset; }

Block::~Block() {}