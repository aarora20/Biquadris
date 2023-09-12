#include "board.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "cell.h"
#include "iblock.h"
#include "jblock.h"
#include "lblock.h"
#include "level0.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
#include "oblock.h"
#include "sblock.h"
#include "tblock.h"
#include "zblock.h"
using namespace std;

Board::Board(int startLevel, int seed, string scriptfile)
    : seed(seed), scriptfile(scriptfile) {
  auto blankCell = make_shared<Cell>(".", 0);
  auto emptyCell = make_shared<Cell>(" ", 0);
  for (int row = 0; row < 18; row++) {
    for (int col = 0; col < columns; col++) {
      if (row < 3) {
        data[row][col] = emptyCell;
      } else {
        data[row][col] = blankCell;
      }
    }
  }
  for (int row = 0; row < 2; ++row) {
    for (int col = 0; col < columns; col++) {
      nextData[row][col] = emptyCell;
    }
  }
  if (startLevel == 0) {
    level = make_unique<Level0>(scriptfile);
  } else if (startLevel == 1) {
    level = make_unique<Level1>(seed);
  } else if (startLevel == 2) {
    level = make_unique<Level2>(seed);
  } else if (startLevel == 3) {
    level = make_unique<Level3>(seed);
  } else if (startLevel == 4) {
    level = make_unique<Level4>(seed);
  }
}

void Board::changeLevel(int startLevel) {
  if (startLevel == 0) {
    level = make_unique<Level0>(scriptfile);
  } else if (startLevel == 1) {
    level = make_unique<Level1>(seed);
  } else if (startLevel == 2) {
    level = make_unique<Level2>(seed);
  } else if (startLevel == 3) {
    level = make_unique<Level3>(seed);
  } else if (startLevel == 4) {
    level = make_unique<Level4>(seed);
  }
}
bool Board::getHeavy() { return isHeavy; }

void Board::setHeavy(bool b) { isHeavy = b; }

Board::~Board() {}

void Board::drop() {
  while (validMove("down")) {
    curBlock->down();
  }
  curBlock = move(nextBlock);
  nextBlock = level->getBlock();
}

string Board::getRow(int row) {
  string output = "";
  for (int col = 0; col < columns; col++) {
    // Blind
    if (blind && col >= 3 && col <= 9 && row >= 6 && row <= 15) {
      output += "?";
    } else {
      output += data[row][col]->getType();
    }
  }
  return output;
}

string Board::getNextDataRow(int row) {
  string output = "";
  for (int col = 0; col < columns; col++) {
    output += nextData[row][col]->getType();
  }
  return output;
}

vector<vector<shared_ptr<Cell>>>& Board::getBoard() { return data; };
std::unique_ptr<Level>& Board::getLevelInstance() { return level; };

void Board::clearPos(int x, int y) {
  if (y > 2) {
    auto cell = make_shared<Cell>(".", 0);
    data[y][x] = cell;
  } else {
    auto cell = make_shared<Cell>(" ", 0);
    data[y][x] = cell;
  }
}

void Board::clearNextPos(int x, int y) {
  auto cell = make_shared<Cell>(" ", 0);
  nextData[y][x] = cell;
}

std::unique_ptr<Block>& Board::getCurBlock() { return curBlock; };
std::unique_ptr<Block>& Board::getNextBlock() { return nextBlock; };

void Board::setNextBlock() {
  int yOffset = -2;
  nextBlock = level->generateBlock();
  auto blockVector = nextBlock->getBlockPosition();
  auto blockType = nextBlock->getType();
  int level = getLevelInstance()->getLevel();
  auto cell = make_shared<Cell>(blockType, level);
  for (long unsigned int i = 0; i < blockVector.size(); i++) {
    int xpos = blockVector[i][0];
    int ypos = blockVector[i][1];
    nextData[ypos + yOffset][xpos] = cell;
  }
}

bool Board::setCurBlock() {
  curBlock = move(nextBlock);
  if (!validMove("place")) {
    return false;
  }
  auto blockVector = curBlock->getBlockPosition();
  auto blockType = curBlock->getType();
  int level = getLevelInstance()->getLevel();
  auto cell = make_shared<Cell>(blockType, level);
  for (long unsigned int i = 0; i < blockVector.size(); i++) {
    int xpos = blockVector[i][0];
    int ypos = blockVector[i][1];
    data[ypos][xpos] = cell;
  }
  return true;
}

