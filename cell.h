#ifndef _CELL_
#define _CELL_

#include <string>

class Cell {
    std::string type;
    int remainingBlocks, level;
public:
    Cell(std::string type, int level);
    ~Cell();
    std::string getType();
    void setType(std::string btype);
    int getLevel();
    int getRemainingBlocks();
    void setRemainingBlocks(int remainingBlocks);
};

#endif