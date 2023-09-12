#ifndef _BLOCK_H_
#define _BLOCK_H_
#include <string>
#include <vector>
using namespace std;

class Block {
 protected:
  string type;
  bool isHeavy;
  int xOffset = 0;
  int yOffset = 0;
  int orientation = 0;

 public:
  Block(string type, bool isHeavy);
  virtual ~Block();

  void rotateCw();
  void rotateCcw();
  void left();
  void down();
  void right();

  virtual vector<vector<int>> getBlockPosition(
      int overrideOrientation = -1) = 0;
  string getType();
  bool getHeavy();
  int getOrientation();
  int getXOffset();
  int getYOffset();
};

#endif