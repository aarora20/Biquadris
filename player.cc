#include "player.h"

#include "board.h"

Player::Player(int level, int score, Board* board)
    : level{level}, score{score}, board{board} {}
Player::~Player() {}
Board* Player::getBoard() { return board; }
void Player::updateLevel(int setLevel) { level = setLevel; }
int Player::getLevel() { return level; }
int Player::getScore() { return score; }
void Player::setScore(int newScore) { score = newScore; }