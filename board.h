#ifndef _BOARD_H_
#define _BOARD_H_
#include <memory>
#include <string>
#include <vector>

#include "block.h"
#include "level0.h"
#include "cell.h"

using namespace std;

class Board {
    int seed = 123;
    string scriptfile;
    bool isHeavy = false;
    long unsigned int rows = 18;
    int columns = 11;
    int turnsSinceClear = 0;
    vector<vector<shared_ptr<Cell>>> data{rows, vector<shared_ptr<Cell>>(columns)};
    vector<vector<shared_ptr<Cell>>> nextData{rows, vector<shared_ptr<Cell>>(columns)};
    unique_ptr<Level> level;
    unique_ptr<Block> curBlock;
    unique_ptr<Block> nextBlock;
    bool blind = false;
    bool force = false;
    // bool heavy;
public:
    Board(int startLevel, int seed, string scriptfile);
    ~Board();
    string getRow(int row);
    string getNextDataRow(int row);
    vector<vector<shared_ptr<Cell>>> &getBoard();
    unique_ptr<Level> &getLevelInstance();
    unique_ptr<Block> &getCurBlock();
    unique_ptr<Block> &getNextBlock();
    void clearPos(int x, int y);
    void clearNextPos(int x, int y);
    void placeCurBlock();
    void updateCurBlock(string type);
    void changeLevel(int startLevel);
    // vector<vector<int>> getCurBlock();
    bool validMove(string move);
    // bool drop();
    // int calculateScore();
    // void clearRow();
    bool setCurBlock();
    void setNextBlock();
    void setBlind(bool isBlind);
    void setForce(bool isForce);
    bool getHeavy();
    void setHeavy(bool b);
    void setTurnsSinceClear(int turns);
    int getTurnsSinceClear();
};

#endif
