#ifndef _GAME_
#define _GAME_

#include <memory>

#include "player.h"
#include "subject.h"

class Game : public Subject {
 private:
  static const int MAX_LEVEL = 4;
  static const int MIN_LEVEL = 0;
  static const int BLOCK_ROW_START = 0;
  static const int BLOCK_ROW_END = 18;
  static const int BLOCK_COLUMN_SIZE = 11;

  string cmd = "";

  int seed, startLevel;

  bool sequencePassed;
  vector<string> sequence = {};
  vector<string>::iterator it = sequence.begin();

  bool text, restartCommandTriggered;
  string file1, file2, noRandomFile;
  std::unique_ptr<Board> board1;
  std::unique_ptr<Board> board2;
  std::unique_ptr<Player> player1;
  std::unique_ptr<Player> player2;

  bool executePlayerCommand(Board* board, Player* player, int playerNum);
  void handleLevelCommand(const string& cmd, Board* board, Player* player);
  void handleDropCommand(Board* board);
  void handleRotateCommand(const string& cmd, Board* board);
  void handleMoveCommand(const string& cmd, Board* board);
  void handleReplaceBlockCommand(const string& cmd, Board* board);
  void handleSequenceCommand();
  void clearCurBlock(Board* board, int xOffset, int yOffset);
  void clearNextBlock(Board* board);
  void isHeavyDrop(Board* board);
  void clearRow(Board* board, vector<int> rows);
  vector<int> isRowFull(Board* board, Player* player);
  void calculateScore(Board* board, Player* player, int playerNum,
                      vector<int> rows);

 public:
  Game(int seed, int startLevel, bool text, string file1, string file2);
  ~Game();

  Player* getPlayer(int i = 1);

  string start();
  string executeTurns();
  bool player1Turn();
  bool player2Turn();
};

#endif