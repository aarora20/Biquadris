#include "textobserver.h"

#include <iomanip>
#include <iostream>

#include "game.h"

using namespace std;

TextObserver::TextObserver(Game *game) : Observer{game} { game->attach(this); }

TextObserver::~TextObserver() { game->detach(this); }

void TextObserver::printPlayerInfo() {
  cout << " Player:" << setw(4) << "1";
  cout << "     Player:" << setw(4) << "2" << endl;
  cout << " Level:" << setw(5) << game->getPlayer(1)->getLevel();
  cout << "     Level:    " << game->getPlayer(2)->getLevel() << endl;
  cout << " Score:" << setfill(' ') << setw(5)
       << game->getPlayer(1)->getScore();
  cout << "     Score:"
       << "    " << game->getPlayer(2)->getScore() << endl;
}

void TextObserver::printBoards() {
  static const int COLUMNS = 27;
  static const int ROWS = 18;
  cout << "+";
  for (int i = 0; i < COLUMNS; i++) cout << "-";
  cout << "+" << endl;
  for (int row = 0; row < ROWS; row++) {
    cout << "|" << game->getPlayer(1)->getBoard()->getRow(row) << "     ";
    cout << game->getPlayer(2)->getBoard()->getRow(row) << "|" << endl;
  }
  cout << "+";
  for (int i = 0; i < COLUMNS; i++) cout << "-";
  cout << "+" << endl;
}

void TextObserver::printNextBlocks() {
  static const int ROWS = 2;
  cout << "Next:" << setw(17) << "Next:" << endl;
  for (int row = 0; row < ROWS; row++) {
    cout << game->getPlayer(1)->getBoard()->getNextDataRow(row) << "      ";
    cout << game->getPlayer(2)->getBoard()->getNextDataRow(row) << endl;
  }
  cout << endl;
}
void TextObserver::notify() {
  printPlayerInfo();
  printBoards();
  printNextBlocks();
}