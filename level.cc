#include "level.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "block.h"
using namespace std;

Level::Level(int level, int seed) : level{level}, seed{seed} {}

int Level::getLevel() { return level; }

bool Level::getHeavy() { return isHeavy; }

Level::~Level() {}