void Board::placeCurBlock() {
  int xOffset = curBlock->getXOffset();
  int yOffset = curBlock->getYOffset();
  // cout << "X offset: " << xOffset << " Y offset: " << yOffset << endl;
  auto blockVector = curBlock->getBlockPosition();
  auto blockType = curBlock->getType();
  int level = getLevelInstance()->getLevel();
  auto cell = make_shared<Cell>(blockType, level);
  for (long unsigned int i = 0; i < blockVector.size(); i++) {
    int xpos = blockVector[i][0] + xOffset;
    int ypos = blockVector[i][1] + yOffset;
    data[ypos][xpos] = cell;
  }
}

void Board::updateCurBlock(string type) {
  if (type == "I" || type == "J" || type == "L" || type == "O" || type == "S" ||
      type == "Z" || type == "T") {
    curBlock = level->generateUpdatedBlock(type);
  } else {
    cout << "Type " << type << " not valid" << endl;
  }
}

bool Board::validMove(string move) {
  int xOffset = curBlock->getXOffset();
  int yOffset = curBlock->getYOffset();
  auto blockVector = curBlock->getBlockPosition();
  if (move == "place") {
    for (long unsigned int i = 0; i < blockVector.size(); i++) {
      int xpos = blockVector[i][0] + xOffset;
      int ypos = blockVector[i][1] + yOffset;
      if (data[ypos][xpos]->getType() != "." &&
          data[ypos][xpos]->getType() != " ") {
        // cout << "Position [" << xpos - 1 << "," << ypos
        //      << "] is invalid. Move cannot be made." << endl;
        return false;
      }
    }
  } else if (move == "left") {
    for (long unsigned int i = 0; i < blockVector.size(); i++) {
      int xpos = blockVector[i][0] + xOffset - 1;
      int ypos = blockVector[i][1] + yOffset;
      if (xpos < 0 || (data[ypos][xpos]->getType() != "." &&
                       data[ypos][xpos]->getType() != " ")) {
        // cout << "Position [" << xpos - 1 << "," << ypos
        //      << "] is invalid. Move cannot be made." << endl;
        return false;
      }
    }
  } else if (move == "right") {
    for (long unsigned int i = 0; i < blockVector.size(); i++) {
      int xpos = blockVector[i][0] + xOffset + 1;
      int ypos = blockVector[i][1] + yOffset;
      if (xpos > 10 || (data[ypos][xpos]->getType() != "." &&
                        data[ypos][xpos]->getType() != " ")) {
        // cout << "Position [" << xpos + 1 << "," << ypos
        //      << "] is invalid. Move cannot be made." << endl;
        return false;
      }
    }
  } else if (move == "down") {
    for (long unsigned int i = 0; i < blockVector.size(); i++) {
      int xpos = blockVector[i][0] + xOffset;
      int ypos = blockVector[i][1] + yOffset + 1;
      if (ypos > 17 || (data[ypos][xpos]->getType() != "." &&
                        data[ypos][xpos]->getType() != " ")) {
        //cout << "Position [" << xpos << "," << ypos + 1
        //      << "] is invalid. Move cannot be made." << endl;
        return false;
      }
    }
  } else if (move == "clockwise") {
    int newOrientation = getCurBlock()->getOrientation();
    newOrientation == 3 ? newOrientation = 0 : newOrientation++;
    blockVector = curBlock->getBlockPosition(newOrientation);
    for (long unsigned int i = 0; i < blockVector.size(); i++) {
      int xpos = blockVector[i][0] + xOffset;
      int ypos = blockVector[i][1] + yOffset;
      if (xpos < 0 || xpos > 10 || ypos > 17 ||
          (data[ypos][xpos]->getType() != "." &&
           data[ypos][xpos]->getType() != " ")) {
        // cout << "Position [" << xpos << "," << ypos + 1
        //      << "] is invalid. Move cannot be made." << endl;
        return false;
      }
    }
  } else if (move == "counterclockwise") {
    int newOrientation = getCurBlock()->getOrientation();
    newOrientation == 0 ? newOrientation = 3 : newOrientation;
    blockVector = curBlock->getBlockPosition(newOrientation);
    for (long unsigned int i = 0; i < blockVector.size(); i++) {
      int xpos = blockVector[i][0] + xOffset;
      int ypos = blockVector[i][1] + yOffset;
      if (xpos < 0 || xpos > 10 || ypos > 17 ||
          (data[ypos][xpos]->getType() != "." &&
           data[ypos][xpos]->getType() != " ")) {
        // cout << "Position [" << xpos << "," << ypos + 1
        //      << "] is invalid. Move cannot be made." << endl;
        return false;
      }
    }
  }
  return true;
}

void Board::setBlind(bool isBlind) { blind = isBlind; }

void Board::setForce(bool isForce) { force = isForce; }

void Board::setTurnsSinceClear(int turns) { turnsSinceClear = turns; }

int Board::getTurnsSinceClear() { return turnsSinceClear; }