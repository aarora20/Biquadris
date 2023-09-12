#include "cell.h"

#include <iostream>
#include <string>

using namespace std;

Cell::Cell(std::string type, int level) : type{type}, level{level} {
  remainingBlocks = 4;
}

Cell::~Cell() {}

int Cell::getRemainingBlocks() {return remainingBlocks;}

string Cell::getType() {return type;}

int Cell::getLevel() {return level;}

void Cell::setRemainingBlocks(int BlocksRemaining) {
    remainingBlocks = BlocksRemaining;
}

void Cell::setType(string bType) {
    type = bType;
}